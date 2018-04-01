#include <Instruction.hpp>

#include <Bits.hpp>
#include <ARM.hpp>
#include <Logger.hpp>

Instruction::Instruction(uint32_t instruction, uint8_t cond)
{
	this->instruction = instruction;

	this->cond = (Condition) cond;

	this->executionStage = ::IF;
}

Instruction::~Instruction()
{

}

bool Instruction::execute(ARM* arm)
{	
	this->executionStage = (InstructionExecutionStage) ((int)this->executionStage + 1);

	if(this->executionStage == ::EX)
	{
		uint32_t cpsr = arm->getRegister(::CPSR);

		uint8_t negative_flag = (cpsr >> 31) & 0x01;
		uint8_t zero_flag = (cpsr >> 30) & 0x01;
		uint8_t carry_flag = (cpsr >> 29) & 0x01;
		uint8_t overflow_flag = (cpsr >> 28) & 0x01;

		Logger::log("COND: " + to_string(cond));

		// Check conditions
		switch(this->cond)
		{
			case ::EQ:
			{
				// Zero flag is not set.
				if(!zero_flag)
				{
					return false;
				}

				break;
			}

			case ::NE:
			{
				// Zero flag is not clear.
				if(zero_flag)
				{
					return false;
				}

				break;
			}

			case ::CS:
			{
				// Carry flag is not set.
				if(!carry_flag)
				{
					return false;
				}

				break;
			}

			case ::CC:
			{
				// Carry flag is not clear.
				if(carry_flag)
				{
					return false;
				}

				break;
			}

			case ::MI:
			{
				// Negative flag is not set.
				if(!negative_flag)
				{
					return false;
				}

				break;
			}

			case ::PL:
			{
				// Negative flag is not clear.
				if(negative_flag)
				{
					return false;
				}

				break;
			}

			case ::VS:
			{
				// Overflow flag is not set.
				if(!overflow_flag)
				{
					return false;
				}

				break;
			}

			case ::VC:
			{
				// Overflow flag is not clear.
				if(overflow_flag)
				{
					return false;
				}

				break;
			}

			case ::HI:
			{
				// Carry is not set and Z is not clear.
				if(!carry_flag || zero_flag)
				{
					return false;
				}

				break;
			}

			case ::LS:
			{
				// Carry flag is not set.
				if(!carry_flag)
				{
					return true;
				}

				// OR

				// Zero flag is set.
				if(zero_flag)
				{
					return true;
				}

				return false;
			}

			case ::GE:
			{
				// Negative flag is not equal to Overflow flag
				if(negative_flag != overflow_flag)
				{
					return false;
				}

				break;
			}

			case ::LT:
			{
				// Negative flag is equal to Overflow flag
				if(negative_flag == overflow_flag)
				{
					return false;
				}

				break;
			}

			case ::GT:
			{
				// Zero flag is not clear or Negative flag is not equal to Overflow flag
				if(zero_flag || negative_flag != overflow_flag)
				{
					return false;
				}

				break;
			}

			case ::LE:
			{
				// Zero flag is set.
				if(zero_flag)
				{
					return true;
				}

				// OR

				// Negative flag is not equal to Overflow flag.
				if(negative_flag != overflow_flag)
				{
					return true;
				}

				return false;
			}

			case ::AL:
			{
				return true;
			}

			case ::NV:
			{
				return false;
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