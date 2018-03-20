#include <Instruction.hpp>

using namespace CPU;

#include <Bits.hpp>

Instruction::Instruction(uint8_t opcode, uint8_t type, uint8_t rd, uint8_t rn, uint8_t rotate4, uint8_t immediate8)
{
	this->opcode = opcode;
	this->type = type;
	this->rd = rd;
	this->rn = rn;
	this->rotate4 = rotate4;
	this->immediate8 = immediate8;

	this->calculate();
}

Instruction::~Instruction()
{

}

void Instruction::calculate()
{
	this->value = Bits::ror32UBits(this->immediate8, (this->rotate4 * 2));
}

uint8_t Instruction::getOpcode()
{
	return this->opcode;
}

uint8_t Instruction::getType()
{
	return this->type;
}

uint8_t Instruction::getDestinationRegister()
{
	return this->rd;
}

uint8_t Instruction::getFirstOperandRegister()
{
	return this->rn;
}

uint32_t Instruction::getValue()
{
	return this->value;
}