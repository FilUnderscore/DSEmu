#include <DataProcessingInstruction.hpp>

using namespace CPU;

#include <Bits.hpp>

#include <ARM.hpp>

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
		Logger::log("No exec");

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

				// Bit 30 (Zero flag)
				if(result == 0x00)
				{
					// Set Bit 30 to 1
					cpsr |= 1 << 0x40000000;
				}
				else
				{
					// Set Bit 30 to 0
					cpsr |= 0 << 0x40000000;
				}

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