#include <DSEmu.hpp>

#include <DSSystem.hpp>
#include <DSCartridgeLoader.hpp>
#include <Logger.hpp>
#include <string>

using namespace std;

using DS::DSSystem;

int main(int argc, char** argv)
{
	DSEmu::init();

	Logger::log("DSEmu\n");

	DSCartridge* cartridge = DSCartridgeLoader::loadCartridgeFromFile("TinyFB.nds");

	DSSystem* ds = new DSSystem();

	ds->loadCartridge(cartridge);

	ds->run();

	delete ds;
	ds = NULL;

	delete cartridge;
	cartridge = NULL;

	return 0;
}