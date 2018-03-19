#include <DSCartridgeHeader.hpp>

#include <Logger.hpp>

#include <Bits.hpp>

#include <cstring>

#include <String.hpp>

using namespace Cartridge;

DSCartridgeHeader::DSCartridgeHeader()
{

}

DSCartridgeHeader::DSCartridgeHeader(uint8_t* headerData)
{
	uint8_t gameTitle[12 + 1] = {};
	memcpy(gameTitle, headerData, sizeof(gameTitle));
	//Fixes memcpy overcopy
	gameTitle[12] = '\0';
	this->gameTitle = string((const char*) gameTitle);

	uint8_t gamecode[4 + 1] = {};
	memcpy(gamecode, headerData + 0x0C, sizeof(gamecode));
	//Fixes memcpy overcopy
	gamecode[4] = '\0';
	this->gamecode = string((const char*) gamecode);

	uint8_t makercode[2];
	memcpy(makercode, headerData + 0x10, sizeof(makercode));
	this->makercode = string((const char*) makercode);

	uint8_t unitcode[1];
	memcpy(unitcode, headerData + 0x12, sizeof(unitcode));
	this->unitcode = unitcode[0];

	uint8_t encryptionSeedSelect[1];
	memcpy(encryptionSeedSelect, headerData + 0x13, sizeof(encryptionSeedSelect));
	this->encryptionSeedSelect = encryptionSeedSelect[0];

	uint8_t deviceCapacity[1];
	memcpy(deviceCapacity, headerData + 0x14, sizeof(deviceCapacity));
	this->deviceCapacity = deviceCapacity[0];

	memcpy(this->reserved_0, headerData + 0x15, sizeof(this->reserved_0));

	uint8_t reserved_1[1];
	memcpy(reserved_1, headerData + 0x1C, sizeof(reserved_1));
	this->reserved_1 = reserved_1[0];

	uint8_t ndsRegion[1];
	memcpy(ndsRegion, headerData + 0x1D, sizeof(ndsRegion));
	this->ndsRegion = ndsRegion[0];

	uint8_t romVersion[1];
	memcpy(romVersion, headerData + 0x1E, sizeof(romVersion));
	this->romVersion = romVersion[0];

	uint8_t autostart[1];
	memcpy(autostart, headerData + 0x1F, sizeof(autostart));
	this->autostart = autostart[0];

	uint8_t arm9_romOffset[4];
	memcpy(arm9_romOffset, headerData + 0x20, sizeof(arm9_romOffset));
	this->arm9_romOffset = Bits::to32UBits(arm9_romOffset);

	uint8_t arm9_entryAddress[4];
	memcpy(arm9_entryAddress, headerData + 0x24, sizeof(arm9_entryAddress));
	this->arm9_entryAddress = Bits::to32UBits(arm9_entryAddress);

	uint8_t arm9_ramAddress[4];
	memcpy(arm9_ramAddress, headerData + 0x28, sizeof(arm9_ramAddress));
	this->arm9_ramAddress = Bits::to32UBits(arm9_ramAddress);

	uint8_t arm9_size[4];
	memcpy(arm9_size, headerData + 0x2C, sizeof(arm9_size));
	this->arm9_size = Bits::to32UBits(arm9_size);

	uint8_t arm7_romOffset[4];
	memcpy(arm7_romOffset, headerData + 0x30, sizeof(arm7_romOffset));
	this->arm7_romOffset = Bits::to32UBits(arm7_romOffset);

	uint8_t arm7_entryAddress[4];
	memcpy(arm7_entryAddress, headerData + 0x34, sizeof(arm7_entryAddress));
	this->arm7_entryAddress = Bits::to32UBits(arm7_entryAddress);

	uint8_t arm7_ramAddress[4];
	memcpy(arm7_ramAddress, headerData + 0x38, sizeof(arm7_ramAddress));
	this->arm7_ramAddress = Bits::to32UBits(arm7_ramAddress);

	uint8_t arm7_size[4];
	memcpy(arm7_size, headerData + 0x3C, sizeof(arm7_size));
	this->arm7_size = Bits::to32UBits(arm7_size);

	uint8_t fntOffset[4];
	memcpy(fntOffset, headerData + 0x40, sizeof(fntOffset));
	this->fntOffset = Bits::to32UBits(fntOffset);

	uint8_t fntSize[4];
	memcpy(fntSize, headerData + 0x44, sizeof(fntSize));
	this->fntSize = Bits::to32UBits(fntSize);

	uint8_t fatOffset[4];
	memcpy(fatOffset, headerData + 0x48, sizeof(fatOffset));
	this->fatOffset = Bits::to32UBits(fatOffset);

	uint8_t fatSize[4];
	memcpy(fatSize, headerData + 0x4C, sizeof(fatSize));
	this->fatSize = Bits::to32UBits(fatSize);

	uint8_t file_arm9_overlayOffset[4];
	memcpy(file_arm9_overlayOffset, headerData + 0x50, sizeof(file_arm9_overlayOffset));
	this->file_arm9_overlayOffset = Bits::to32UBits(file_arm9_overlayOffset);

	uint8_t file_arm9_overlaySize[4];
	memcpy(file_arm9_overlaySize, headerData + 0x54, sizeof(file_arm9_overlaySize));
	this->file_arm9_overlaySize = Bits::to32UBits(file_arm9_overlaySize);

	uint8_t file_arm7_overlayOffset[4];
	memcpy(file_arm7_overlayOffset, headerData + 0x58, sizeof(file_arm7_overlayOffset));
	this->file_arm7_overlayOffset = Bits::to32UBits(file_arm7_overlayOffset);

	uint8_t file_arm7_overlaySize[4];
	memcpy(file_arm7_overlaySize, headerData + 0x5C, sizeof(file_arm7_overlaySize));
	this->file_arm7_overlaySize = Bits::to32UBits(file_arm7_overlaySize);

	uint8_t port_40001A4h_setting_normalCommands[4];
	memcpy(port_40001A4h_setting_normalCommands, headerData + 0x60, sizeof(port_40001A4h_setting_normalCommands));
	this->port_40001A4h_setting_normalCommands = Bits::to32UBits(port_40001A4h_setting_normalCommands);

	uint8_t port_40001A4h_setting_key1Commands[4];
	memcpy(port_40001A4h_setting_key1Commands, headerData + 0x64, sizeof(port_40001A4h_setting_key1Commands));
	this->port_40001A4h_setting_key1Commands = Bits::to32UBits(port_40001A4h_setting_key1Commands);

	uint8_t iconTitle_offset[4];
	memcpy(iconTitle_offset, headerData + 0x68, sizeof(iconTitle_offset));
	this->iconTitle_offset = Bits::to32UBits(iconTitle_offset);

	uint8_t secureAreaChecksum[2];
	memcpy(secureAreaChecksum, headerData + 0x6C, sizeof(secureAreaChecksum));
	this->secureAreaChecksum = Bits::to16UBits(secureAreaChecksum);

	uint8_t secureAreaDelay[2];
	memcpy(secureAreaDelay, headerData + 0x6E, sizeof(secureAreaDelay));
	this->secureAreaDelay = Bits::to16UBits(secureAreaDelay);

	uint8_t arm9_autoLoadListRamAddress[4];
	memcpy(arm9_autoLoadListRamAddress, headerData + 0x70, sizeof(arm9_autoLoadListRamAddress));
	this->arm9_autoLoadListRamAddress = Bits::to32UBits(arm9_autoLoadListRamAddress);

	uint8_t arm7_autoLoadListRamAddress[4];
	memcpy(arm7_autoLoadListRamAddress, headerData + 0x74, sizeof(arm7_autoLoadListRamAddress));
	this->arm7_autoLoadListRamAddress = Bits::to32UBits(arm7_autoLoadListRamAddress);

	uint8_t secureAreaDisable[8];
	memcpy(secureAreaDisable, headerData + 0x78, sizeof(secureAreaDisable));
	this->secureAreaDisable = Bits::to64UBits(secureAreaDisable);

	uint8_t totalUsedROMSize[4];
	memcpy(totalUsedROMSize, headerData + 0x80, sizeof(totalUsedROMSize));
	this->totalUsedROMSize = Bits::to32UBits(totalUsedROMSize);

	uint8_t romHeaderSize[4];
	memcpy(romHeaderSize, headerData + 0x84, sizeof(romHeaderSize));
	this->romHeaderSize = Bits::to32UBits(romHeaderSize);

	memcpy(this->reserved_2, headerData + 0x88, sizeof(this->reserved_2));

	memcpy(this->nintendoLogo, headerData + 0xC0, sizeof(this->nintendoLogo));

	uint8_t nintendoLogoChecksum[2];
	memcpy(nintendoLogoChecksum, headerData + 0x15C, sizeof(nintendoLogoChecksum));
	this->nintendoLogoChecksum = Bits::to16UBits(nintendoLogoChecksum);

	uint8_t headerChecksum[2];
	memcpy(headerChecksum, headerData + 0x15E, sizeof(headerChecksum));
	this->headerChecksum = Bits::to16UBits(headerChecksum);

	uint8_t debug_romOffset[4];
	memcpy(debug_romOffset, headerData + 0x160, sizeof(debug_romOffset));
	this->debug_romOffset = Bits::to32UBits(debug_romOffset);

	uint8_t debug_size[4];
	memcpy(debug_size, headerData + 0x164, sizeof(debug_size));
	this->debug_size = Bits::to32UBits(debug_size);

	uint8_t debug_ramAddress[4];
	memcpy(debug_ramAddress, headerData + 0x168, sizeof(debug_ramAddress));
	this->debug_ramAddress = Bits::to32UBits(debug_ramAddress);

	memcpy(this->reserved_3, headerData + 0x16C, sizeof(this->reserved_3));

	memcpy(this->reserved_4, headerData + 0x170, sizeof(this->reserved_4));
}

void DSCartridgeHeader::print()
{
	Logger::log("\n");
	Logger::log("DSCartridgeHeader");

	Logger::log("Game Title: " + this->gameTitle);

	Logger::log("Gamecode: " + this->gamecode);

	Logger::log("Implement String To Hex");
	Logger::log("Makercode: " + String::toHexString((uint8_t*) strdup(this->makercode.c_str()), sizeof(this->makercode)));

	Logger::log("Unitcode: " + String::toHexString(Bits::from8UBits(this->unitcode), sizeof(this->unitcode)));

	Logger::log("Encryption Seed Select: " + String::toHexString(Bits::from8UBits(this->encryptionSeedSelect), sizeof(this->encryptionSeedSelect)));

	Logger::log("Device Capacity: " + String::toHexString(Bits::from8UBits(this->deviceCapacity), sizeof(this->deviceCapacity)));

	Logger::log("Reserved 0: " + String::toHexString(this->reserved_0, sizeof(this->reserved_0)));

	Logger::log("Reserved 1: " + String::toHexString(Bits::from8UBits(this->reserved_1), sizeof(this->reserved_1)));

	Logger::log("NDS Region: " + String::toHexString(Bits::from8UBits(this->ndsRegion), sizeof(this->ndsRegion)));

	Logger::log("ROM Version: " + String::toHexString(Bits::from8UBits(this->romVersion), sizeof(this->romVersion)));

	Logger::log("Autostart: " + String::toHexString(Bits::from8UBits(this->autostart), sizeof(this->autostart)));

	Logger::log("ARM9 ROM Offset: " + String::decToHex(this->arm9_romOffset));

	Logger::log("ARM9 Entry Address: " + String::decToHex(this->arm9_entryAddress));

	Logger::log("ARM9 RAM Address: " + String::decToHex(this->arm9_ramAddress));

	Logger::log("ARM9 Size: " + String::decToHex(this->arm9_size));

	Logger::log("ARM7 Rom Offset: " + String::decToHex(this->arm7_romOffset));

	Logger::log("ARM7 Entry Address: " + String::decToHex(this->arm7_entryAddress));

	Logger::log("ARM7 RAM Address: " + String::decToHex(this->arm7_ramAddress));

	Logger::log("ARM7 Size: " + String::decToHex(this->arm7_size));

	Logger::log("File Name Table (FNT) offset: " + String::decToHex(this->fntOffset));

	Logger::log("File Name Table (FNT) size: " + String::decToHex(this->fntSize));

	Logger::log("File Allocation Table (FAT) offset: " + String::decToHex(this->fatOffset));

	Logger::log("File Allocation Table (FAT) size: " + String::decToHex(this->fatSize));

	Logger::log("File ARM9 Overlay Offset: " + String::decToHex(this->file_arm9_overlayOffset));

	Logger::log("File ARM9 Overlay Size: " + String::decToHex(this->file_arm9_overlaySize));

	Logger::log("File ARM7 Overlay Offset: " + String::decToHex(this->file_arm7_overlayOffset));

	Logger::log("File ARM7 Overlay Size: " + String::decToHex(this->file_arm7_overlaySize));

	Logger::log("Port 40001A4h setting for normal commands: " + to_string(this->port_40001A4h_setting_normalCommands));

	Logger::log("Port 40001A4h setting for KEY1 commands: " + to_string(this->port_40001A4h_setting_key1Commands));

	Logger::log("Icon/Title Offset: " + String::decToHex(this->iconTitle_offset));

	Logger::log("Secure Area Checksum: " + to_string(this->secureAreaChecksum));

	Logger::log("Secure Area Delay: " + to_string(this->secureAreaDelay));

	Logger::log("ARM9 Auto Load List RAM Address: " + String::decToHex(this->arm9_autoLoadListRamAddress));

	Logger::log("ARM7 Auto Load List RAM Address: " + String::decToHex(this->arm7_autoLoadListRamAddress));

	Logger::log("Secure Area Disable: " + to_string(this->secureAreaDisable));

	Logger::log("Total Used ROM size: " + to_string(this->totalUsedROMSize));

	Logger::log("ROM Header Size: " + to_string(this->romHeaderSize));

	Logger::log("Reserved 2: " + String::toHexString(this->reserved_2, sizeof(this->reserved_2)));

	Logger::log("Nintendo Logo: " + String::toHexString(this->nintendoLogo, sizeof(this->nintendoLogo)));

	Logger::log("Nintendo Logo Checksum: " + to_string(this->nintendoLogoChecksum));

	Logger::log("Header Checksum: " + to_string(this->headerChecksum));

	Logger::log("Debug ROM Offset: " + String::decToHex(this->debug_romOffset));

	Logger::log("Debug size: " + String::decToHex(this->debug_size));

	Logger::log("Debug RAM Address: " + String::decToHex(this->debug_ramAddress));

	Logger::log("Reserved 3: " + String::toHexString(this->reserved_3, sizeof(this->reserved_3)));

	Logger::log("Reserved 4: " + String::toHexString(this->reserved_4, sizeof(this->reserved_4)));

	Logger::log("\n");
}

string DSCartridgeHeader::getGameTitle()
{
	return this->gameTitle;
}

string DSCartridgeHeader::getGamecode()
{
	return this->gamecode;
}

string DSCartridgeHeader::getMakercode()
{
	return this->makercode;
}

uint8_t DSCartridgeHeader::getUnitcode()
{
	return this->unitcode;
}

uint8_t DSCartridgeHeader::getEncryptionSeedSelect()
{
	return this->encryptionSeedSelect;
}

uint8_t DSCartridgeHeader::getDeviceCapacity()
{
	return this->deviceCapacity;
}

uint8_t* DSCartridgeHeader::getReserved_0()
{
	return this->reserved_0;
}

uint8_t DSCartridgeHeader::getReserved_1()
{
	return this->reserved_1;
}

uint8_t DSCartridgeHeader::getNDSRegion()
{
	return this->ndsRegion;
}

uint8_t DSCartridgeHeader::getROMVersion()
{
	return this->romVersion;
}

uint8_t DSCartridgeHeader::getAutostart()
{
	return this->autostart;
}

uint32_t DSCartridgeHeader::getARM9ROMOffset()
{
	return this->arm9_romOffset;
}

uint32_t DSCartridgeHeader::getARM9EntryAddress()
{
	return this->arm9_entryAddress;
}

uint32_t DSCartridgeHeader::getARM9RAMAddress()
{
	return this->arm9_ramAddress;
}

uint32_t DSCartridgeHeader::getARM9Size()
{
	return this->arm9_size;
}

uint32_t DSCartridgeHeader::getARM7ROMOffset()
{
	return this->arm7_romOffset;
}

uint32_t DSCartridgeHeader::getARM7EntryAddress()
{
	return this->arm7_entryAddress;
}

uint32_t DSCartridgeHeader::getARM7RAMAddress()
{
	return this->arm7_ramAddress;
}

uint32_t DSCartridgeHeader::getARM7Size()
{
	return this->arm7_size;
}

uint32_t DSCartridgeHeader::getFNTOffset()
{
	return this->fntOffset;
}

uint32_t DSCartridgeHeader::getFNTSize()
{
	return this->fntSize;
}

uint32_t DSCartridgeHeader::getFATOffset()
{
	return this->fatOffset;
}

uint32_t DSCartridgeHeader::getFATSize()
{
	return this->fatSize;
}

uint32_t DSCartridgeHeader::getFileARM9OverlayOffset()
{
	return this->file_arm9_overlayOffset;
}

uint32_t DSCartridgeHeader::getFileARM9OverlaySize()
{
	return this->file_arm9_overlaySize;
}

uint32_t DSCartridgeHeader::getFileARM7OverlayOffset()
{
	return this->file_arm7_overlayOffset;
}

uint32_t DSCartridgeHeader::getFileARM7OverlaySize()
{
	return this->file_arm7_overlaySize;
}

uint32_t DSCartridgeHeader::getPort40001A4hSettingNormalCommands()
{
	return this->port_40001A4h_setting_normalCommands;
}

uint32_t DSCartridgeHeader::getPort40001A4hSettingKey1Commands()
{
	return this->port_40001A4h_setting_key1Commands;
}

uint32_t DSCartridgeHeader::getIconTitleOffset()
{
	return this->iconTitle_offset;
}

uint16_t DSCartridgeHeader::getSecureAreaChecksum()
{
	return this->secureAreaChecksum;
}

uint16_t DSCartridgeHeader::getSecureAreaDelay()
{
	return this->secureAreaDelay;
}

uint32_t DSCartridgeHeader::getARM9AutoLoadListRAMAddress()
{
	return this->arm9_autoLoadListRamAddress;
}

uint32_t DSCartridgeHeader::getARM7AutoLoadListRAMAddress()
{
	return this->arm7_autoLoadListRamAddress;
}

uint64_t DSCartridgeHeader::getSecureAreaDisable()
{
	return this->secureAreaDisable;
}

uint32_t DSCartridgeHeader::getTotalUsedROMSize()
{
	return this->totalUsedROMSize;
}

uint32_t DSCartridgeHeader::getROMHeaderSize()
{
	return this->romHeaderSize;
}

uint8_t* DSCartridgeHeader::getReserved_2()
{
	return this->reserved_2;
}

uint8_t* DSCartridgeHeader::getNintendoLogo()
{
	return this->nintendoLogo;
}

uint16_t DSCartridgeHeader::getNintendoLogoChecksum()
{
	return this->nintendoLogoChecksum;
}

uint16_t DSCartridgeHeader::getHeaderChecksum()
{
	return this->headerChecksum;
}

uint32_t DSCartridgeHeader::getDebugROMOffset()
{
	return this->debug_romOffset;
}

uint32_t DSCartridgeHeader::getDebugSize()
{
	return this->debug_size;
}

uint32_t DSCartridgeHeader::getDebugRAMAddress()
{
	return this->debug_ramAddress;
}

uint8_t* DSCartridgeHeader::getReserved_3()
{
	return this->reserved_3;
}

uint8_t* DSCartridgeHeader::getReserved_4()
{
	return this->reserved_4;
}