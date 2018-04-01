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
			uint32_t cpsr = arm->getRegister(::CPSR);

			// Set carry flag depending on Bit 31 of RM
			cpsr |= ((rm >> 31) << 29);
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
			uint32_t result = this->operation->getResult();

			arm->setRegister((Register) this->getDestinationRegister(), result);
		
			if(this->s == 0x01)
			{
				// Set condition codes in CPSR
				uint32_t cpsr = arm->getRegister(::CPSR);

				if(this->operation->getOptype() == ::LOGICAL)
				{
					//Bit 31 (Negative flag)
					// Set to Bit 31 of the result.
					cpsr |= ((result >> 31) << 31);

					// Bit 30 (Zero flag)
					// Set Zero flag if the result is 0.
					cpsr |= ((result == 0x00) << 30);

					// TODO: Bit 29 and Bit 28
				}
				else if(this->operation->getOptype() == ::ARITHMETIC)
				{
					// Bit 31 (Negative flag)
					// Set to Bit 31 of the result.
					cpsr |= ((result >> 31) << 31);

					// Bit 30 (Zero flag)
					// Set Zero flag if the result is 0.
					cpsr |= ((result == 0x00) << 30);

					// Bit 29 (Carry flag)
					// Set Carry flag of carry out bit 31 in ALU (TODO)
					cpsr |= ((result >> 31) << 29);

					if(this->rd != ::PC)
					{
						// Bit 28 (Overflow flag)
						// Set Overflow flag if RD is not R15 and bit 31 of result will set the CPSR if the result is overflow.
						cpsr |= ((result >> 31) << 28);
					}
				}

				arm->setRegister(::CPSR, cpsr);
			}

			break;
		}

		default:
		{
			break;
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