#ifndef INCLUDE_CP15_HPP_
#define INCLUDE_CP15_HPP_

#include "CP.hpp"

using namespace CPU;

namespace CPU
{
	/*
	 * CP15 - ARM9 co-processor
	 */
	class CP15 : public CP
	{
	public:
		CP15();
		~CP15();	
	};
}

#endif