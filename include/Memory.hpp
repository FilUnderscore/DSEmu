#ifndef INCLUDE_MEMORY_HPP_
#define INCLUDE_MEMORY_HPP_

#include "Pointer.hpp"
#include <cstdint>
#include <vector>
#include <functional>

using std::function;
using std::vector;

class Memory
{
public:
	Memory();

	Memory(uint32_t startAddress, uint32_t endAddress);
	
	Memory(uint32_t startAddress, uint32_t endAddress, std::function<void()> func);

	~Memory();

	void addMirroredAddress(uint32_t mirroredAddress);

	void executeFunction();

	uint32_t getStartAddress();

	uint32_t getEndAddress();

	std::function<void()> getFunction();

	Pointer<uint8_t>* getMemory();

	void clear();

private:
	uint32_t startAddress;
	uint32_t endAddress;

	std::function<void()> func;

	Pointer<uint8_t>* memory;

	vector<uint32_t>* mirroredAddresses;
};

#endif