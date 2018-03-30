#ifndef INCLUDE_RAM_HPP_
#define INCLUDE_RAM_HPP_

#include <Memory.hpp>
#include <cstdint>

namespace DS
{
	class DSSystem;
}

using DS::DSSystem;

class RAM
{
public:
	RAM(DSSystem* ds);
	~RAM();

	Pointer<Memory>* getMemoryMap();

	bool load(uint8_t* data, uint32_t dataLength, uint32_t destAddress = 0x00);

	bool write(uint32_t destAddress, uint8_t* data);

	bool copy(uint32_t sourceAddress, uint32_t destAddress, uint32_t length);

	Memory* getMemory(uint32_t address);

	uint32_t getTotalRAMSize();

	Pointer<uint8_t>* getRAM();

	void print();

private:
	Pointer<Memory>* memoryMap;
};

#endif