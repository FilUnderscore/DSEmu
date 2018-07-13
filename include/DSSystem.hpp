#ifndef INCLUDE_DS_HPP_
#define INCLUDE_DS_HPP_

#include "DSCartridge.hpp"
#include <thread>
#include <vector>

using namespace Cartridge;

using std::vector;

namespace CPU
{
	class ARM9;
	class ARM7;
}

using namespace CPU;

class BIOS;
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