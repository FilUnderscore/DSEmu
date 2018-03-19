#include <DS.hpp>

#include <Logger.hpp>

#include <String.hpp>

DS::DS()
{
	this->bios = new BIOS(this);

	this->arm9 = new ARM9(this);

	this->arm7 = new ARM7(this);

	this->ram = new RAM(this);
}

DS::~DS()
{

}

BIOS* DS::getBIOS()
{
	return this->bios;
}

ARM9* DS::getARM9()
{
	return this->arm9;
}

ARM7* DS::getARM7()
{
	return this->arm7;
}

RAM* DS::getRAM()
{
	return this->ram;
}

void DS::loadCartridge(DSCartridge* cartridge)
{
	this->cartridge = cartridge;

	this->cartridge->getCartridgeHeader()->print();

	Logger::log("Loading ARM9 into Virtual RAM");

	this->ram->load(cartridge->getROMData() + this->cartridge->getCartridgeHeader()->getARM9ROMOffset(), this->cartridge->getCartridgeHeader()->getARM9Size(), this->cartridge->getCartridgeHeader()->getARM9RAMAddress());

	Logger::log("Loading ARM7 into Virtual RAM");

	this->ram->load(cartridge->getROMData() + this->cartridge->getCartridgeHeader()->getARM7ROMOffset(), this->cartridge->getCartridgeHeader()->getARM7Size(), this->cartridge->getCartridgeHeader()->getARM7RAMAddress());

	this->ram->print();

	this->run();
}

DSCartridge* DS::getDSCartridge()
{
	return this->cartridge;
}

void DS::run()
{
	this->arm9->tick();

	this->arm9->print();
}