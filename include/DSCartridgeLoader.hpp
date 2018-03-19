#ifndef INCLUDE_DSCARTRIDGELOADER_HPP_
#define INCLUDE_DSCARTRIDGELOADER_HPP_

#include "DSCartridge.hpp"

#include <string>

using namespace std;

using namespace Cartridge;

namespace Cartridge
{
	class DSCartridgeLoader
	{
	public:
		static DSCartridge* loadCartridgeFromFile(string filePath);
	};
}

#endif