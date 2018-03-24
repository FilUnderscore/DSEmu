#include <BranchInstruction.hpp>

using namespace CPU;

BranchInstruction::BranchInstruction(uint32_t instruction, uint8_t cond, uint8_t l, uint32_t offset) : Instruction(instruction, cond)
{
	this->l = l;
	this->offset = offset;

	this->calculate();
}

BranchInstruction::~BranchInstruction()
{

}

void BranchInstruction::calculate()
{
	this->offset <<= 8;
	this->offset /= 64;

	Logger::log("OFFSET: " + to_string(this->offset));
}

bool BranchInstruction::execute(ARM* arm)
{
	Logger::log("Branch not implemented.");

	return false;
}

bool BranchInstruction::isWithLink()
{
	return this->l;
}

uint32_t BranchInstruction::getOffset()
{
	return this->offset;
}