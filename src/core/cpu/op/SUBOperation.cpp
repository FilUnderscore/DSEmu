#include <SUBOperation.hpp>

#include <ARM.hpp>

#include <DataProcessingInstruction.hpp>

using namespace CPU;

SUBOperation::SUBOperation() : Operation(::SUB)
{

}

SUBOperation::~SUBOperation()
{

}

void SUBOperation::execute()
{
	uint32_t rn = this->arm->getRegister((Register) this->instruction->getFirstOperandRegister());

	uint32_t op2 = this->instruction->getValue();

	this->result = rn - op2;
}

void SUBOperation::memory()
{

}