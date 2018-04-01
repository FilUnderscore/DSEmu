#ifndef INCLUDE_DS_HPP_
#define INCLUDE_DS_HPP_

#include "ARM9.hpp"
#include "ARM7.hpp"
#include "BIOS.hpp"
#include "DSCartridge.hpp"
#include <thread>
#include <vector>

using namespace CPU;
using namespace Cartridge;

using std::vector;

class GPU;

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

		GPU* getGPU();

		void loadCartridge(DSCartridge* cartridge);

		DSCartridge* getDSCartridge();

		void run();

		void registerThread(thread* thread);

		bool isRunning();

		void terminate();

	private:
		BIOS* bios;

		ARM9* arm9;

		ARM7* arm7;

		GPU* gpu;

		DSCartridge* cartridge;

		vector<thread*>* threads;

		bool running;
	};
}

#endif