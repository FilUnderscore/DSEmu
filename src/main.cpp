#include <cstdlib>
#include <cstring>
#include <cstdio>

#include <DSEmu.hpp>

#include <DS.hpp>

#include <DSCartridgeLoader.hpp>

#include <string>

using namespace std;

int main(int argc, char** argv)
{
	DSEmu::init();

	printf("DSEmu");
	printf("\n");

	DSCartridge* cartridge = DSCartridgeLoader::loadCartridgeFromFile("TinyFB.nds");

	DS* ds = new DS();

	ds->loadCartridge(cartridge);

	ds->getRAM()->copy(1, 0x400000, 1);

	return 0;
}