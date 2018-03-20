#include <BOperation.hpp>

#include <Register.hpp>

#include <ARM.hpp>

#include <Logger.hpp>

BOperation::BOperation() : Operation(::B)
{

}

BOperation::~BOperation()
{

}	

#include <iostream>

#include <bitset>

void BOperation::execute()
{
	// 24 bit offset
	uint32_t offset = (this->instruction->getInstruction() >> 0) & 0xFFFFFF;
	
	cout << "OFF: " << bitset<32>(offset);
	
	//offset <<= 2;
	//offset &= 0xFFFFFF;

	cout << "OFF: " << bitset<32>(offset);

	//int32_t mask = 1u << (24 - 1);

	// Sign-extend offset with mask to signed 32-bit integer.
	//int32_t address = (offset ^ mask) - mask;

	int32_t address = offset;
	address <<= 8;
	address /= 64;

	Logger::log("Address: " + to_string(address));
}

void BOperation::memory()
{

}

void BOperation::write()
{

}