#ifndef INCLUDE_MEMORY_HPP_
#define INCLUDE_MEMORY_HPP_

#include "Pointer.hpp"
#include <cstdint>
#include <vector>

using std::vector;

class Memory
{
public:
	Memory();

	Memory(uint32_t startAddress, uint32_t endAddress);
	
	~Memory();

	void addMirroredAddress(uint32_t mirroredAddress);

	uint32_t getStartAddress();

	uint32_t getEndAddress();

	Pointer<uint8_t>* getMemory();

	void clear();

private:
	uint32_t startAddress;
	uint32_t endAddress;

	Pointer<uint8_t>* memory;

	vector<uint32_t>* mirroredAddresses;
};

#endif