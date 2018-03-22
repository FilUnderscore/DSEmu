#include <Instruction.hpp>

using namespace CPU;

#include <Bits.hpp>

Instruction::Instruction(uint32_t instruction, uint8_t cond)
{
	this->instruction = instruction;

	this->cond = (Condition) cond;

	this->executionStage = ::ID;
}

Instruction::~Instruction()
{

}

bool Instruction::execute(ARM* arm)
{
	this->executionStage = (InstructionExecutionStage) ((int)this->executionStage + 1);

	if(this->executionStage == ::EX)
	{
		// Check conditions
		switch(this->cond)
		{
			case ::EQ:
			{

			}

			case ::NE:
			{

			}

			case ::CS:
			{

			}

			case ::CC:
			{

			}

			case ::MI:
			{

			}

			case ::PL:
			{

			}

			case ::VS:
			{

			}

			case ::VC:
			{

			}

			case ::HI:
			{

			}

			case ::LS:
			{

			}

			case ::GE:
			{

			}

			case ::LT:
			{

			}

			case ::GT:
			{

			}

			case ::LE:
			{

			}

			case ::AL:
			{
				return true;
			}

			case ::NV:
			{

			}

			default:
			{
				return false;
			}
		}
	}

	return true;
}

uint32_t Instruction::getInstruction()
{
	return this->instruction;
}

Condition Instruction::getCondition()
{
	return this->cond;
}

InstructionExecutionStage Instruction::getExecutionStage()
{
	return this->executionStage;
}