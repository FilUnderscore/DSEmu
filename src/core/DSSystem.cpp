#include "include\DSSystem.hpp"

#include "include\Logger.hpp"
#include "include\String.hpp"
#include "include\SharedMemoryMap.hpp"
#include "include\GPU.hpp"
#include "include\ARM9.hpp"
#include "include\ARM7.hpp"
#include "include\BIOS.hpp"

using DS::DSSystem;
using CPU::ARM7;
using CPU::ARM9;

DSSystem::DSSystem()
{
	this->threads = new vector<thread*>();

	this->bios = new BIOS(this);

	this->arm9 = new ARM9(this);
	this->arm7 = new ARM7(this);

	this->gpu = new GPU(this);

	SharedMemoryMap::getInstance()->allocate(0x02000000, 0x023FFFFF); // Main Memory
	SharedMemoryMap::getInstance()->mirror(0x02400000, 0x02000000);

	SharedMemoryMap::getInstance()->allocate(0x03000000, 0x03003FFF); // Shared WRAM Bank 0
	SharedMemoryMap::getInstance()->allocate(0x03004000, 0x03007FFF); // Shared WRAM Bank 1

	SharedMemoryMap::getInstance()->print();
}

DSSystem::~DSSystem()
{

}

BIOS* DSSystem::getBIOS()
{
	return this->bios;
}

ARM9* DSSystem::getARM9()
{
	return this->arm9;
}

ARM7* DSSystem::getARM7()
{
	return this->arm7;
}

GPU* DSSystem::getGPU()
{
	return this->gpu;
}

void DSSystem::loadCartridge(DSCartridge* cartridge)
{
	this->cartridge = cartridge;
	this->cartridge->getCartridgeHeader()->print();

	Logger::log("Loading ARM9 into Virtual RAM");

	this->arm9->getMemory()->load(cartridge->getROMData() + this->cartridge->getCartridgeHeader()->getARM9ROMOffset(), this->cartridge->getCartridgeHeader()->getARM9Size(), this->cartridge->getCartridgeHeader()->getARM9RAMAddress());
	this->arm9->getMemory()->print();

	Logger::log("Loading ARM7 into Virtual RAM");

	this->arm7->getMemory()->load(cartridge->getROMData() + this->cartridge->getCartridgeHeader()->getARM7ROMOffset(), this->cartridge->getCartridgeHeader()->getARM7Size(), this->cartridge->getCartridgeHeader()->getARM7RAMAddress());
	this->arm7->getMemory()->print();
}

DSCartridge* DSSystem::getDSCartridge()
{
	return this->cartridge;
}

void DSSystem::run()
{
	this->running = true;

	this->arm9->run(this->cartridge->getCartridgeHeader()->getARM9EntryAddress());
	//this->arm7->run(this->cartridge->getCartridgeHeader()->getARM7EntryAddress());

	while(this->running)
	{
		this->gpu->getVideo()->tick();
	}

	this->terminate();
}

void DSSystem::registerThread(thread* thread)
{
	this->threads->push_back(thread);
}

bool DSSystem::isRunning()
{
	return this->running;
}

void DSSystem::terminate()
{
	if(!this->running)
	{
		return;
	}

	this->running = false;

	for(uint32_t index = 0; index < this->threads->size(); index++)
	{
		thread* thread = this->threads->at(index);

		delete thread;
	}
}