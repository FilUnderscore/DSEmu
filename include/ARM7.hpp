#ifndef INCLUDE_ARM7_HPP_
#define INCLUDE_ARM7_HPP_

/**
  * ARM7TDMI - DS co-processor
  * Clock Speed: 33 MHz
  * MIPS (Million Instructions Per Second): 20
  * RISC (Reduced Instruction Set Computer): 16-bit/32-bit
  */

#include "ARM.hpp"

#include "CP14.hpp"

using namespace CPU;

namespace CPU
{
	class ARM7 : public ARM
	{
	public:
		ARM7(DSSystem* ds);
		~ARM7();

		void processPipeline();

	private:
		CP14 cp14;
	};
}

#endif