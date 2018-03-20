#ifndef INCLUDE_MOVOPERATION_HPP_
#define INCLUDE_MOVOPERATION_HPP_

#include "Operation.hpp"

namespace CPU
{
	class MOVOperation : public Operation
	{
	public:
		MOVOperation();
		~MOVOperation();

		void execute();

		void memory();

		void write();
	};
}

#endif