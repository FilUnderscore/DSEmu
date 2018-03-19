#ifndef INCLUDE_DSCARTRIDGEHEADER_HPP_
#define INCLUDE_DSCARTRIDGEHEADER_HPP_

#include <string>

using namespace std;

namespace Cartridge
{
	/*
	 * Loaded from ROM Address 0 to Main RAM 27FFE00h on Power-up
	 */
	class DSCartridgeHeader
	{
	public:
		DSCartridgeHeader();

		DSCartridgeHeader(uint8_t* headerData);

		void print();

		string getGameTitle();

		string getGamecode();

		string getMakercode();

		uint8_t getUnitcode();

		uint8_t getEncryptionSeedSelect();

		uint8_t getDeviceCapacity();

		uint8_t* getReserved_0();

		uint8_t getReserved_1();

		uint8_t getNDSRegion();

		uint8_t getROMVersion();

		uint8_t getAutostart();

		uint32_t getARM9ROMOffset();

		uint32_t getARM9EntryAddress();

		uint32_t getARM9RAMAddress();

		uint32_t getARM9Size();

		uint32_t getARM7ROMOffset();

		uint32_t getARM7EntryAddress();

		uint32_t getARM7RAMAddress();

		uint32_t getARM7Size();

		uint32_t getFNTOffset();

		uint32_t getFNTSize();

		uint32_t getFATOffset();

		uint32_t getFATSize();

		uint32_t getFileARM9OverlayOffset();

		uint32_t getFileARM9OverlaySize();

		uint32_t getFileARM7OverlayOffset();

		uint32_t getFileARM7OverlaySize();

		uint32_t getPort40001A4hSettingNormalCommands();

		uint32_t getPort40001A4hSettingKey1Commands();

		uint32_t getIconTitleOffset();

		uint16_t getSecureAreaChecksum();

		uint16_t getSecureAreaDelay();

		uint32_t getARM9AutoLoadListRAMAddress();

		uint32_t getARM7AutoLoadListRAMAddress();

		uint64_t getSecureAreaDisable();

		uint32_t getTotalUsedROMSize();

		uint32_t getROMHeaderSize();

		uint8_t* getReserved_2();

		uint8_t* getNintendoLogo();

		uint16_t getNintendoLogoChecksum();

		uint16_t getHeaderChecksum();

		uint32_t getDebugROMOffset();

		uint32_t getDebugSize();

		uint32_t getDebugRAMAddress();

		uint8_t* getReserved_3();

		uint8_t* getReserved_4();

	private:
		/*
		 * Game title
		 * Address: 000h
		 *
		 * Uppercase ASCII, padded with 00h
		 */
		string gameTitle;

		/*
		 * Game code
		 * Address: 00Ch
		 *
		 * Uppercase ASCII, NTR-<code>
		 */
		string gamecode;

		/*
		 * Maker code
		 * Address: 010h
		 *
		 * Uppercase ASCII, "01" = Nintendo
		 */
		string makercode;

		/*
		 * Unit code
		 * Address: 012h
		 *
		 * 00h = NDS (Nintendo DS)
		 * 02h = NDS + DSi
		 * 03h = DSi
		 * bit1 = DSi 
		 */
		uint8_t unitcode;

		/*
		 * Encrypption Seed Select
		 * Address: 013h
		 *
		 * 00..07h, usually 00h
		 */
		uint8_t encryptionSeedSelect;

		/*
		 * Device Capacity
		 * Address: 014h
		 *
		 * Chipsize = 128KB SHL nn (e.g. 7 = 16MB)
		 */
		uint8_t deviceCapacity;

		/*
		 * Reserved
		 * Address: 015h
		 *
		 * zero filled
		 */
		uint8_t reserved_0[7];

		/*
		 * Reserved
		 * Address: 01Ch
		 *
		 * zero
		 *
		 * except used on DSi
		 */
		uint8_t reserved_1;

		/*
		 * NDS Region
		 * Address: 01Dh
		 *
		 * 00h = Normal
		 * 80h = China
		 * 40h = Korea
		 *
		 * other on DSi
		 */
		uint8_t ndsRegion;

		/*
		 * ROM version
		 * Address: 01Eh
		 *
		 * usually 00h
		 */
		uint8_t romVersion;

		/*
		 * Autostart
		 * Address: 01Fh
		 *
		 * Bit2: Skip "Press Button" after Health and Safety
		 *
		 * Also skips boot menu, even in Manual mode & even Start pressed
		 */
		uint8_t autostart;

		/*
		 * ARM9 ROM Offset
		 * Address: 020h
		 *
		 * 4000h and up, align 1000h
		 */
		uint32_t arm9_romOffset;

		/*
		 * ARM9 Entry Address
		 * Address: 024h
		 *
		 * 2000000h..23BFE00h
		 */
		uint32_t arm9_entryAddress;

		/*
		 * ARM9 RAM Address
		 * Address: 028h
		 *
		 * 2000000h..23BFE00h
		 */
		uint32_t arm9_ramAddress;

		/*
		 * ARM9 Size
		 * Address: 02Ch
		 *
		 * max 3BFE00h (3839.5KB)
		 */
		uint32_t arm9_size;

		/*
		 * ARM7 ROM Offset
		 * Address: 030h
		 *
		 * 8000h and up
		 */
		uint32_t arm7_romOffset;

		/*
		 * ARM7 Entry Address
		 * Address: 034h
		 *
		 * 2000000h..23BFE00h or 37F8000h..3807E00h
		 */
		uint32_t arm7_entryAddress;

		/*
		 * ARM7 RAM Address
		 * Address: 038h
		 *
		 * 2000000h..23BFE00h or 37F8000h..3807E00h
		 */
		uint32_t arm7_ramAddress;

		/*
		 * ARM7 Size
		 * Address: 03Ch
		 *
		 * max 3BFE00h (3839.5KB) or FE00h (63.5KB)
		 */
		uint32_t arm7_size;

		/*
		 * FNT (File Name Table) Offset
		 * Address: 040h
		 */
		uint32_t fntOffset;

		/*
		 * FNT (File Name Table) Size
		 * Address: 044h
		 */
		uint32_t fntSize;

		/*
		 * FAT (File Allocation Table) Offset
		 * Address: 048h
		 */
		uint32_t fatOffset;

		/*
		 * FAT (File Allocation Table) Size
		 * Address: 04Ch
		 */
		uint32_t fatSize;

		/*
		 * File ARM9 Overlay Offset
		 * Address: 050h
		 */
		uint32_t file_arm9_overlayOffset;

		/*
		 * File ARM9 Overlay Size
		 * Address: 054h
		 */
		uint32_t file_arm9_overlaySize;

		/*
		 * File ARM7 Overlay Offset
		 * Address: 058h
		 */
		uint32_t file_arm7_overlayOffset;

		/*
		 * File ARM7 Overlay Size
		 * Address: 05Ch
		 */
		uint32_t file_arm7_overlaySize;

		/*
		 * Port 40001A4h setting for normal commands
		 * Address: 060h
		 *
		 * usually 00586000h
		 */
		uint32_t port_40001A4h_setting_normalCommands;

		/*
		 * Port 40001A4h setting for KEY1 commands
		 * Address: 064h
		 *
		 * usually 001808F8h
		 */
		uint32_t port_40001A4h_setting_key1Commands;

		/*
		 * Icon/Title Offset
		 * Address: 068h
		 *
		 * 0 = None
		 *
		 * 8000h and up
		 */
		uint32_t iconTitle_offset;

		/*
		 * Secure Area Checksum
		 * Address: 06Ch
		 *
		 * CRC-16 of [[020h]..00007FFFh]
		 */
		uint16_t secureAreaChecksum;

		/*
		 * Secure Area Delay
		 * Address: 06Eh
		 *
		 * in 131kHz units
		 *
		 * 051Eh = 10ms or 0D7Eh = 26ms
		 */
		uint16_t secureAreaDelay;

		/*
		 * ARM9 Auto Load List RAM Address
		 * Address: 070h
		 */
		uint32_t arm9_autoLoadListRamAddress;

		/*
		 * ARM7 Auto Load List RAM Address
		 * Address: 074h
		 */
		uint32_t arm7_autoLoadListRamAddress;

		/*
		 * Secure Area Disable
		 * Address: 078h
		 *
		 * by encrypted "NmMdOnly"
		 *
		 * usually zero
		 */
		uint64_t secureAreaDisable;

		/*
		 * Total used ROM size
		 * Address: 080h
		 *
		 * remaining/unused bytes usually FFh-padded
		 */
		uint32_t totalUsedROMSize;

		/*
		 * ROM Header Size
		 * Address: 084h
		 *
		 * 4000h
		 */
		uint32_t romHeaderSize;

		/*
		 * Reserved
		 * Address: 088h
		 *
		 * zero filled
		 *
		 * except [88h..93h] used on DSi
		 */
		uint8_t reserved_2[0x38];

		/*
		 * Nintendo Logo
		 * Address: 0C0h
		 *
		 * compressed bitmap same as in GBA Headers
		 */
		uint8_t nintendoLogo[0x9C];

		/*
		 * Nintendo Logo Checksum
		 * Address: 15Ch
		 *
		 * CRC-16 of [0C0h-15Bh], fixed CF56h
		 */
		uint16_t nintendoLogoChecksum;

		/*
		 * Header Checksum
		 * Address: 15Eh
		 *
		 * CRC-16 of [000h-15Dh]
		 */
		uint16_t headerChecksum;

		/**
		  * Debug
		  *
		  * only if debug version with SIO and 8MB
		  */

		/*
		 * Debug ROM Offset
		 * Address: 160h
		 *
		 * 0 = none
		 *
		 * 8000h and up
		 */
		uint32_t debug_romOffset;

		/*
		 * Debug Size
		 * Address: 164h
		 *
		 * 0 = none
		 *
		 * max 3BFE00h
		 */
		uint32_t debug_size;

		/*
		 * Debug RAM Address
		 * Address: 168h
		 *
		 * 0 = none
		 *
		 * 2400000h..27BFE00h
		 */
		uint32_t debug_ramAddress;

		/*
		 * Reserved
		 * Address: 16Ch
		 *
		 * zero filled
		 *
		 * transferred and stored but not used
		 */
		uint8_t reserved_3[4];

		/*
		 * Reserved
		 * Address: 170h
		 *
		 * zero filled
		 *
		 * transferred but not stored in RAM
		 */
		uint8_t reserved_4[0x90];
	};
}

#endif