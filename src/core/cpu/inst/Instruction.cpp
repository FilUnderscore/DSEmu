#include <Instruction.hpp>

using namespace CPU;

#include <Bits.hpp>

Instruction::Instruction(uint32_t instruction, uint8_t cond)
{
	this->instruction = instruction;

	this->cond = cond;
}

Instruction::~Instruction()
{

}

uint32_t Instruction::getInstruction()
{
	return this->instruction;
}

uint8_t Instruction::getCondition()
{
	return this->cond;
}