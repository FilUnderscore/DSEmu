#include <DSCartridge.hpp>

using namespace Cartridge;

DSCartridge::DSCartridge(DSCartridgeHeader* cartridgeHeader, uint8_t* romData)
{
	this->cartridgeHeader = cartridgeHeader;
	this->romData = romData;
}

DSCartridge::~DSCartridge()
{

}

DSCartridgeHeader* DSCartridge::getCartridgeHeader()
{
	return this->cartridgeHeader;
}

uint8_t* DSCartridge::getROMData()
{
	return this->romData;
}