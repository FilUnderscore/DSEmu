#ifndef INCLUDE_CP14_HPP_
#define INCLUDE_CP14_HPP_

#include "CP.hpp"

using namespace CPU;

namespace CPU
{
	/*
	 * CP14 - ARM7 co-processor
	 */
	class CP14 : public CP
	{
	public:
		CP14();
		~CP14();
	};
}

#endif