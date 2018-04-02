#ifndef INCLUDE_DISPLAYENGINEA_HPP_
#define INCLUDE_DISPLAYENGINEA_HPP_

#include "DisplayEngine.hpp"

class DisplayEngineA : public DisplayEngine
{
public:
	DisplayEngineA(GPU* gpu);
	~DisplayEngineA();
};

#endif