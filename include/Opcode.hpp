#ifndef INCLUDE_OPCODE_HPP_
#define INCLUDE_OPCODE_HPP_

namespace CPU
{
	enum Opcode
	{
		ANDEQ = 0x00,

		BNE = 0x1A,

		CMPPL = 0x53,

		STRH = 0xE0,

		BX = 0xE1,

		SUBS = 0xE2,

		MOV = 0xE3,

		//MOVN = ,

		STR = 0xE5,

		B = 0xEA
	};
}

#endif