#include <MemoryMap.hpp>

#include <Logger.hpp>
#include <SharedMemoryMap.hpp>
#include <String.hpp>
#include <cstring>

using namespace std;

MemoryMap::MemoryMap()
{
	// 4194304 bits
	//this->memory = new uint8_t[this->memorySize = 0x400000];

	//this->memoryMap = new Pointer<Memory>(25);
	this->memoryMap = new vector<Memory*>();

	// ARM 9
	//(*this->memoryMap)[1] = Memory(0xFFFF0000, 0xFFFF7FFF); // BIOS - 0x7FFF = 0x8000 (32KiB)
	//(*this->memoryMap)[2] = Memory(0x00000000, 0x00007FFF); // ITCM - 0x7FFF = 0x8000 (32KiB)
	//(*this->memoryMap)[3] = Memory(0x0B000000, 0x0B003FFF); // DTCM - 0x3FFF = 0x4000 (16KiB)

	// Shared between ARM 9 and ARM 7 (mirror is 0x02400000 - 0x027FFFFF)
	//(*this->memoryMap)[0] = Memory(0x02000000, 0x023FFFFF); // Main Memory - 0x3FFFFF = 0x400000 (4MiB)

	//one is (ARM 9 send / ARM 7 receive) and one is (ARM 7 send / ARM 9 receive)
	//(*this->memoryMap)[4] = Memory(0x03000000, 0x03003FFF); // Shared WRAM Bank 0 - 0x3FFF = 0x4000 (16KiB)
	//(*this->memoryMap)[5] = Memory(0x03004000, 0x03007FFF); // Shared WRAM Bank 1 - 0x3FFF = 0x4000 (16KiB)

	// ARM 7
	//(*this->memoryMap)[6] = Memory(0x00000000, 0x00003FFF); // BIOS - 0x3FFF = 0x4000 (16KiB)
	//(*this->memoryMap)[7] = Memory(0x03800000, 0x0380FFFF); // IWRAM - 0xFFFF - 0x10000 (64KiB)

	// VRAM (Video RAM)
	//(*this->memoryMap)[8] = Memory(0x07000000, 0x070003FF); // Main OAM - 0x3FF = 0x400 (1KiB)
	//(*this->memoryMap)[9] = Memory(0x07000400, 0x070007FF); // Sub OAM - 0x3FF = 0x400 (1KiB)
	//(*this->memoryMap)[10] = Memory(0x05000000, 0x050003FF); // Main Palette - 0x3FF = 0x400 (1KiB)
	//(*this->memoryMap)[11] = Memory(0x05000400, 0x050007FF); // Sub Palette - 0x3FF = 0x400 (1KiB)
	//(*this->memoryMap)[12] = Memory(0x06800000, 0x0681FFFF); // Bank A - 0x1FFFF = 0x20000 (128KiB)
	//(*this->memoryMap)[13] = Memory(0x06820000, 0x0683FFFF); // Bank B - 0x1FFFF = 0x20000 (128KiB)
	//(*this->memoryMap)[14] = Memory(0x06840000, 0x0685FFFF); // Bank C - 0x1FFFF = 0x20000 (128KiB)
	//(*this->memoryMap)[15] = Memory(0x06860000, 0x0687FFFF); // Bank D - 0x1FFFF = 0x20000 (128KiB)
	//(*this->memoryMap)[16] = Memory(0x06880000, 0x0688FFFF); // Bank E - 0xFFFF = 0x10000 (64KiB)
	//(*this->memoryMap)[17] = Memory(0x06890000, 0x06893FFF); // Bank F - 0x3FFF = 0x4000 (16KiB)
	//(*this->memoryMap)[18] = Memory(0x06894000, 0x06897FFF); // Bank G - 0x3FFF = 0x4000 (16KiB)
	//(*this->memoryMap)[19] = Memory(0x06898000, 0x0689FFFF); // Bank H - 0x7FFF = 0x8000 (32KiB)
	//(*this->memoryMap)[20] = Memory(0x068A0000, 0x068A3FFF); // Bank I - 0x3FFF = 0x4000 (16KiB)

	// VVRAM (Virtual Video RAM)
	//(*this->memoryMap)[21] = Memory(0x06000000, 0x0607FFFF); // Main Background - 0x7FFFF = 0x80000 (512KiB)
	//(*this->memoryMap)[22] = Memory(0x06200000, 0x0621FFFF); // Sub Background - 0x1FFFF = 0x20000 (128KiB)
	//(*this->memoryMap)[23] = Memory(0x06400000, 0x0643FFFF); // Main Sprite - 0x3FFFF = 0x40000 (256KiB)
	//(*this->memoryMap)[24] = Memory(0x06600000, 0x0661FFFF); // Sub Sprite - 0x1FFFF = 0x20000 (128KiB)
}

MemoryMap::~MemoryMap()
{

}

vector<Memory*>* MemoryMap::getMemoryMap()
{
	return this->memoryMap;
}

bool MemoryMap::allocate(uint32_t startAddress, uint32_t endAddress, std::function<void()> func)
{
	// Check if memory is already allocated in between both addresses.

	Memory* memory = new Memory(startAddress, endAddress, func);

	this->memoryMap->push_back(memory);

	return true;
}

bool MemoryMap::mirror(uint32_t mirroredAddress, uint32_t address)
{
	Memory* memory = this->getMemory(address);

	if(memory == NULL)
	{
		Logger::log("Mirror Destination Memory Address out of range: " + String::decToHex(address));

		return false;
	}

	memory->addMirroredAddress(mirroredAddress);

	return true;
}

bool MemoryMap::load(uint8_t* data, uint32_t dataLength, uint32_t destAddress)
{
	if(data == NULL || dataLength == 0 || destAddress == 0)
	{
		return false;
	}

	Memory* memory = this->getMemory(destAddress);

	if(memory == NULL)
	{
		Logger::log("Load Destination Memory Address out of range: " + String::decToHex(destAddress));

		return false;
	}

	destAddress -= memory->getStartAddress();

	if(destAddress + dataLength > memory->getMemory()->getSize())
	{
		Logger::log("Attempted to load into RAM at address: " + String::decToHex(memory->getStartAddress() + destAddress) + " to " + String::decToHex((memory->getStartAddress() + destAddress) + dataLength) + " (Max Memory: " + String::decToHex(memory->getMemory()->getSize() /* TODO: Calculate total RAM */) + ")");

		return false;
	}

	Logger::log("Dest Addr: " + to_string(destAddress));

	memcpy(memory->getMemory()->get() + destAddress, data, dataLength);

	return true;
}

bool MemoryMap::write(uint32_t destAddress, uint8_t* data, uint32_t dataLength)
{
	// Handle any I/O at address (eg. video)
	this->load(data, dataLength, destAddress);

	Memory* memory = this->getMemory(destAddress);

	memory->executeFunction();

	return true;
}

bool MemoryMap::copy(uint32_t sourceAddress, uint32_t destAddress, uint32_t length)
{
	if(length == 0)
	{
		return false;
	}

	Memory* sourceMemory = this->getMemory(sourceAddress);
	Memory* destMemory = this->getMemory(destAddress);

	if(sourceMemory == NULL)
	{
		Logger::log("Copy Source Memory Address out of range: " + String::decToHex(sourceAddress));

		return false;
	}

	if(destMemory == NULL)
	{
		Logger::log("Copy Destination Memory Address out of range: " + String::decToHex(destAddress));

		return false;
	}

	sourceAddress -= sourceMemory->getStartAddress();
	destAddress -= destMemory->getStartAddress();

	if(destAddress + length > destMemory->getMemory()->getSize())
	{
		Logger::log("Attempted to copy RAM to address: " + String::decToHex(destMemory->getStartAddress() + destAddress) + " to " + String::decToHex((destMemory->getStartAddress() + destAddress) + length) + " from " + String::decToHex(sourceMemory->getStartAddress() + sourceAddress) + " (Length: " + String::decToHex(length) + ")");

		return false;
	}

	for(uint32_t address = sourceAddress; address < sourceAddress + length; address++)
	{
		destMemory->getMemory()[(address - sourceAddress) + destAddress] = sourceMemory->getMemory()[address]; 
	}

	return true;
}

Memory* MemoryMap::getMemory(uint32_t address)
{
	for(uint32_t index = 0; index < this->memoryMap->size(); index++)
	{
		Memory* memory = this->memoryMap->at(index);

		if(address >= memory->getStartAddress() && address <= memory->getEndAddress())
		{
			return memory;
		}
	}

	Memory* memory = SharedMemoryMap::getInstance()->getMemory(address);
	
	if(memory != NULL)
	{
		return memory;
	}

	return NULL;
}

uint32_t MemoryMap::getTotalSize()
{
	uint32_t totalRamSize = 0;

	for(uint32_t index = 0; index < this->memoryMap->size(); index++)
	{
		Memory* memory = this->memoryMap->at(index);

		totalRamSize += memory->getMemory()->getSize();
	}

	return totalRamSize;
}

Pointer<uint8_t>* MemoryMap::getMemory()
{
	Pointer<uint8_t>* memoryMap = new Pointer<uint8_t>(this->getTotalSize());
	uint32_t currentAddress = 0x0;

	for(uint32_t index = 0; index < this->memoryMap->size(); index++)
	{
		Memory* memory = this->memoryMap->at(index);

		memcpy(memoryMap->get() + currentAddress, memory->getMemory()->get(), memory->getMemory()->getSize());

		currentAddress += memory->getEndAddress();
	}

	return memoryMap;
}

#include <algorithm>

#include <Bits.hpp>

void MemoryMap::print()
{
	Logger::log("");
	Logger::log("Memory Map");
	Logger::log("Total RAM: " + to_string(this->getTotalSize()) + "b");

	//Logger::log(String::toHexString((char*) this->memory, this->memorySize));

	for(uint32_t index = 0; index < this->memoryMap->size(); index++)
	{
		Memory* memory = this->memoryMap->at(index);

		string hex = String::toHexString(memory->getMemory()->get(), memory->getMemory()->getSize());

		//Cut off extra zeroes after 4 repeated zeroes, displaying (..4 '0' more..)
		hex.erase(std::remove(hex.begin(), hex.end(), '0'), hex.end());

		Logger::log("[" + String::decToHex(memory->getStartAddress()) + " - " + String::decToHex(memory->getEndAddress()) + "] (Size: " + to_string(memory->getMemory()->getSize()) + "b): " + hex);
	}

	Logger::log("");
}