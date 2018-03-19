#ifndef INCLUDE_DSCARTRIDGE_HPP_
#define INCLUDE_DSCARTRIDGE_HPP_

#include "DSCartridgeHeader.hpp"

namespace Cartridge
{
	class DSCartridge
	{
	public:
		DSCartridge(DSCartridgeHeader* cartridgeHeader, uint8_t* romData);
		~DSCartridge();

		DSCartridgeHeader* getCartridgeHeader();

		uint8_t* getROMData();

	private:
		DSCartridgeHeader* cartridgeHeader;

		uint8_t* romData;
	};
}

#endif