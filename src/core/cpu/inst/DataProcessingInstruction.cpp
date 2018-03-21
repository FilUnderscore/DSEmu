#include <DataProcessingInstruction.hpp>

using namespace CPU;

#include <Bits.hpp>

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

	this->calculate();
}

DataProcessingInstruction::~DataProcessingInstruction()
{

}

void DataProcessingInstruction::calculate()
{
	// Logical Left
	if(this->sh = 0x00)
	{

	}
	// Logical Right
	else if(this->sh = 0x01)
	{

	}
	// Arithmetic Right
	else if(this->sh = 0x02)
	{

	}
	//Rotate Right
	else if(this->sh = 0x03)
	{

	}

	this->value = Bits::ror32UBits(this->immediate8, (this->rotate4 * 2));
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