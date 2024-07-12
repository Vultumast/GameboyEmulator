#include "pch.h"
#define EMULATOR_IMPORT
#include "../EmulatorLib/Framework.hpp"
#include "../EmulatorLib/RomInfo.hpp"

TEST(ROMInfoTest, SampleTestOne) {
    // Arrange
    uint8_t rom[8192] = { 0 };
    rom[0x149] = 0x03;

    // Act
    ROMInfo* rominfo = rominfo_create(rom, sizeof(rom));
    auto ramsize = rominfo_getramsize(rominfo);

    // Assert
    EXPECT_EQ(ramsize, 32000);
}

TEST(ROMInfoTest, SampleTestTwo) {
    // Arrange
    uint8_t rom[8192] = { 0 };
    rom[0x149] = 0x02;

    // Act
    ROMInfo info(rom, sizeof(rom));
    auto ramsize = info.GetRAMSize();

    // Assert
    EXPECT_EQ(ramsize, 8000);
}