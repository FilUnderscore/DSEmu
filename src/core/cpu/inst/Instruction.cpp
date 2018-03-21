#include <Instruction.hpp>

using namespace CPU;

#include <Bits.hpp>

Instruction::Instruction(uint32_t instruction, uint8_t cond)
{
	this->instruction = instruction;

	this->cond = cond;

	this->executionStage = ::ID;
}

Instruction::~Instruction()
{

}

void Instruction::execute(ARM* arm)
{
	this->executionStage = (InstructionExecutionStage) ((int)this->executionStage + 1);
}

uint32_t Instruction::getInstruction()
{
	return this->instruction;
}

uint8_t Instruction::getCondition()
{
	return this->cond;
}

InstructionExecutionStage Instruction::getExecutionStage()
{
	return this->executionStage;
}