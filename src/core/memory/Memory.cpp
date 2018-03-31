#include <Memory.hpp>

#include <Logger.hpp>
#include <String.hpp>
#include <cstring>

Memory::Memory() : Memory(0, 0)
{
	
}

Memory::Memory(uint32_t startAddress, uint32_t endAddress)
{
	this->startAddress = startAddress;

	this->endAddress = endAddress;

	this->memory = new Pointer<uint8_t>(endAddress - startAddress);

	this->mirroredAddresses = new vector<uint32_t>();
}

Memory::Memory(uint32_t startAddress, uint32_t endAddress, std::function<void()> func) : Memory(startAddress, endAddress)
{
	this->func = func;
}

Memory::~Memory()
{
	Logger::log("Memory destroyed.");
}

void Memory::addMirroredAddress(uint32_t mirroredAddress)
{
	this->mirroredAddresses->push_back(mirroredAddress);
}

void Memory::executeFunction()
{
	if(this->func)
	{
		this->func();
	}
}

uint32_t Memory::getStartAddress()
{
	return this->startAddress;
}

uint32_t Memory::getEndAddress()
{
	return this->endAddress;
}

std::function<void()> Memory::getFunction()
{
	return this->func;	
}

Pointer<uint8_t>* Memory::getMemory()
{
	return this->memory;
}

void Memory::clear()
{
	memset(this->memory, 0, this->memory->getSize());
}