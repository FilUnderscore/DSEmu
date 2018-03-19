#include <String.hpp>

#include <ios>
#include <iomanip>
#include <sstream>

#include <algorithm>

using namespace std;

string String::toHexString(uint8_t* array, uint32_t size)
{
	stringstream ss;

	for(int i = 0; i < size; i++)
	{
		ss << std::hex << setfill('0') << setw(2) << (int) (uint8_t) array[i];
	}

	return ss.str();
}

char String::toHexChar(char binChar)
{
	return (int) (unsigned char) binChar;
}

string String::decToHex(uint32_t dec)
{
	stringstream ss;

	ss << std::hex << dec;

	string str = ss.str();

	std::transform(str.begin(), str.end(), str.begin(), ::toupper);

	return "0x" + str;
}