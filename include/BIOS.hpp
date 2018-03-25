#ifndef INCLUDE_BIOS_HPP_
#define INCLUDE_BIOS_HPP_

namespace DS
{
	class DSSystem;
}

using DS::DSSystem;

class BIOS
{
public:
	BIOS(DSSystem* ds);
	~BIOS();
};

#endif