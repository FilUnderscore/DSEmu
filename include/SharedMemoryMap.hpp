#ifndef INCLUDE_SHAREDMEMORYMAP_HPP_
#define INCLUDE_SHAREDMEMORYMAP_HPP_

#include "MemoryMap.hpp"

class SharedMemoryMap : public MemoryMap
{
public:
	static SharedMemoryMap* getInstance();

	Memory* getMemory(uint32_t address);
	
private:
	static SharedMemoryMap* instance;

	SharedMemoryMap();
	~SharedMemoryMap();
};

#endif