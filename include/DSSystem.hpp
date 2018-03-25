#ifndef INCLUDE_DS_HPP_
#define INCLUDE_DS_HPP_

#include "ARM9.hpp"
#include "ARM7.hpp"
#include "BIOS.hpp"
#include "DSCartridge.hpp"
#include "RAM.hpp"

using namespace CPU;
using namespace Cartridge;

namespace DS
{
	class DSSystem
	{
	public:
		DSSystem();
		~DSSystem();

		BIOS* getBIOS();

		ARM9* getARM9();

		ARM7* getARM7();

		RAM* getRAM();

		void loadCartridge(DSCartridge* cartridge);

		DSCartridge* getDSCartridge();

		void run();

	private:
		BIOS* bios;

		ARM9* arm9;

		ARM7* arm7;

		RAM* ram;

		DSCartridge* cartridge;
	};
}

#endif