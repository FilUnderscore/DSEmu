#include <DSSystem.hpp>

#include <Logger.hpp>
#include <String.hpp>

using DS::DSSystem;

DSSystem::DSSystem()
{
	this->bios = new BIOS(this);

	this->arm9 = new ARM9(this);

	this->arm7 = new ARM7(this);

	this->ram = new RAM(this);
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

RAM* DSSystem::getRAM()
{
	return this->ram;
}

void DSSystem::loadCartridge(DSCartridge* cartridge)
{
	this->cartridge = cartridge;
	this->cartridge->getCartridgeHeader()->print();

	Logger::log("Loading ARM9 into Virtual RAM");

	this->ram->load(cartridge->getROMData() + this->cartridge->getCartridgeHeader()->getARM9ROMOffset(), this->cartridge->getCartridgeHeader()->getARM9Size(), this->cartridge->getCartridgeHeader()->getARM9RAMAddress());

	Logger::log("Loading ARM7 into Virtual RAM");

	this->ram->load(cartridge->getROMData() + this->cartridge->getCartridgeHeader()->getARM7ROMOffset(), this->cartridge->getCartridgeHeader()->getARM7Size(), this->cartridge->getCartridgeHeader()->getARM7RAMAddress());
	this->ram->print();
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