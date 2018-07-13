#include "include\BranchInstruction.hpp"

#include "include\ARM.hpp"

#include "include\String.hpp"

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

bool BranchInstruction::execute(CPU::ARM* arm)
{
	if(!Instruction::execute(arm))
	{
		Logger::log("BranchInstruction cancelled.");

		arm->lockPipeline(false);

		return false;
	}

	switch(this->executionStage)
	{
		case ::ID:
		{
			// Cause delay in Pipeline until Branch occurs
			arm->lockPipeline(true);

			break;
		}

		case ::EX:
		{	
			uint32_t pc = arm->getRegister(::PC);

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
			arm->setRegister(::PC, this->offset);

			// Allow pipeline to continue.
			arm->lockPipeline(false);

			break;
		}

		default:
		{
			break;
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