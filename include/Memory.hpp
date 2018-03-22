#ifndef INCLUDE_MEMORY_HPP_
#define INCLUDE_MEMORY_HPP_

#include "MemoryType.hpp"

#include <cstdint>

using namespace std;

#include "Pointer.hpp"

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

	Pointer<uint8_t>* getMemory();

	void clear();

private:
	MemoryType memoryType;

	uint32_t startAddress;
	uint32_t endAddress;

	Pointer<uint8_t>* memory;
};

#endif