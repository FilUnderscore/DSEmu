#include <DataProcessingInstruction.hpp>

#include <Bits.hpp>
#include <ARM.hpp>
#include <limits>

using namespace CPU;

using std::numeric_limits;

DataProcessingInstruction::DataProcessingInstruction(uint32_t instruction, uint8_t cond, uint8_t opcode, uint8_t s, uint8_t rd, uint8_t rn, uint8_t rotate4, uint8_t immediate8, uint8_t shift, uint8_t rs, uint8_t sh, uint8_t rm) : Instruction(instruction, cond)
{
	this->opcode = opcode;

	this->s = s;

	this->rd = rd;
	this->rn = rn;

	this->rotate4 = rotate4;
	this->immediate8 = immediate8;

	this->shift = shift;
	this->rs = rs;
	this->sh = sh;
	this->rm = rm;
}

DataProcessingInstruction::~DataProcessingInstruction()
{

}

void DataProcessingInstruction::calculate(ARM* arm)
{
	if(((this->instruction >> 25) & 0x01) == 0x00)
	{
		uint32_t shiftValue;

		if(((this->instruction >> 4) & 0x01) == 0x00)
		{
			shiftValue = this->shift;
		}
		else
		{
			// Shift amount specified in bottom byte of RS
			shiftValue = this->rs & 0x0F;
		}

		uint32_t rm = arm->getRegister((Register) this->rm);

		// Logical Left
		if(this->sh == 0x00)
		{
			this->value = (rm << shiftValue);
		}
		// Logical Right
		else if(this->sh == 0x01)
		{
			this->value = (rm >> shiftValue);
		}
		// Arithmetic Right
		else if(this->sh == 0x02)
		{

		}
		//Rotate Right
		else if(this->sh == 0x03)
		{
			this->value = Bits::ror32UBits(rm, shiftValue);
		}
	}
	else
	{
		this->value = Bits::ror32UBits(this->immediate8, (this->rotate4 * 2));
	}
}

bool DataProcessingInstruction::execute(ARM* arm)
{
	if(!Instruction::execute(arm))
	{
		Logger::log("DataProcessingInstruction cancelled.");

		return false;
	}

	switch(this->executionStage)
	{
		case ::EX:
		{
			this->calculate(arm);

			this->operation = Operation::getOperation((Opcode) this->opcode);

			this->operation->set(arm, this);

			this->operation->execute();
		
			break;
		}

		case ::MEM:
		{
			this->operation->memory();
		
			break;
		}

		case ::WB:
		{
			// Converted to uint32_t, int64_t is used for flag setting and it has a higher max value than an int32_t.
			int64_t opResult = this->operation->getResult();
			uint32_t result = (uint32_t) opResult;

			arm->setRegister((Register) this->getDestinationRegister(), result);
		
			if(this->s == 0x01)
			{
				// Set condition codes in CPSR

				uint32_t cpsr = arm->getRegister(::CPSR);

				// Bit 31 (Negative flag)
				if(opResult < 0)
				{
					// Set Bit 31 to 1
					cpsr |= (1 << 31);
				}
				else
				{
					// Set Bit 31 to 0
					cpsr |= (0 << 31);
				}

				// Bit 30 (Zero flag)
				if(result == 0x00)
				{
					// Set Bit 30 to 1
					cpsr |= (1 << 30);
				}
				else
				{
					// Set Bit 30 to 0
					cpsr |= (0 << 30);
				}

				/*
				 * TODO: Proper implementation
				 *
				// Bit 29 (Unsigned Overflow) Carry Flag
				if(opResult > numeric_limits<uint32_t>::max())
				{
					// Set Bit 29 to 1
					cpsr |= (1 << 29);
				}
				else
				{
					// Bit 28 (Signed) Overflow Flag
					// Inside Carry Flag if statement, because max value of uint32_t is greater than int32_t.
					if(opResult > numeric_limits<int32_t>::max())
					{
						// Set Bit 28 to 1
						cpsr |= (1 << 28);
					}
					else
					{
						// Set Bit 28 to 0
						cpsr |= (0 << 28);
					}

					// Set Bit 29 to 0
					cpsr |= (0 << 29);
				}
				*/

				arm->setRegister(::CPSR, cpsr);
			}

			break;
		}

		default:
		{
			return false;
		}
	}

	return true;
}

uint8_t DataProcessingInstruction::getOpcode()
{
	return this->opcode;
}

uint8_t DataProcessingInstruction::getDestinationRegister()
{
	return this->rd;
}

uint8_t DataProcessingInstruction::getFirstOperandRegister()
{
	return this->rn;
}

uint32_t DataProcessingInstruction::getValue()
{
	return this->value;
}