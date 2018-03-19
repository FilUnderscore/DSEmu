#ifndef INCLUDE_MEMORY_HPP_
#define INCLUDE_MEMORY_HPP_

#include "MemoryType.hpp"

#include <cstdint>

using namespace std;

class Memory
{
public:
	Memory();

	Memory(uint32_t startAddress, uint32_t endAddress);
	Memory(MemoryType type, uint32_t startAddress, uint32_t endAddress);
	
	~Memory();

	MemoryType getMemoryType();

	uint32_t getStartAddress();

	uint32_t getEndAddress();

	uint8_t* getMemory();

	uint32_t getMemorySize();

	void clear();

private:
	MemoryType memoryType;

	uint32_t startAddress;
	uint32_t endAddress;

	uint8_t* memory;

	uint32_t memorySize;
};

#endif