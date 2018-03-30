#include <DSCartridgeLoader.hpp>

#include <Logger.hpp>
#include <String.hpp>
#include <vector>
#include <fstream>

using namespace Cartridge;

DSCartridge* DSCartridgeLoader::loadCartridgeFromFile(string filePath)
{
	Logger::log("Loading Cartridge from file: " + filePath);

	ifstream in(filePath, ios::in | ios::binary | ios::ate);
	in >> noskipws;
	in >> hex;

	if(in.is_open())
	{
		int fileLength = in.tellg();

		Logger::log("ROM File Length: " + to_string(fileLength));

		uint8_t* data = new uint8_t[fileLength]();

		in.seekg(0, ios::beg);
		in.read((char*) data, fileLength);

		in.close();

		Logger::log("ROM HEX: " + String::toHexString(data, fileLength));

		DSCartridgeHeader* header = new DSCartridgeHeader(data);
		
		DSCartridge* cartridge = new DSCartridge(header, data);

		return cartridge;
	}
	else
	{
		Logger::log("Failed to open file.");
	}

	return NULL;
}