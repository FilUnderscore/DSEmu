#ifndef INCLUDE_CONDITION_HPP_
#define INCLUDE_CONDITION_HPP_

namespace CPU
{
	enum Condition
	{
		/*
		 * Equal / equals zero
		 *
		 * Status flag state for execution (in CPSR):
		 * Z set
		 */
		EQ = 0x00,

		/*
		 * Not equal
		 *
		 * Status flag state for execution (in CPSR):
		 * Z clear
		 */
		NE = 0x01,

		/*
		 * Carry set / unsigned higher or same
		 *
		 * Status flag state for execution (in CPSR):
		 * C set
		 */
		CS = 0x02,

		/*
		 * Carry clear / unsigned lower
		 *
		 * Status flag state for execution (in CPSR):
		 * C clear
		 */
		CC = 0x03,

		/*
		 * Minus / negative
		 *
		 * Status flag state for execution (in CPSR):
		 * N set
		 */
		MI = 0x04,

		/*
		 * Plus / positive or zero
		 *
		 * Status flag state for execution (in CPSR):
		 * N clear
		 */
		PL = 0x05,

		/*
		 * Overflow
		 *
		 * Status flag state for execution (in CPSR):
		 * V set
		 */
		VS = 0x06,

		/*
		 * No overflow
		 *
		 * Status flag state for execution (in CPSR):
		 * V clear
		 */
		VC = 0x07,

		/*
		 * Unsigned higher
		 *
		 * Status flag state for execution (in CPSR):
		 * C set and Z clear
		 */
		HI = 0x08,

		/*
		 * Unsigned lower or same
		 *
		 * Status flag state for execution (in CPSR):
		 * C clear or Z set
		 */
		LS = 0x09,

		/*
		 * Signed greater than or equal
		 *
		 * Status flag state for execution (in CPSR):
		 * N equals V
		 */
		GE = 0x0A,

		/*
		 * Signed less than
		 *
		 * Status flag state for execution (in CPSR):
		 * N is not equal to V
		 */
		LT = 0x0B,

		/*
		 * Signed greater than
		 *
		 * Status flag state for execution (in CPSR):
		 * Z clear and N equals V
		 */
		GT = 0x0C,

		/*
		 * Signed less than or equal
		 *
		 * Status flag state for execution (in CPSR):
		 * Z set or N is not equal to V
		 */
		LE = 0x0D,

		/*
		 * Always
		 *
		 * Status flag state for execution (in CPSR):
		 * any
		 */
		AL = 0x0E,

		/*
		 * Never
		 *
		 * DO NOT USE!
		 *
		 * Status flag state for execution (in CPSR):
		 * none
		 */
		NV = 0x0F
	};
}

#endif