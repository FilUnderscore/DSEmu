#include <SUBOperation.hpp>

#include <ARM.hpp>
#include <DataProcessingInstruction.hpp>

using namespace CPU;

SUBOperation::SUBOperation() : Operation(::SUB, ::ARITHMETIC)
{

}

SUBOperation::~SUBOperation()
{

}

void SUBOperation::execute()
{
	uint32_t rn = this->arm->getRegister((Register) this->instruction->getFirstOperandRegister());

	uint32_t op2 = this->instruction->getValue();

	Logger::log("RN: " + to_string(rn));
	Logger::log("OP2: " + to_string(op2));

	this->result = rn - op2;

	if(this->result == -1)
	{
		this->result = 0;
	}
}

void SUBOperation::memory()
{

}