#ifndef INCLUDE_DSEMU_HPP_
#define INCLUDE_DSEMU_HPP_

class DSEmu
{
public:
	static void init();

	static void start();

	static void pause();

	static void stop();

private:
	DSEmu();
	~DSEmu();
};

#endif