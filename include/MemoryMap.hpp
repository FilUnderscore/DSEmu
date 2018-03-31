#ifndef INCLUDE_MEMORYMAP_HPP_
#define INCLUDE_MEMORYMAP_HPP_

#include <Memory.hpp>
#include <cstdint>
#include <map>
#include <vector>
#include <functional>

using std::function;
using std::map;
using std::vector;

class MemoryMap
{
public:

	/**
	  * CLASS
	  */

	MemoryMap();
	~MemoryMap();

	bool allocate(uint32_t startAddress, uint32_t endAddress, std::function<void()> func = [](){});
	bool mirror(uint32_t mirroredAddress, uint32_t address);
	bool load(uint8_t* data, uint32_t dataLength, uint32_t destAddress = 0x00);
	bool write(uint32_t destAddress, uint8_t* data, uint32_t dataLength);
	bool copy(uint32_t sourceAddress, uint32_t destAddress, uint32_t length);

	void print();

	virtual Memory* getMemory(uint32_t address);

	vector<Memory*>* getMemoryMap();

	Pointer<uint8_t>* getMemory();

	uint32_t getTotalSize();

protected:
	vector<Memory*>* memoryMap;
};

#endif