#include <DSEmu.hpp>

#include <DS.hpp>

#include <DSCartridgeLoader.hpp>

#include <string>

using namespace std;

#include <Logger.hpp>

int main(int argc, char** argv)
{
	DSEmu::init();

	Logger::log("DSEmu\n");

	DSCartridge* cartridge = DSCartridgeLoader::loadCartridgeFromFile("TinyFB.nds");

	DS* ds = new DS();

	ds->loadCartridge(cartridge);

	ds->run();

	return 0;
}