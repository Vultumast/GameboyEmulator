#pragma once

#include <cstdint>

constexpr std::uint16_t Addr_ROM_Start = 0x0000;
constexpr std::uint16_t Addr_ROM_End = 0x3FFF;

constexpr std::uint16_t Addr_ROMSwap_Start = 0x4000;
constexpr std::uint16_t Addr_ROMSwap_End = 0x7FFF;

constexpr std::uint16_t Addr_VRAM_Start = 0x8000;
constexpr std::uint16_t Addr_VRAM_End = 0x9FFF;

constexpr std::uint16_t Addr_SRAM_Start = 0xA000;
constexpr std::uint16_t Addr_SRAM_End = 0xBFFF;

constexpr std::uint16_t Addr_ERAM_Start = 0xE000;
constexpr std::uint16_t Addr_ERAM_End = 0xFE9F;

constexpr std::uint16_t Addr_IORegisters_Start = 0xFF00;
constexpr std::uint16_t Addr_IORegisters_End = 0xFF7F;

constexpr std::uint16_t Addr_HRAM_Start = 0xFF80;
constexpr std::uint16_t Addr_HRAM_End = 0xFFFE;

constexpr std::uint16_t Addr_InterruptRegister = 0xFFFF;



constexpr std::uint16_t Reg_Joypad = 0xFF00;

constexpr std::uint16_t Reg_SerialTransfer_Start = 0xFF01;
constexpr std::uint16_t Reg_SerialTransfer_End = 0xFF02;

constexpr std::uint16_t Reg_Timer_Start = 0xFF04;
constexpr std::uint16_t Reg_Timer_End = 0xFF07;

constexpr std::uint16_t Reg_Audio_Start = 0xFF10;
constexpr std::uint16_t Reg_Audio_End = 0xFF26;

constexpr std::uint16_t Reg_WavePattern_Start = 0xFF30;
constexpr std::uint16_t Reg_WavePattern_End = 0xFF3F;

constexpr std::uint16_t Reg_LCDControl_Start = 0xFF40;
constexpr std::uint16_t Reg_LCDControl_End = 0xFF4B;

constexpr std::uint16_t Reg_VRAMBankSelect = 0xFF4F;

constexpr std::uint16_t Reg_DisableBootRom = 0xFF50;

constexpr std::uint16_t Reg_VRAMDMA_Start = 0xFF51;
constexpr std::uint16_t Reg_VRAMDMA_End = 0xFF55;

constexpr std::uint16_t Reg_BGOBJPalettes_Start = 0xFF68;
constexpr std::uint16_t Reg_BGOBJPalettes_End = 0xFF6B;

constexpr std::uint16_t Reg_WRAMBankSelect = 0xFF70;
