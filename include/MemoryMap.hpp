#ifndef INCLUDE_RAM_HPP_
#define INCLUDE_RAM_HPP_

#include <Memory.hpp>
#include <cstdint>
#include <map>
#include <vector>

using std::map;
using std::vector;

class MemoryMap
{
public:
	MemoryMap();
	~MemoryMap();

	//Pointer<Memory>* getMemoryMap();

	vector<Memory*>* getMemoryMap();

	bool allocate(uint32_t startAddress, uint32_t endAddress);

	bool mirror(uint32_t mirroredAddress, uint32_t address);

	bool load(uint8_t* data, uint32_t dataLength, uint32_t destAddress = 0x00);

	bool write(uint32_t destAddress, uint8_t* data, uint32_t dataLength);

	bool copy(uint32_t sourceAddress, uint32_t destAddress, uint32_t length);

	Memory* getMemory(uint32_t address);

	uint32_t getTotalRAMSize();

	Pointer<uint8_t>* getMemory();

	void print();

private:
	//Pointer<Memory>* memoryMap;
	vector<Memory*>* memoryMap;
};

#endif