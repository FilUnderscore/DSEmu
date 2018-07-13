#ifndef INCLUDE_GPU_HPP_
#define INCLUDE_GPU_HPP_

#include "VRAM.hpp"
#include "Memory.hpp"
#include "DSSystem.hpp"
#include "VideoGL.hpp"

using DS::DSSystem;

class GPU
{
public:
	static Memory* VRAM_A;
	static Memory* VRAM_B;
	static Memory* VRAM_C;
	static Memory* VRAM_D;
	static Memory* VRAM_E;
	static Memory* VRAM_F;
	static Memory* VRAM_G;
	static Memory* VRAM_H;
	static Memory* VRAM_I;

	GPU(DSSystem* ds);
	~GPU();

	void init();

	void powerControl(Memory* memory);

	void displayControl(Memory* memory);

	void vramControl(Memory* memory);

	void vramWrite(Memory* memory);

	VideoGL* getVideo();

private:
	DSSystem* ds;

	VideoGL* video;
};

#endif