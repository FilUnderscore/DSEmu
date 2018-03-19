#ifndef INCLUDE_BITS_HPP_
#define INCLUDE_BITS_HPP_

#include <cstdint>

using namespace std;

class Bits
{
public:
	static uint8_t to8UBits(uint8_t* array);

	static uint16_t to16UBits(uint8_t* array);

	static uint32_t to32UBits(uint8_t* array);

	static uint64_t to64UBits(uint8_t* array);

	static uint8_t* from8UBits(uint8_t ubits8);

	static uint8_t* from16UBits(uint16_t ubits16);

	static uint8_t* from32UBits(uint32_t ubits32);

	static uint8_t* from64UBits(uint64_t ubits64);

	static uint32_t ror32UBits(uint32_t ubits32, uint32_t count);
};

#endif