#include <Instruction.hpp>

using namespace CPU;

#include <Bits.hpp>

Instruction::Instruction(uint32_t instruction, Operation* operation, uint8_t cond, uint8_t opcode, uint8_t s, uint8_t rd, uint8_t rn, uint8_t rotate4, uint8_t immediate8, uint8_t shift, uint8_t rs, uint8_t sh, uint8_t rm)
{
	this->instruction = instruction;

	this->operation = operation;

	this->cond = cond;

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

Instruction::~Instruction()
{

}

void Instruction::calculate()
{
	this->value = Bits::ror32UBits(this->immediate8, (this->rotate4 * 2));
}

uint32_t Instruction::getInstruction()
{
	return this->instruction;
}

Operation* Instruction::getOperation()
{
	return this->operation;
}

uint8_t Instruction::getOpcode()
{
	return this->opcode;
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