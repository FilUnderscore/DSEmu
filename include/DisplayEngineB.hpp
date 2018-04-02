#ifndef INCLUDE_DISPLAYENGINEB_HPP_
#define INCLUDE_DISPLAYENGINEB_HPP_

#include "DisplayEngine.hpp"

class DisplayEngineB : public DisplayEngine
{
public:
	DisplayEngineB(GPU* gpu);
	~DisplayEngineB();
};

#endif