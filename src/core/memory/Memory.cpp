#include <Memory.hpp>

#include <cstring>

#include <Logger.hpp>
#include <String.hpp>

Memory::Memory() : Memory(::UNDEFINED, 0, 0)
{
	
}

Memory::Memory(uint32_t startAddress, uint32_t endAddress) : Memory(MemoryType::UNDEFINED, startAddress, endAddress)
{

}

Memory::Memory(MemoryType type, uint32_t startAddress, uint32_t endAddress)
{
	this->memoryType = type;

	this->startAddress = startAddress;

	this->endAddress = endAddress;

	this->memory = new Pointer<uint8_t>(endAddress - startAddress);
}

Memory::~Memory()
{

}

MemoryType Memory::getMemoryType()
{
	return this->memoryType;
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