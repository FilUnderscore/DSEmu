#include <ARM.hpp>

#include <DSSystem.hpp>
#include <Logger.hpp>
#include <Bits.hpp>
#include <String.hpp>
#include <InstructionDecoder.hpp>
#include <BranchInstruction.hpp>
#include <DataProcessingInstruction.hpp>
#include <HalfwordDataTransferInstruction.hpp>
#include <SingleDataTransferInstruction.hpp>

ARM::ARM(DSSystem* ds)
{
	this->ds = ds;

	this->init();
}

ARM::~ARM()
{

}

void ARM::init()
{
	this->registerMap = new Pointer<uint32_t>(16 + 1);

	// (16 + 5) = 21 shadow registers
	this->registerShadowMap = new map<ProcessorMode, Pointer<uint32_t>*>();

	this->pipeline = new vector<Instruction*>();

	Operation::init();
}

void ARM::setRegister(Register reg, uint32_t value)
{
	this->registerMap->operator[](reg) = value;
}

uint32_t ARM::getRegister(Register reg)
{
	return this->registerMap->operator[](reg);
}

void ARM::print()
{
	Logger::log("");
	Logger::log("ARM Registers");

	for(uint32_t index = 0; index < this->registerMap->getSize(); index++)
	{
		uint32_t value = this->getRegister((Register) index);

		Logger::log("R" + to_string(index) + ": " + to_string(value));
	}

	Logger::log("");
}

#include <thread>
#include <chrono>

void ARM::run()
{
	// executeAt(0x02);
	this->setRegister(::PC, 0x02);

	while(this->fetchNextInstruction())
	{
		this->tick();

		// Clock delay = milliseconds / Hz
		// Clock delay = 1000ms / 66 Hz
		this_thread::sleep_for(std::chrono::milliseconds(1000 / 66));
	}
}

void ARM::processPipeline()
{
	for(uint32_t index = 0; index < this->pipeline->size(); index++)
	{
		Instruction* instruction = this->pipeline->at(index);

		if(instruction->getExecutionStage() != ::WB)
		{
			if(!instruction->execute(this))
			{
				this->pipeline->erase(this->pipeline->begin() + index);	
			}
		}
		else
		{
			this->pipeline->erase(this->pipeline->begin() + index);
		}
	}
}

void ARM::tick()
{
	this->processPipeline();
}

bool ARM::fetchNextInstruction()
{
	uint32_t pc = this->getRegister(::PC);
	this->setRegister(::PC, pc + 4);

	Logger::log("PC: " + String::decToHex(pc));
	Logger::log("PC exec: " + String::decToHex(pc - 8));

	return executeAt(pc);
}

#include <bitset>
#include <iostream>

void ARM::processInstruction(uint32_t instruction)
{
	if(this->getProcessorState() == ::ARM)
	{
		processARMInstruction(instruction);
	}	
	else if(this->getProcessorState() == ::THUMB)
	{
		processTHUMBInstruction((uint16_t) instruction);
	}
}

void ARM::processARMInstruction(uint32_t instruction)
{
	// Delete instruction after memory write to free space.
	Instruction* decodedInstruction = InstructionDecoder::decode(instruction);

	// Print registers (DEBUG)
	this->print();

	if(dynamic_cast<DataProcessingInstruction*>(decodedInstruction))
	{
		DataProcessingInstruction* dataProcessingInstruction = (DataProcessingInstruction*) decodedInstruction;

		Logger::log("Operation Code (OPCODE): " + to_string(dataProcessingInstruction->getOpcode()));
	}
	else if(dynamic_cast<BranchInstruction*>(decodedInstruction))
	{
		BranchInstruction* branchInstruction = (BranchInstruction*) decodedInstruction;

		Logger::log("Branch (With Link: " + to_string(branchInstruction->isWithLink()) + ")");
	}
	else if(dynamic_cast<HalfwordDataTransferInstruction*>(decodedInstruction))
	{
		HalfwordDataTransferInstruction* halfwordDataTransferInstruction = (HalfwordDataTransferInstruction*) decodedInstruction;
	}
	else if(dynamic_cast<SingleDataTransferInstruction*>(decodedInstruction))
	{
		SingleDataTransferInstruction* singleDataTransferInstruction = (SingleDataTransferInstruction*) decodedInstruction;
	}
	else
	{
		Logger::log("Unknown Instruction!");

		exit(0);

		return;
	}

	this->pipeline->push_back(decodedInstruction);
}


void ARM::processTHUMBInstruction(uint16_t instruction)
{
	Logger::log("THUMB Processor Mode not implemented yet!");

	exit(0);
}

void ARM::changeProcessorState(ProcessorState newProcessorState)
{
	if(this->getProcessorState() == newProcessorState)
	{
		return;
	}

	uint32_t cpsr = this->getRegister(::CPSR);

	// Toggle T bit in CPSR
	cpsr ^= 0x20;

	this->setRegister(::CPSR, cpsr);

	Logger::log("Switching to Processor State: " + to_string(newProcessorState));
}

#include <cstring>

bool ARM::executeAt(uint32_t address)
{
	Memory* memory = this->ds->getRAM()->getMemory(address);

	if(memory == NULL)
	{
		Logger::log("Memory address " + String::decToHex(address) + " out of range!");
		exit(0);

		return false;
	}

	address -= memory->getStartAddress();

	uint8_t data[4];
	memcpy(data, memory->getMemory()->get() + address, 4);

	Logger::log("Instruction (HEX): " + String::toHexString(data, 4));

	uint32_t instruction = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];

	this->processInstruction(instruction);
}

void ARM::onFIQ()
{
	uint32_t address = this->getRegister(::PC);

	// Save the address of the next instruction to be executed (plus 4) in R14_fiq
	this->setRegister(::LR, address + 4);

	uint32_t cpsr = this->getRegister(::CPSR);

	// Save the CPSR in SPSR_fiq
	this->setRegister(::SPSR, cpsr);

	// Clear bits 0-4 of CPSR (Mode bits) to 00000
	cpsr &= ~0x11;

	// Set bits 0-4 of CPSR (Mode bits) to 10001
	cpsr |= (1 << 0);
	cpsr |= (1 << 4);

	// Set bits 6-7 of CPSR (F and I bits) to 11
	cpsr |= (1 << 6);
	cpsr |= (1 << 7);

	// Update CPSR
	this->setRegister(::CPSR, cpsr);

	// Set PC to fetch next instruction from memory address 0x1C.
	this->setRegister(::PC, 0x1C);
}

void ARM::onIRQ()
{
	uint32_t address = this->getRegister(::PC);

	// Save address of next instruction to be executed (plus 4) in R14_irq
	this->setRegister(::LR, address + 4);

	uint32_t cpsr = this->getRegister(::CPSR);

	// Save CPSR in SPSR_irq
	this->setRegister(::SPSR, cpsr);

	// Clear bits 0-4 of CPSR (Mode bits) to 00000
	cpsr &= ~0x12;

	// Set bits 0-4 of CPSR (Mode bits) to 10010
	cpsr |= (1 << 1);
	cpsr |= (1 << 4);

	// Set bit 7 of CPSR (I bit) to 1
	cpsr |= (1 << 7);

	// Update CPSR
	this->setRegister(::CPSR, cpsr);

	// Set PC to fetch next instruction from memory address 0x18.
	this->setRegister(::PC, 0x18);
}

ProcessorState ARM::getProcessorState()
{
	return (ProcessorState) ((this->getRegister(::CPSR) >> 5) & 0x01);
}

RAM* ARM::getRAM()
{
	return this->ds->getRAM();
}