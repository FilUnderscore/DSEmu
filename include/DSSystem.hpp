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

class VideoGL;

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

		VideoGL* getVideo();

		void loadCartridge(DSCartridge* cartridge);

		DSCartridge* getDSCartridge();

		void run();

		void registerThread(thread* thread);

		void terminate();

	private:
		BIOS* bios;

		ARM9* arm9;

		ARM7* arm7;

		VideoGL* video;

		DSCartridge* cartridge;

		vector<thread*>* threads;

		bool running;
	};
}

#endif