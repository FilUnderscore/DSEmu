#include <CMPOperation.hpp>

#include <ARM.hpp>
#include <DataProcessingInstruction.hpp>

using namespace CPU;

CMPOperation::CMPOperation() : Operation(::CMP)
{

}

CMPOperation::~CMPOperation()
{

}

void CMPOperation::execute()
{
	this->result = 0;
}

void CMPOperation::memory()
{

}