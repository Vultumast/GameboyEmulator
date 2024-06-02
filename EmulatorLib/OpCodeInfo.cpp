#include "OpCodeInfo.hpp"

OpCodeInfo OpCodes[256] =
{
	// 0x00 - 0x0F
	OpCodeInfo(0x00, OpCode::NOP, 1, 4),
	OpCodeInfo(0x01, OpCode::LD, 3, 12, OperandType::RegisterBC, OperandType::DataUINT16),
	OpCodeInfo(0x02, OpCode::LD, 1, 8, OperandType::RegisterBCIndirect, OperandType::Acculumator),
	OpCodeInfo(0x03, OpCode::INC, 1, 8, OperandType::RegisterBC),
	OpCodeInfo(0x04, OpCode::INC, 1, 4, OperandType::RegisterB),
	OpCodeInfo(0x05, OpCode::DEC, 1, 4, OperandType::RegisterB),
	OpCodeInfo(0x06, OpCode::LD, 2, 8, OperandType::RegisterB, OperandType::DataUINT8),
	OpCodeInfo(0x07, OpCode::RLCA, 1, 4),
	OpCodeInfo(0x08, OpCode::LD, 3, 20, OperandType::AddressUINT16, OperandType::Stackpointer),
	OpCodeInfo(0x09, OpCode::ADD, 1, 8),
	OpCodeInfo(0x0A, OpCode::LD, 1, 8, OperandType::Acculumator, OperandType::RegisterBCIndirect),
	OpCodeInfo(0x0B, OpCode::DEC, 1, 4, OperandType::RegisterBC),
	OpCodeInfo(0x0C, OpCode::INC, 1, 4, OperandType::RegisterC),
	OpCodeInfo(0x0D, OpCode::DEC, 1, 4, OperandType::RegisterC),
	OpCodeInfo(0x0E, OpCode::LD, 2, 8, OperandType::RegisterC, OperandType::DataUINT8),
	OpCodeInfo(0x0F, OpCode::RRCA, 1, 4),

	// 0x10 - 0x1F
	OpCodeInfo(0x10, OpCode::NOP, 1, 4),
	OpCodeInfo(0x11, OpCode::NOP, 1, 4),
	OpCodeInfo(0x12, OpCode::NOP, 1, 4),
	OpCodeInfo(0x13, OpCode::NOP, 1, 4),
	OpCodeInfo(0x14, OpCode::NOP, 1, 4),
	OpCodeInfo(0x15, OpCode::NOP, 1, 4),
	OpCodeInfo(0x16, OpCode::NOP, 1, 4),
	OpCodeInfo(0x17, OpCode::NOP, 1, 4),
	OpCodeInfo(0x18, OpCode::NOP, 1, 4),
	OpCodeInfo(0x19, OpCode::NOP, 1, 4),
	OpCodeInfo(0x1A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x1B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x1C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x1D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x1E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x1F, OpCode::NOP, 1, 4),

	// 0x20 - 0x2F
	OpCodeInfo(0x20, OpCode::NOP, 1, 4),
	OpCodeInfo(0x21, OpCode::NOP, 1, 4),
	OpCodeInfo(0x22, OpCode::NOP, 1, 4),
	OpCodeInfo(0x23, OpCode::NOP, 1, 4),
	OpCodeInfo(0x24, OpCode::NOP, 1, 4),
	OpCodeInfo(0x25, OpCode::NOP, 1, 4),
	OpCodeInfo(0x26, OpCode::NOP, 1, 4),
	OpCodeInfo(0x27, OpCode::NOP, 1, 4),
	OpCodeInfo(0x28, OpCode::NOP, 1, 4),
	OpCodeInfo(0x29, OpCode::NOP, 1, 4),
	OpCodeInfo(0x2A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x2B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x2C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x2D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x2E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x2F, OpCode::NOP, 1, 4),

	// 0x30 - 0x3F
	OpCodeInfo(0x30, OpCode::NOP, 1, 4),
	OpCodeInfo(0x31, OpCode::NOP, 1, 4),
	OpCodeInfo(0x32, OpCode::NOP, 1, 4),
	OpCodeInfo(0x33, OpCode::NOP, 1, 4),
	OpCodeInfo(0x34, OpCode::NOP, 1, 4),
	OpCodeInfo(0x35, OpCode::NOP, 1, 4),
	OpCodeInfo(0x36, OpCode::NOP, 1, 4),
	OpCodeInfo(0x37, OpCode::NOP, 1, 4),
	OpCodeInfo(0x38, OpCode::NOP, 1, 4),
	OpCodeInfo(0x39, OpCode::NOP, 1, 4),
	OpCodeInfo(0x3A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x3B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x3C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x3D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x3E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x3F, OpCode::NOP, 1, 4),

	// 0x40 - 0x4F
	OpCodeInfo(0x40, OpCode::NOP, 1, 4),
	OpCodeInfo(0x41, OpCode::NOP, 1, 4),
	OpCodeInfo(0x42, OpCode::NOP, 1, 4),
	OpCodeInfo(0x43, OpCode::NOP, 1, 4),
	OpCodeInfo(0x44, OpCode::NOP, 1, 4),
	OpCodeInfo(0x45, OpCode::NOP, 1, 4),
	OpCodeInfo(0x46, OpCode::NOP, 1, 4),
	OpCodeInfo(0x47, OpCode::NOP, 1, 4),
	OpCodeInfo(0x48, OpCode::NOP, 1, 4),
	OpCodeInfo(0x49, OpCode::NOP, 1, 4),
	OpCodeInfo(0x4A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x4B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x4C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x4D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x4E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x4F, OpCode::NOP, 1, 4),

	// 0x50 - 0x5F
	OpCodeInfo(0x50, OpCode::NOP, 1, 4),
	OpCodeInfo(0x51, OpCode::NOP, 1, 4),
	OpCodeInfo(0x52, OpCode::NOP, 1, 4),
	OpCodeInfo(0x53, OpCode::NOP, 1, 4),
	OpCodeInfo(0x54, OpCode::NOP, 1, 4),
	OpCodeInfo(0x55, OpCode::NOP, 1, 4),
	OpCodeInfo(0x56, OpCode::NOP, 1, 4),
	OpCodeInfo(0x57, OpCode::NOP, 1, 4),
	OpCodeInfo(0x58, OpCode::NOP, 1, 4),
	OpCodeInfo(0x59, OpCode::NOP, 1, 4),
	OpCodeInfo(0x5A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x5B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x5C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x5D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x5E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x5F, OpCode::NOP, 1, 4),

	// 0x60 - 0x6F
	OpCodeInfo(0x60, OpCode::NOP, 1, 4),
	OpCodeInfo(0x61, OpCode::NOP, 1, 4),
	OpCodeInfo(0x62, OpCode::NOP, 1, 4),
	OpCodeInfo(0x63, OpCode::NOP, 1, 4),
	OpCodeInfo(0x64, OpCode::NOP, 1, 4),
	OpCodeInfo(0x65, OpCode::NOP, 1, 4),
	OpCodeInfo(0x66, OpCode::NOP, 1, 4),
	OpCodeInfo(0x67, OpCode::NOP, 1, 4),
	OpCodeInfo(0x68, OpCode::NOP, 1, 4),
	OpCodeInfo(0x69, OpCode::NOP, 1, 4),
	OpCodeInfo(0x6A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x6B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x6C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x6D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x6E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x6F, OpCode::NOP, 1, 4),

	// 0x70 - 0x7F
	OpCodeInfo(0x70, OpCode::NOP, 1, 4),
	OpCodeInfo(0x71, OpCode::NOP, 1, 4),
	OpCodeInfo(0x72, OpCode::NOP, 1, 4),
	OpCodeInfo(0x73, OpCode::NOP, 1, 4),
	OpCodeInfo(0x74, OpCode::NOP, 1, 4),
	OpCodeInfo(0x75, OpCode::NOP, 1, 4),
	OpCodeInfo(0x76, OpCode::NOP, 1, 4),
	OpCodeInfo(0x77, OpCode::NOP, 1, 4),
	OpCodeInfo(0x78, OpCode::NOP, 1, 4),
	OpCodeInfo(0x79, OpCode::NOP, 1, 4),
	OpCodeInfo(0x7A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x7B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x7C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x7D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x7E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x7F, OpCode::NOP, 1, 4),

	// 0x80 - 0x8F
	OpCodeInfo(0x80, OpCode::NOP, 1, 4),
	OpCodeInfo(0x81, OpCode::NOP, 1, 4),
	OpCodeInfo(0x82, OpCode::NOP, 1, 4),
	OpCodeInfo(0x83, OpCode::NOP, 1, 4),
	OpCodeInfo(0x84, OpCode::NOP, 1, 4),
	OpCodeInfo(0x85, OpCode::NOP, 1, 4),
	OpCodeInfo(0x86, OpCode::NOP, 1, 4),
	OpCodeInfo(0x87, OpCode::NOP, 1, 4),
	OpCodeInfo(0x88, OpCode::NOP, 1, 4),
	OpCodeInfo(0x89, OpCode::NOP, 1, 4),
	OpCodeInfo(0x8A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x8B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x8C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x8D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x8E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x8F, OpCode::NOP, 1, 4),

	// 0x90 - 0x9F
	OpCodeInfo(0x90, OpCode::NOP, 1, 4),
	OpCodeInfo(0x91, OpCode::NOP, 1, 4),
	OpCodeInfo(0x92, OpCode::NOP, 1, 4),
	OpCodeInfo(0x93, OpCode::NOP, 1, 4),
	OpCodeInfo(0x94, OpCode::NOP, 1, 4),
	OpCodeInfo(0x95, OpCode::NOP, 1, 4),
	OpCodeInfo(0x96, OpCode::NOP, 1, 4),
	OpCodeInfo(0x97, OpCode::NOP, 1, 4),
	OpCodeInfo(0x98, OpCode::NOP, 1, 4),
	OpCodeInfo(0x99, OpCode::NOP, 1, 4),
	OpCodeInfo(0x9A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x9B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x9C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x9D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x9E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x9F, OpCode::NOP, 1, 4),

	// 0xA0 - 0xAF
	OpCodeInfo(0xA0, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA1, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA2, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA3, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA4, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA5, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA6, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA7, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA8, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA9, OpCode::NOP, 1, 4),
	OpCodeInfo(0xAA, OpCode::NOP, 1, 4),
	OpCodeInfo(0xAB, OpCode::NOP, 1, 4),
	OpCodeInfo(0xAC, OpCode::NOP, 1, 4),
	OpCodeInfo(0xAD, OpCode::NOP, 1, 4),
	OpCodeInfo(0xAE, OpCode::NOP, 1, 4),
	OpCodeInfo(0xAF, OpCode::NOP, 1, 4),

	// 0xB0 - 0xBF
	OpCodeInfo(0xB0, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB1, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB2, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB3, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB4, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB5, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB6, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB7, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB8, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB9, OpCode::NOP, 1, 4),
	OpCodeInfo(0xBA, OpCode::NOP, 1, 4),
	OpCodeInfo(0xBB, OpCode::NOP, 1, 4),
	OpCodeInfo(0xBC, OpCode::NOP, 1, 4),
	OpCodeInfo(0xBD, OpCode::NOP, 1, 4),
	OpCodeInfo(0xBE, OpCode::NOP, 1, 4),
	OpCodeInfo(0xBF, OpCode::NOP, 1, 4),

	// 0xC0 - 0xCF
	OpCodeInfo(0xC0, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC1, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC2, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC3, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC4, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC5, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC6, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC7, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC8, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC9, OpCode::NOP, 1, 4),
	OpCodeInfo(0xCA, OpCode::NOP, 1, 4),
	OpCodeInfo(0xCB, OpCode::NOP, 1, 4),
	OpCodeInfo(0xCC, OpCode::NOP, 1, 4),
	OpCodeInfo(0xCD, OpCode::NOP, 1, 4),
	OpCodeInfo(0xCE, OpCode::NOP, 1, 4),
	OpCodeInfo(0xCF, OpCode::NOP, 1, 4),

	// 0xD0 - 0xDF
	OpCodeInfo(0xD0, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD1, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD2, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD3, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD4, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD5, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD6, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD7, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD8, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD9, OpCode::NOP, 1, 4),
	OpCodeInfo(0xDA, OpCode::NOP, 1, 4),
	OpCodeInfo(0xDB, OpCode::NOP, 1, 4),
	OpCodeInfo(0xDC, OpCode::NOP, 1, 4),
	OpCodeInfo(0xDD, OpCode::NOP, 1, 4),
	OpCodeInfo(0xDE, OpCode::NOP, 1, 4),
	OpCodeInfo(0xDF, OpCode::NOP, 1, 4),

	// 0xE0 - 0xEF
	OpCodeInfo(0xE0, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE1, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE2, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE3, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE4, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE5, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE6, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE7, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE8, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE9, OpCode::NOP, 1, 4),
	OpCodeInfo(0xEA, OpCode::NOP, 1, 4),
	OpCodeInfo(0xEB, OpCode::NOP, 1, 4),
	OpCodeInfo(0xEC, OpCode::NOP, 1, 4),
	OpCodeInfo(0xED, OpCode::NOP, 1, 4),
	OpCodeInfo(0xEE, OpCode::NOP, 1, 4),
	OpCodeInfo(0xEF, OpCode::NOP, 1, 4),

	// 0xF0 - 0xFF
	OpCodeInfo(0xF0, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF1, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF2, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF3, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF4, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF5, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF6, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF7, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF8, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF9, OpCode::NOP, 1, 4),
	OpCodeInfo(0xFA, OpCode::NOP, 1, 4),
	OpCodeInfo(0xFB, OpCode::NOP, 1, 4),
	OpCodeInfo(0xFC, OpCode::NOP, 1, 4),
	OpCodeInfo(0xFD, OpCode::NOP, 1, 4),
	OpCodeInfo(0xFE, OpCode::NOP, 1, 4),
	OpCodeInfo(0xFF, OpCode::NOP, 1, 4)
};



OpCodeInfo OpCodesCB[256] =
{
	// 0x00 - 0x0F
	OpCodeInfo(0x00, OpCode::RLC, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x01, OpCode::NOP, 1, 4),
	OpCodeInfo(0x02, OpCode::NOP, 1, 4),
	OpCodeInfo(0x03, OpCode::NOP, 1, 4),
	OpCodeInfo(0x04, OpCode::NOP, 1, 4),
	OpCodeInfo(0x05, OpCode::NOP, 1, 4),
	OpCodeInfo(0x06, OpCode::NOP, 1, 4),
	OpCodeInfo(0x07, OpCode::NOP, 1, 4),
	OpCodeInfo(0x08, OpCode::NOP, 1, 4),
	OpCodeInfo(0x09, OpCode::NOP, 1, 4),
	OpCodeInfo(0x0A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x0B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x0C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x0D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x0E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x0F, OpCode::NOP, 1, 4),

	// 0x10 - 0x1F
	OpCodeInfo(0x10, OpCode::NOP, 1, 4),
	OpCodeInfo(0x11, OpCode::NOP, 1, 4),
	OpCodeInfo(0x12, OpCode::NOP, 1, 4),
	OpCodeInfo(0x13, OpCode::NOP, 1, 4),
	OpCodeInfo(0x14, OpCode::NOP, 1, 4),
	OpCodeInfo(0x15, OpCode::NOP, 1, 4),
	OpCodeInfo(0x16, OpCode::NOP, 1, 4),
	OpCodeInfo(0x17, OpCode::NOP, 1, 4),
	OpCodeInfo(0x18, OpCode::NOP, 1, 4),
	OpCodeInfo(0x19, OpCode::NOP, 1, 4),
	OpCodeInfo(0x1A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x1B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x1C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x1D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x1E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x1F, OpCode::NOP, 1, 4),

	// 0x20 - 0x2F
	OpCodeInfo(0x20, OpCode::NOP, 1, 4),
	OpCodeInfo(0x21, OpCode::NOP, 1, 4),
	OpCodeInfo(0x22, OpCode::NOP, 1, 4),
	OpCodeInfo(0x23, OpCode::NOP, 1, 4),
	OpCodeInfo(0x24, OpCode::NOP, 1, 4),
	OpCodeInfo(0x25, OpCode::NOP, 1, 4),
	OpCodeInfo(0x26, OpCode::NOP, 1, 4),
	OpCodeInfo(0x27, OpCode::NOP, 1, 4),
	OpCodeInfo(0x28, OpCode::NOP, 1, 4),
	OpCodeInfo(0x29, OpCode::NOP, 1, 4),
	OpCodeInfo(0x2A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x2B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x2C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x2D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x2E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x2F, OpCode::NOP, 1, 4),

	// 0x30 - 0x3F
	OpCodeInfo(0x30, OpCode::NOP, 1, 4),
	OpCodeInfo(0x31, OpCode::NOP, 1, 4),
	OpCodeInfo(0x32, OpCode::NOP, 1, 4),
	OpCodeInfo(0x33, OpCode::NOP, 1, 4),
	OpCodeInfo(0x34, OpCode::NOP, 1, 4),
	OpCodeInfo(0x35, OpCode::NOP, 1, 4),
	OpCodeInfo(0x36, OpCode::NOP, 1, 4),
	OpCodeInfo(0x37, OpCode::NOP, 1, 4),
	OpCodeInfo(0x38, OpCode::NOP, 1, 4),
	OpCodeInfo(0x39, OpCode::NOP, 1, 4),
	OpCodeInfo(0x3A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x3B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x3C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x3D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x3E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x3F, OpCode::NOP, 1, 4),

	// 0x40 - 0x4F
	OpCodeInfo(0x40, OpCode::NOP, 1, 4),
	OpCodeInfo(0x41, OpCode::NOP, 1, 4),
	OpCodeInfo(0x42, OpCode::NOP, 1, 4),
	OpCodeInfo(0x43, OpCode::NOP, 1, 4),
	OpCodeInfo(0x44, OpCode::NOP, 1, 4),
	OpCodeInfo(0x45, OpCode::NOP, 1, 4),
	OpCodeInfo(0x46, OpCode::NOP, 1, 4),
	OpCodeInfo(0x47, OpCode::NOP, 1, 4),
	OpCodeInfo(0x48, OpCode::NOP, 1, 4),
	OpCodeInfo(0x49, OpCode::NOP, 1, 4),
	OpCodeInfo(0x4A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x4B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x4C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x4D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x4E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x4F, OpCode::NOP, 1, 4),

	// 0x50 - 0x5F
	OpCodeInfo(0x50, OpCode::NOP, 1, 4),
	OpCodeInfo(0x51, OpCode::NOP, 1, 4),
	OpCodeInfo(0x52, OpCode::NOP, 1, 4),
	OpCodeInfo(0x53, OpCode::NOP, 1, 4),
	OpCodeInfo(0x54, OpCode::NOP, 1, 4),
	OpCodeInfo(0x55, OpCode::NOP, 1, 4),
	OpCodeInfo(0x56, OpCode::NOP, 1, 4),
	OpCodeInfo(0x57, OpCode::NOP, 1, 4),
	OpCodeInfo(0x58, OpCode::NOP, 1, 4),
	OpCodeInfo(0x59, OpCode::NOP, 1, 4),
	OpCodeInfo(0x5A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x5B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x5C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x5D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x5E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x5F, OpCode::NOP, 1, 4),

	// 0x60 - 0x6F
	OpCodeInfo(0x60, OpCode::NOP, 1, 4),
	OpCodeInfo(0x61, OpCode::NOP, 1, 4),
	OpCodeInfo(0x62, OpCode::NOP, 1, 4),
	OpCodeInfo(0x63, OpCode::NOP, 1, 4),
	OpCodeInfo(0x64, OpCode::NOP, 1, 4),
	OpCodeInfo(0x65, OpCode::NOP, 1, 4),
	OpCodeInfo(0x66, OpCode::NOP, 1, 4),
	OpCodeInfo(0x67, OpCode::NOP, 1, 4),
	OpCodeInfo(0x68, OpCode::NOP, 1, 4),
	OpCodeInfo(0x69, OpCode::NOP, 1, 4),
	OpCodeInfo(0x6A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x6B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x6C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x6D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x6E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x6F, OpCode::NOP, 1, 4),

	// 0x70 - 0x7F
	OpCodeInfo(0x70, OpCode::NOP, 1, 4),
	OpCodeInfo(0x71, OpCode::NOP, 1, 4),
	OpCodeInfo(0x72, OpCode::NOP, 1, 4),
	OpCodeInfo(0x73, OpCode::NOP, 1, 4),
	OpCodeInfo(0x74, OpCode::NOP, 1, 4),
	OpCodeInfo(0x75, OpCode::NOP, 1, 4),
	OpCodeInfo(0x76, OpCode::NOP, 1, 4),
	OpCodeInfo(0x77, OpCode::NOP, 1, 4),
	OpCodeInfo(0x78, OpCode::NOP, 1, 4),
	OpCodeInfo(0x79, OpCode::NOP, 1, 4),
	OpCodeInfo(0x7A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x7B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x7C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x7D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x7E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x7F, OpCode::NOP, 1, 4),

	// 0x80 - 0x8F
	OpCodeInfo(0x80, OpCode::NOP, 1, 4),
	OpCodeInfo(0x81, OpCode::NOP, 1, 4),
	OpCodeInfo(0x82, OpCode::NOP, 1, 4),
	OpCodeInfo(0x83, OpCode::NOP, 1, 4),
	OpCodeInfo(0x84, OpCode::NOP, 1, 4),
	OpCodeInfo(0x85, OpCode::NOP, 1, 4),
	OpCodeInfo(0x86, OpCode::NOP, 1, 4),
	OpCodeInfo(0x87, OpCode::NOP, 1, 4),
	OpCodeInfo(0x88, OpCode::NOP, 1, 4),
	OpCodeInfo(0x89, OpCode::NOP, 1, 4),
	OpCodeInfo(0x8A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x8B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x8C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x8D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x8E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x8F, OpCode::NOP, 1, 4),

	// 0x90 - 0x9F
	OpCodeInfo(0x90, OpCode::NOP, 1, 4),
	OpCodeInfo(0x91, OpCode::NOP, 1, 4),
	OpCodeInfo(0x92, OpCode::NOP, 1, 4),
	OpCodeInfo(0x93, OpCode::NOP, 1, 4),
	OpCodeInfo(0x94, OpCode::NOP, 1, 4),
	OpCodeInfo(0x95, OpCode::NOP, 1, 4),
	OpCodeInfo(0x96, OpCode::NOP, 1, 4),
	OpCodeInfo(0x97, OpCode::NOP, 1, 4),
	OpCodeInfo(0x98, OpCode::NOP, 1, 4),
	OpCodeInfo(0x99, OpCode::NOP, 1, 4),
	OpCodeInfo(0x9A, OpCode::NOP, 1, 4),
	OpCodeInfo(0x9B, OpCode::NOP, 1, 4),
	OpCodeInfo(0x9C, OpCode::NOP, 1, 4),
	OpCodeInfo(0x9D, OpCode::NOP, 1, 4),
	OpCodeInfo(0x9E, OpCode::NOP, 1, 4),
	OpCodeInfo(0x9F, OpCode::NOP, 1, 4),

	// 0xA0 - 0xAF
	OpCodeInfo(0xA0, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA1, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA2, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA3, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA4, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA5, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA6, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA7, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA8, OpCode::NOP, 1, 4),
	OpCodeInfo(0xA9, OpCode::NOP, 1, 4),
	OpCodeInfo(0xAA, OpCode::NOP, 1, 4),
	OpCodeInfo(0xAB, OpCode::NOP, 1, 4),
	OpCodeInfo(0xAC, OpCode::NOP, 1, 4),
	OpCodeInfo(0xAD, OpCode::NOP, 1, 4),
	OpCodeInfo(0xAE, OpCode::NOP, 1, 4),
	OpCodeInfo(0xAF, OpCode::NOP, 1, 4),

	// 0xB0 - 0xBF
	OpCodeInfo(0xB0, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB1, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB2, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB3, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB4, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB5, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB6, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB7, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB8, OpCode::NOP, 1, 4),
	OpCodeInfo(0xB9, OpCode::NOP, 1, 4),
	OpCodeInfo(0xBA, OpCode::NOP, 1, 4),
	OpCodeInfo(0xBB, OpCode::NOP, 1, 4),
	OpCodeInfo(0xBC, OpCode::NOP, 1, 4),
	OpCodeInfo(0xBD, OpCode::NOP, 1, 4),
	OpCodeInfo(0xBE, OpCode::NOP, 1, 4),
	OpCodeInfo(0xBF, OpCode::NOP, 1, 4),

	// 0xC0 - 0xCF
	OpCodeInfo(0xC0, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC1, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC2, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC3, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC4, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC5, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC6, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC7, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC8, OpCode::NOP, 1, 4),
	OpCodeInfo(0xC9, OpCode::NOP, 1, 4),
	OpCodeInfo(0xCA, OpCode::NOP, 1, 4),
	OpCodeInfo(0xCB, OpCode::NOP, 1, 4),
	OpCodeInfo(0xCC, OpCode::NOP, 1, 4),
	OpCodeInfo(0xCD, OpCode::NOP, 1, 4),
	OpCodeInfo(0xCE, OpCode::NOP, 1, 4),
	OpCodeInfo(0xCF, OpCode::NOP, 1, 4),

	// 0xD0 - 0xDF
	OpCodeInfo(0xD0, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD1, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD2, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD3, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD4, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD5, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD6, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD7, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD8, OpCode::NOP, 1, 4),
	OpCodeInfo(0xD9, OpCode::NOP, 1, 4),
	OpCodeInfo(0xDA, OpCode::NOP, 1, 4),
	OpCodeInfo(0xDB, OpCode::NOP, 1, 4),
	OpCodeInfo(0xDC, OpCode::NOP, 1, 4),
	OpCodeInfo(0xDD, OpCode::NOP, 1, 4),
	OpCodeInfo(0xDE, OpCode::NOP, 1, 4),
	OpCodeInfo(0xDF, OpCode::NOP, 1, 4),

	// 0xE0 - 0xEF
	OpCodeInfo(0xE0, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE1, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE2, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE3, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE4, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE5, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE6, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE7, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE8, OpCode::NOP, 1, 4),
	OpCodeInfo(0xE9, OpCode::NOP, 1, 4),
	OpCodeInfo(0xEA, OpCode::NOP, 1, 4),
	OpCodeInfo(0xEB, OpCode::NOP, 1, 4),
	OpCodeInfo(0xEC, OpCode::NOP, 1, 4),
	OpCodeInfo(0xED, OpCode::NOP, 1, 4),
	OpCodeInfo(0xEE, OpCode::NOP, 1, 4),
	OpCodeInfo(0xEF, OpCode::NOP, 1, 4),

	// 0xF0 - 0xFF
	OpCodeInfo(0xF0, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF1, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF2, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF3, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF4, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF5, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF6, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF7, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF8, OpCode::NOP, 1, 4),
	OpCodeInfo(0xF9, OpCode::NOP, 1, 4),
	OpCodeInfo(0xFA, OpCode::NOP, 1, 4),
	OpCodeInfo(0xFB, OpCode::NOP, 1, 4),
	OpCodeInfo(0xFC, OpCode::NOP, 1, 4),
	OpCodeInfo(0xFD, OpCode::NOP, 1, 4),
	OpCodeInfo(0xFE, OpCode::NOP, 1, 4),
	OpCodeInfo(0xFF, OpCode::NOP, 1, 4)
};
