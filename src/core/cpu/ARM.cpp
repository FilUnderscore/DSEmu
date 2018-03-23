#include <ARM.hpp>

#include <DS.hpp>

#include <Logger.hpp>

#include <Bits.hpp>

#include <String.hpp>

#include <InstructionDecoder.hpp>

#include <BranchInstruction.hpp>
#include <DataProcessingInstruction.hpp>

ARM::ARM(DS* ds)
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

	//processInstruction(0xfeffffea); //BLA
	//processInstruction(0x0C0000EA);
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
	//executeAt(0x02);
	this->setRegister(::PC, 0x02);
	this->fetchNextInstruction();

	while(true)
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

		if(instruction->getExecutionStage() == ::ID)
		{
			// Begin Instruction Fetch (executeAt(PC + 8))
			Logger::log("Fetch");
			this->fetchNextInstruction();
		}
		
		if(instruction->getExecutionStage() != ::WB)
		{
			instruction->execute(this);
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

	Logger::log("Tick");
}

void ARM::fetchNextInstruction()
{
	uint32_t pc = this->getRegister(::PC);
	this->setRegister(::PC, pc + 4);

	Logger::log("PC: " + String::decToHex(pc));
	Logger::log("PC exec: " + String::decToHex(pc - 8));

	executeAt(pc);
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

	if(dynamic_cast<DataProcessingInstruction*>(decodedInstruction))
	{
		DataProcessingInstruction* dataProcessingInstruction = (DataProcessingInstruction*) decodedInstruction;

		Logger::log("Operation Code (OPCODE): " + to_string(dataProcessingInstruction->getOpcode()));

		// TODO: Pipeline (EX)
		//dataProcessingInstruction->execute(this);
		//dataProcessingInstruction->execute(this);
		//dataProcessingInstruction->execute(this);
	}
	else if(dynamic_cast<BranchInstruction*>(decodedInstruction))
	{
		BranchInstruction* branchInstruction = (BranchInstruction*) decodedInstruction;

		Logger::log("Branch (With Link: " + to_string(branchInstruction->isWithLink()) + ")");
	}
	else
	{
		Logger::log("Unknown Instruction!");

		exit(0);

		return;
	}

	this->pipeline->push_back(decodedInstruction);
}

/*
void ARM::processARMInstruction(uint32_t instruction)
{
	// Little Endian

	//01 03 A0 E3 03 10 A0 E3 02 28 A0 E3 80 30 A0 E3 00 00 00 00 A0 01 00 00 04 13 80 E5 00 20 80 E5 40 32 80 E5 1A 05 A0 E3 1F 10 A0 E3 03 29 A0 E3 B2 10 C0 E0 01 20 52 E2 FC FF FF 1A 50 41 53 53 FE FF FF EA	

	//01 03 A0 E3 - MOV R0, #0x40000000
	//03 10 A0 E3 - MOV R1, #0x3
	//02 28 A0 E3 - MOV R2, #0x20000
	//80 30 A0 E3 - MOV R3, #0x80

	//std::cout << "Binary Instruction: ";
	//std::cout << std::bitset<32>(instruction) << endl;

	// Increment PC by 4 bytes
	this->setRegister(::PC, this->getRegisterValue(::PC) + 4);

	std::cout << "Instruction (BINARY): " << std::bitset<32>(instruction) << endl;

	//[opcode (0-7bits)][register_2 (7-11bits)][type? (11-15bits)][rotate4 (15-19 bits)][register_1 (19-23bits)][immediate8 (23-31 bits)]

	//First 8 bits are opcode
	uint8_t opcode = instruction & 0xFF;

	//20-24 bits are destination register
	uint8_t register_1 = (instruction >> 20) & 0x0F;

	//8-12 bits are 1st operand register
	uint8_t register_2 = instruction >> 8 & 0x0F;

	uint8_t type = instruction >> 12 & 0x0F;

	uint8_t rotate4 = instruction >> 16 & 0x0F;
	uint8_t immediate8 = instruction >> 24 & 0xFF;

	std::cout << "Immediate 8: " << std::bitset<8>(immediate8) << endl;

	uint32_t value = 0;
	
	rotate4 *= 2;

	value = Bits::ror32UBits(immediate8, rotate4);

	Logger::log("Opcode: " + to_string(opcode));
	Logger::log("Register 1: " + to_string(register_1));
	Logger::log("Value: " + to_string(value));
	Logger::log("Register 2: " + to_string(register_2));

	std::cout << endl;

	switch(opcode)
	{
		// ANDEQ
		case 0x00:
		{
			Logger::log("ANDEQ");
			// Zero padding
			// Contrived NOP

			// Executed when Zero flag in CPSR is set.
			bool zero_flag = this->getRegisterValue(::CPSR) & 0x02;

			if(!zero_flag)
			{
				return;
			}

			break;
		}

		// BNE (THUMB)
		case 0x1A:
		{
			Logger::log("BNE");
			break;
		}

		// CMPPL
		case 0x53:
		{
			Logger::log("CMPPL");
			break;
		}

		// STRH
		case 0xE0:
		{
			Logger::log("STRH");
			break;
		}

		// BX (THUMB)
		case 0xE1:
		{
			Logger::log("BX {reg}");

			uint8_t arm_thumb_r1 = (instruction >> 24) & 0x0F;

			this->setRegister(::R12, 0x00);
			uint32_t reg_value = this->getRegisterValue((Register)arm_thumb_r1);

			uint32_t mode_switch = ~reg_value & 0x01;

			Logger::log("REG: " + to_string(arm_thumb_r1));
			Logger::log("REGV: " + to_string(reg_value));
			Logger::log("MS: " + to_string(mode_switch));

			if(mode_switch)
			{
				this->changeProcessorState(::THUMB);
			}
			else
			{
				this->changeProcessorState(::ARM);
			}

			break;
		}

		// SUBS
		case 0xE2:
		{
			Logger::log("SUBS");
			break;
		}

		// MOV
		case 0xE3:
		{
			if(value != 0 && register_2 == 0)
			{
				//MOV r1, #0

				Logger::log("MOV r" + to_string(register_1) + ", " + to_string(value));

				this->setRegister((Register) register_1, value);
			}
			else if(value == 0 && register_2 != 0)
			{
				//MOV r1, r2

				Logger::log("MOV r" + to_string(register_1) + ", " + to_string(register_2));

				this->setRegister((Register) register_1, this->getRegisterValue((Register) register_2));
			}
			else
			{
				Logger::log("Invalid MOV instruction!");
				exit(0);
			}

			break;
		}

		// MOVN
		case 0xFFFF:
		{
			Logger::log("MVN r" + to_string(register_1) + ", " + to_string(register_2));

			// Logical NOT on Register 2 value.
			value = ~this->getRegisterValue((Register) register_2);

			this->setRegister((Register) register_1, value);
		}

		// STR
		case 0xE5:
		{
			Logger::log("STR");
			break;
		}

		// B (THUMB)
		case 0xEA:
		{
			Logger::log("B");

			this->setRegister(::PC, value);

			break;
		}

		default:
		{
			Logger::log("Unknown Opcode: " + String::decToHex(opcode));
			exit(0);
			break;
		}
	}

	std::cout << endl << endl;

	Logger::log("PC: " + to_string(this->getRegisterValue(::PC)));

	this->executeAt(this->getRegisterValue(::PC));
}
*/

void ARM::processTHUMBInstruction(uint16_t instruction)
{
	/*
	 * THUMB bitwise shift and rotate operations (ASR, LSL, LSR, and ROR)
	 *
	if((immediate8 & 0x0F) == 0)
	{
		uint32_t immediate8_hi = immediate8 >> 4 & 0x0F;

		Logger::log("Immediate 8");
		std::cout << "Immediate8: " << std::bitset<8>(immediate8_hi) << endl;
		std::cout << "Rotate4: " << std::bitset<4>(rotate4) << endl;

		if(immediate8 != 0)
		{
			//Logical Shift Right (LSR)
			value = immediate8_hi >> rotate4;

			std::cout << "Value: " << std::bitset<32>(value) << endl;
		}
		else
		{
			//Logical Shift Left (LSL)
			value = immediate8 >> rotate4;
		}
	}
	else
	{

	}
	*/

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

void ARM::executeAt(uint32_t address)
{
	Memory* memory = this->ds->getRAM()->getMemory(address);

	if(memory == NULL)
	{
		Logger::log("Memory address " + String::decToHex(address) + " out of range!");
		exit(0);

		return;
	}

	//this->setRegister(::PC, address);

	address -= memory->getStartAddress();

	//Logger::log("Mem: " + String::toHexString(memory->getMemory()->get(), memory->getMemory()->getSize()));

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
	cpsr |= 0x11;

	// Set bits 6-7 of CPSR (F and I bits) to 11
	cpsr |= 0xC0;

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
	cpsr |= 0x12;

	// Set bit 7 of CPSR (I bit) to 1
	cpsr |= 0x80;

	// Update CPSR
	this->setRegister(::CPSR, cpsr);

	// Set PC to fetch next instruction from memory address 0x18.
	this->setRegister(::PC, 0x18);
}

ProcessorState ARM::getProcessorState()
{
	return (ProcessorState) ((this->getRegister(::CPSR) >> 5) & 0x01);
}