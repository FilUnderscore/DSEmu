#ifndef INCLUDE_STRING_HPP_
#define INCLUDE_STRING_HPP_

#include <string>

using namespace std;

class String
{
public:
	static string toHexString(uint8_t* array, uint32_t size);

	static char toHexChar(char binChar);

	static string decToHex(uint32_t dec);
};

#endif