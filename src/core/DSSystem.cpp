#include <DSSystem.hpp>

#include <Logger.hpp>
#include <String.hpp>

#include <SharedMemoryMap.hpp>

using DS::DSSystem;

DSSystem::DSSystem()
{
	this->bios = new BIOS(this);

	this->arm9 = new ARM9(this);
	this->arm7 = new ARM7(this);

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
	this->arm9->run();
	this->arm9->print();
}