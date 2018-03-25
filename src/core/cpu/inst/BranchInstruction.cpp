#include <BranchInstruction.hpp>

#include <ARM.hpp>

#include <String.hpp>

using namespace CPU;

BranchInstruction::BranchInstruction(uint32_t instruction, uint8_t cond, uint8_t l, int32_t offset) : Instruction(instruction, cond)
{
	this->l = l;
	this->offset = offset;

	this->calculate();
}

BranchInstruction::~BranchInstruction()
{

}

void BranchInstruction::calculate()
{
	this->offset <<= 8;
	this->offset /= 64;

	Logger::log("Branch to memory address: " + String::decToHex(this->offset));
}

bool BranchInstruction::execute(ARM* arm)
{
	if(!Instruction::execute(arm))
	{
		Logger::log("Branch cancelled");

		return false;
	}

	switch(this->executionStage)
	{
		case ::EX:
		{	
			uint32_t pc = arm->getRegister(::PC);

			Logger::log("PROGRAM COUNT: " + to_string(pc));

			// Increment due to pre-fetch
			pc += 4;
			pc += this->offset;

			this->offset = pc;

			break;
		}

		case ::MEM:
		{
			break;
		}

		case ::WB:
		{
			// TODO: Hold CPU for Branch instruction to occur, 3 cycles.

			Logger::log("OFF: " + to_string(this->offset));

			arm->setRegister(::PC, this->offset);

			Logger::log("OFF2: " + to_string(this->offset));

			break;
		}

		default:
		{
			return false;
		}
	}

	return true;
}

bool BranchInstruction::isWithLink()
{
	return this->l;
}

int32_t BranchInstruction::getOffset()
{
	return this->offset;
}