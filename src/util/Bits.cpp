#include <Bits.hpp>

uint8_t Bits::to8UBits(uint8_t* array)
{
	return (uint8_t) array[0];
}

uint16_t Bits::to16UBits(uint8_t* array)
{
	return array[0] | array[1];
}

uint32_t Bits::to32UBits(uint8_t* array)
{
	return array[0] | array[1] | array[2] | array[3];
}

uint64_t Bits::to64UBits(uint8_t* array)
{
	return array[0] | array[1] | array[2] | array[3] | 
			array[4] | array[5] | array[6] | array[7];
}

uint8_t* Bits::from8UBits(uint8_t ubits8)
{
	uint8_t* array = new uint8_t[sizeof(uint8_t)]();

	array[0] = ubits8 & 0xFF;

	return array;
}

uint8_t* Bits::from16UBits(uint16_t ubits16)
{
	uint8_t* array = new uint8_t[sizeof(uint16_t)]();

	array[0] = (ubits16 >> 8) & 0xFF;
	array[1] = ubits16 & 0xFF;

	return array;
}

uint8_t* Bits::from32UBits(uint32_t ubits32)
{
	uint8_t* array = new uint8_t[sizeof(uint32_t)]();

	array[0] = (ubits32 >> 24) & 0xFF;
	array[1] = (ubits32 >> 16) & 0xFF;
	array[2] = (ubits32 >> 8) & 0xFF;
	array[3] = ubits32 & 0xFF;

	return array;
}

uint8_t* Bits::from64UBits(uint64_t ubits64)
{
	uint8_t* array = new uint8_t[sizeof(uint64_t)]();

	array[0] = (ubits64 >> 56) & 0xFF;
	array[1] = (ubits64 >> 48) & 0xFF;
	array[2] = (ubits64 >> 40) & 0xFF;
	array[3] = (ubits64 >> 32) & 0xFF;
	array[4] = (ubits64 >> 24) & 0xFF;
	array[5] = (ubits64 >> 16) & 0xFF;
	array[6] = (ubits64 >> 8) & 0xFF;
	array[7] = ubits64 & 0xFF;

	return array;
}

uint32_t Bits::ror32UBits(uint32_t ubits32, uint32_t count)
{
	return ((ubits32 >> count) | (ubits32 << (32 - count))) >> 0;
}