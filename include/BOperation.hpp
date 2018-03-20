#ifndef INCLUDE_BOPERATION_HPP_
#define INCLUDE_BOPERATION_HPP_

#include "Operation.hpp"

namespace CPU
{
	class BOperation : public Operation
	{
	public:
		BOperation();
		~BOperation();
		
		void execute();

		void memory();

		void write();
	};
}

#endif