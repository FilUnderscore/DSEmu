#include <Operation.hpp>

using namespace CPU;

#include <ARM.hpp>

#include <MOVOperation.hpp>
#include <BOperation.hpp>

#include <DataProcessingInstruction.hpp>

map<Opcode, Operation*(*)()>* Operation::operations;

Operation::Operation()
{
	this->arm = NULL;
	this->instruction = NULL;
}

Operation::Operation(Opcode opcode) : Operation()
{
	this->opcode = opcode;
}

Operation::~Operation()
{

}

void Operation::set(ARM* arm, DataProcessingInstruction* instruction)
{
	if(this->arm != NULL || this->instruction != NULL)
	{
		Logger::log("Operation cannot be set again!");
		exit(0);
		return;
	}

	this->arm = arm;
	this->instruction = instruction;
}

void Operation::execute()
{
	Logger::log("Operation execution.");
}

void Operation::memory()
{
	Logger::log("Memory access.");
}

void Operation::write()
{
	Logger::log("Write back from memory to register.");
}

Opcode Operation::getOpcode()
{
	return this->opcode;
}

void Operation::init()
{
	if(operations != NULL)
	{
		return;
	}

	operations = new map<Opcode, Operation*(*)()>;

	operations->insert(make_pair(::MOV, &createInstance<MOVOperation>));
}

Operation* Operation::getOperation(Opcode opcode)
{
	if(operations->find(opcode) == operations->end())
	{
		Logger::log("Opcode " + to_string(opcode) + " not found!");
		exit(0);
		return NULL;
	}

	return operations->find(opcode)->second();
}