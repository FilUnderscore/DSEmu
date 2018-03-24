#include <MOVOperation.hpp>

#include <Logger.hpp>

#include <Register.hpp>

#include <ARM.hpp>

#include <DataProcessingInstruction.hpp>

using namespace CPU;

MOVOperation::MOVOperation() : Operation(::MOV)
{

}


MOVOperation::~MOVOperation()
{

}

void MOVOperation::execute()
{
	if(this->instruction->getValue() != 0 && this->instruction->getFirstOperandRegister() == 0)
	{
		//MOV r1, #0

		Logger::log("MOV r" + to_string(this->instruction->getDestinationRegister()) + ", " + to_string(this->instruction->getValue()));

		this->result = this->instruction->getValue();
	}
	else if(this->instruction->getValue() == 0 && this->instruction->getFirstOperandRegister() != 0)
	{
		//MOV r1, r2

		Logger::log("MOV r" + to_string(this->instruction->getDestinationRegister()) + ", " + to_string(this->instruction->getFirstOperandRegister()));

		this->result = this->arm->getRegister((Register) this->instruction->getFirstOperandRegister());
	}
	else
	{
		Logger::log("Invalid MOV instruction!");
		Logger::log("RD: " + to_string(this->instruction->getDestinationRegister()));
		Logger::log("RN: " + to_string(this->instruction->getFirstOperandRegister()));
		Logger::log("VAL: " + to_string(this->instruction->getValue()));
		exit(0);
	}
}

void MOVOperation::memory()
{

}