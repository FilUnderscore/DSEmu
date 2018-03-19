#include <Memory.hpp>

#include <cstring>

#include <Logger.hpp>
#include <String.hpp>

Memory::Memory()
{
	this->memoryType = MemoryType::UNDEFINED;

	this->startAddress = 0x00;

	this->endAddress = 0x00;

	this->memorySize = 0x00;

	this->memory = NULL;
}

Memory::Memory(uint32_t startAddress, uint32_t endAddress) : Memory(MemoryType::UNDEFINED, startAddress, endAddress)
{

}

Memory::Memory(MemoryType type, uint32_t startAddress, uint32_t endAddress)
{
	this->memoryType = type;

	this->startAddress = startAddress;

	this->endAddress = endAddress;

	this->memory = new uint8_t[this->memorySize = (endAddress - startAddress)]();
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

uint8_t* Memory::getMemory()
{
	return this->memory;
}

uint32_t Memory::getMemorySize()
{
	return this->memorySize;
}

void Memory::clear()
{
	memset(this->memory, 0, this->memorySize);
}