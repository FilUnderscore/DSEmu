#ifndef INCLUDE_CP_HPP_
#define INCLUDE_CP_HPP_

#include "ARM.hpp"

using CPU::ARM;

namespace CPU
{
	/*
	 * CP - ARM co-processor
	 */
	class CP
	{
	public:
		CP();
		virtual ~CP();
	};
}

#endif