#ifndef INCLUDE_DISPLAYENGINE_HPP_
#define INCLUDE_DISPLAYENGINE_HPP_

#include "GPU.hpp"
#include <cstdint>

class DisplayEngine
{
public:
	DisplayEngine(GPU* gpu);
	virtual ~DisplayEngine();

protected:
	GPU* gpu;

	/**
	  * Mode 	BG0			BG1			BG2			BG3
	  * 0		Text/3D		Text		Text		Text
	  * 1       Text/3D     Text    	Text    	Affine
	  * 2       Text/3D		Text		Affine		Affine
	  * 3		Text/3D		Text		Text		Extended
	  * 4		Text/3D		Text		Affine		Extended
	  * 5		Text/3D		Text		Extended	Extended
	  * 6		3D			-			Large		-
	  *
	  * Referenced from http://problemkaputt.de/gbatek.htm#dsvideo
	  */
	// Bit0-2
	uint8_t bg_mode;

	// Bit3
	uint8_t bg0_2d3d_selection;

	// Bit4
	uint8_t tile_obj_mapping;

	// Bit5
	uint8_t bitmap_obj_2d_dimension;

	// Bit6
	uint8_t bitmap_obj_mapping;

	// Same as GBA LCD I/O Display Control
	// Bit7-15
	// Referenced from http://problemkaputt.de/gbatek.htm#gbalcdvideocontroller

	// 1 = Allow FAST access to VRAM, Palette, OAM
	// Bit7
	uint8_t forced_blank;

	// 0 = Off, 1 = On
	// Bit8
	uint8_t screen_display_bg0;
	// Bit9
	uint8_t screen_display_bg1;
	// Bit10
	uint8_t screen_display_bg2;
	// Bit11
	uint8_t screen_display_bg3;

	// 0 = Off, 1 = On
	// Bit12
	uint8_t screen_display_obj;

	// 0 = Off, 1 = On
	// Bit13
	uint8_t window0_display_flag;
	// Bit14
	uint8_t window1_display_flag;

	// 0 = Off, 1 = On
	// Bit15
	uint8_t obj_window_display_flag;

	// Display Mode (Engine A: 0..3, Engine B: 0..1, GBA: Green Swap)
	// Bit16-17
	uint8_t displayMode;

	// VRAM Block (0..3=VRAM A..D)  (For Capture & above Display Mode = 2)
	// Bit18-19
	uint8_t vram_block;

	// Tile OBJ 1D-Boundary (See Bit4)
	// Bit20-21
	uint8_t tile_obj_1d_boundary;

	// Bitmap OBJ 1D-Boundary (see Bit5-6)
	// Bit22
	uint8_t bitmap_obj_1d_boundary;

	// OBJ Processing during H-Blank (was located in Bit5 on GBA)
	// Bit23
	uint8_t obj_processing_hblank;

	// Character Base (in 64K steps) (merged with 16K step in BGxCNT)
	// Bit24-26
	uint8_t character_base;

	// Screen Base (in 64K steps) (merged with 2K step in BGxCNT)
	// Bit27-29
	uint8_t screen_base;

	// 0 = Disable, 1 = Enable
	// Bit30
	uint8_t bg_extended_palettes;

	// 0 = Disable, 1 = Enable
	// Bit31
	uint8_t obj_extended_palettes;
};

#endif