#ifndef INCLUDE_SUBOPERATION_HPP_
#define INCLUDE_SUBOPERATION_HPP_

#include "Operation.hpp"

namespace CPU
{
	class SUBOperation : public Operation
	{
	public:
		SUBOperation();
		~SUBOperation();

		void execute();

		void memory();
	};
}

#endif