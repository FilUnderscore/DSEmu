#ifndef INCLUDE_ARM9_HPP_
#define INCLUDE_ARM9_HPP_

/**
  * ARM946E-S - DS main processor
  * Clock Speed: 67 MHz
  * MIPS (Million Instructions Per Second): 200 - 300
  * RISC (Reduced Instruction Set Computer): 32-bit
  */

#include "ARM.hpp"

#include "CP15.hpp"

using namespace CPU;

class DS;

namespace CPU
{
	class ARM9 : public ARM
	{
	public:
		ARM9(DS* ds);
		~ARM9();

	private:
		CP15 cp15;
	};
}

#endif