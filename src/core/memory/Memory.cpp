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
}

Memory::~Memory()
{
	Logger::log("Memory destroyed.");
}

uint32_t Memory::getStartAddress()
{
	return this->startAddress;
}

uint32_t Memory::getEndAddress()
{
	return this->endAddress;
}

Pointer<uint8_t>* Memory::getMemory()
{
	return this->memory;
}

void Memory::clear()
{
	memset(this->memory, 0, this->memory->getSize());
}