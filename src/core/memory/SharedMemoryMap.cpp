#include "include\SharedMemoryMap.hpp"

#include "include\Logger.hpp"

SharedMemoryMap* SharedMemoryMap::instance = NULL;

SharedMemoryMap::SharedMemoryMap() : MemoryMap()
{

}

SharedMemoryMap::~SharedMemoryMap()
{

}

SharedMemoryMap* SharedMemoryMap::getInstance()
{
	if(instance == NULL)
	{
		instance = new SharedMemoryMap();
	}

	return instance;
}

Memory* SharedMemoryMap::getMemory(uint32_t address)
{
	for(uint32_t index = 0; index < this->memoryMap->size(); index++)
	{
		Memory* memory = this->memoryMap->at(index);

		if(address >= memory->getStartAddress() && address <= memory->getEndAddress())
		{
			return memory;
		}
	}

	return NULL;
}