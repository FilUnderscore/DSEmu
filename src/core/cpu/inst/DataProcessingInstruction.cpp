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

void DataProcessingInstruction::calculate()
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

		// Logical Left
		if(this->sh == 0x00)
		{
			this->value = (this->rm << shiftValue);
		}
		// Logical Right
		else if(this->sh == 0x01)
		{
			this->value = (this->rm >> shiftValue);
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
			this->calculate();

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
			arm->setRegister((Register) this->getDestinationRegister(), this->operation->getResult());
		
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