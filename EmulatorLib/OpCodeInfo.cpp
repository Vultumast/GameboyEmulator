#include "OpCodeInfo.hpp"

OpCodeInfo OpCodeInfo::OpCodes[256] =
{
	// 0x00 - 0x0F
	OpCodeInfo(0x00, OpCode::NOP, 1, 4),
	OpCodeInfo(0x01, OpCode::LD,  3, 12, OperandType::RegisterBC, OperandType::DataUINT16),
	OpCodeInfo(0x02, OpCode::LD,  1, 8, OperandType::RegisterBCIndirect, OperandType::Acculumator),
	OpCodeInfo(0x03, OpCode::INC, 1, 8, OperandType::RegisterBC),
	OpCodeInfo(0x04, OpCode::INC, 1, 4, OperandType::RegisterB),
	OpCodeInfo(0x05, OpCode::DEC, 1, 4, OperandType::RegisterB),
	OpCodeInfo(0x06, OpCode::LD,  2, 8, OperandType::RegisterB, OperandType::DataUINT8),
	OpCodeInfo(0x07, OpCode::RLCA,1, 4),
	OpCodeInfo(0x08, OpCode::LD,  3, 20, OperandType::AddressUINT16, OperandType::Stackpointer),
	OpCodeInfo(0x09, OpCode::ADD, 1, 8),
	OpCodeInfo(0x0A, OpCode::LD,  1, 8, OperandType::Acculumator, OperandType::RegisterBCIndirect),
	OpCodeInfo(0x0B, OpCode::DEC, 1, 8, OperandType::RegisterBC),
	OpCodeInfo(0x0C, OpCode::INC, 1, 4, OperandType::RegisterC),
	OpCodeInfo(0x0D, OpCode::DEC, 1, 4, OperandType::RegisterC),
	OpCodeInfo(0x0E, OpCode::LD,  2, 8, OperandType::RegisterC, OperandType::DataUINT8),
	OpCodeInfo(0x0F, OpCode::RRCA,1, 4),

	// 0x10 - 0x1F
	OpCodeInfo(0x10, OpCode::STOP,2, 4),
	OpCodeInfo(0x11, OpCode::LD,  3, 12, OperandType::RegisterDE, OperandType::DataUINT16),
	OpCodeInfo(0x12, OpCode::LD,  1, 8, OperandType::RegisterDEIndirect, OperandType::Acculumator),
	OpCodeInfo(0x13, OpCode::INC, 1, 8, OperandType::RegisterDE),
	OpCodeInfo(0x14, OpCode::INC, 1, 4, OperandType::RegisterD),
	OpCodeInfo(0x15, OpCode::DEC, 1, 4, OperandType::RegisterD),
	OpCodeInfo(0x16, OpCode::LD,  2, 8, OperandType::RegisterD, OperandType::DataUINT8),
	OpCodeInfo(0x17, OpCode::RLA, 1, 4),
	OpCodeInfo(0x18, OpCode::JR,  2, 12, OperandType::DataINT8),
	OpCodeInfo(0x19, OpCode::ADD, 1, 8, OperandType::RegisterHL, OperandType::RegisterDE),
	OpCodeInfo(0x1A, OpCode::LD,  1, 8, OperandType::Acculumator, OperandType::RegisterDEIndirect),
	OpCodeInfo(0x1B, OpCode::DEC, 1, 8, OperandType::RegisterDE),
	OpCodeInfo(0x1C, OpCode::INC, 1, 4, OperandType::RegisterE),
	OpCodeInfo(0x1D, OpCode::DEC, 1, 4, OperandType::RegisterE),
	OpCodeInfo(0x1E, OpCode::LD,  2, 8, OperandType::RegisterC, OperandType::DataUINT8),
	OpCodeInfo(0x1F, OpCode::RRA, 1, 4),

	// 0x20 - 0x2F
	OpCodeInfo(0x20, OpCode::JR,  2, 8, OperandType::FlagNotZero, OperandType::DataINT8, 12),
	OpCodeInfo(0x21, OpCode::LD,  3, 12, OperandType::RegisterHL, OperandType::DataUINT16),
	OpCodeInfo(0x22, OpCode::LD,  1, 8, OperandType::IncrementHL, OperandType::Acculumator),
	OpCodeInfo(0x23, OpCode::INC, 1, 8, OperandType::RegisterHL),
	OpCodeInfo(0x24, OpCode::INC, 1, 4, OperandType::RegisterH),
	OpCodeInfo(0x25, OpCode::DEC, 1, 4, OperandType::RegisterH),
	OpCodeInfo(0x26, OpCode::LD,  2, 8, OperandType::RegisterH, OperandType::DataINT8),
	OpCodeInfo(0x27, OpCode::DAA, 1, 4),
	OpCodeInfo(0x28, OpCode::JR,  2, 8, OperandType::FlagZero, OperandType::DataINT8, 12),
	OpCodeInfo(0x29, OpCode::ADD, 1, 8, OperandType::RegisterHL, OperandType::RegisterHL),
	OpCodeInfo(0x2A, OpCode::LD,  1, 8, OperandType::Acculumator, OperandType::IncrementHL),
	OpCodeInfo(0x2B, OpCode::DEC, 1, 8, OperandType::RegisterHL),
	OpCodeInfo(0x2C, OpCode::INC, 1, 4, OperandType::RegisterL),
	OpCodeInfo(0x2D, OpCode::DEC, 1, 4, OperandType::RegisterL),
	OpCodeInfo(0x2E, OpCode::LD,  2, 8, OperandType::RegisterL, OperandType::DataUINT8),
	OpCodeInfo(0x2F, OpCode::CPL, 1, 4),

	// 0x30 - 0x3F
	OpCodeInfo(0x30, OpCode::JR,  2, 8, OperandType::FlagNotCarry, OperandType::DataINT8, 12),
	OpCodeInfo(0x31, OpCode::LD,  3, 12, OperandType::Stackpointer, OperandType::DataUINT16),
	OpCodeInfo(0x32, OpCode::LD,  1, 8, OperandType::DecrementHL, OperandType::Acculumator),
	OpCodeInfo(0x33, OpCode::INC, 1, 8, OperandType::Stackpointer),
	OpCodeInfo(0x34, OpCode::INC, 1, 12, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x35, OpCode::DEC, 1, 12, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x36, OpCode::LD,  2, 12, OperandType::RegisterHLIndirect, OperandType::DataUINT8),
	OpCodeInfo(0x37, OpCode::SCF, 1, 4),
	OpCodeInfo(0x38, OpCode::JR,  2, 8, OperandType::FlagCarry, OperandType::DataINT8, 12),
	OpCodeInfo(0x39, OpCode::ADD, 1, 8, OperandType::RegisterHL, OperandType::Stackpointer),
	OpCodeInfo(0x3A, OpCode::LD,  1, 8, OperandType::Acculumator, OperandType::DecrementHL),
	OpCodeInfo(0x3B, OpCode::DEC, 1, 8, OperandType::Stackpointer),
	OpCodeInfo(0x3C, OpCode::INC, 1, 4, OperandType::Acculumator),
	OpCodeInfo(0x3D, OpCode::DEC, 1, 4, OperandType::Acculumator),
	OpCodeInfo(0x3E, OpCode::LD,  2, 8,  OperandType::Acculumator, OperandType::DataUINT8),
	OpCodeInfo(0x3F, OpCode::CCF, 1, 4),

	// 0x40 - 0x4F
	OpCodeInfo(0x40, OpCode::LD, 1, 4, OperandType::RegisterB, OperandType::RegisterB),
	OpCodeInfo(0x41, OpCode::LD, 1, 4, OperandType::RegisterB, OperandType::RegisterC),
	OpCodeInfo(0x42, OpCode::LD, 1, 4, OperandType::RegisterB, OperandType::RegisterD),
	OpCodeInfo(0x43, OpCode::LD, 1, 4, OperandType::RegisterB, OperandType::RegisterE),
	OpCodeInfo(0x44, OpCode::LD, 1, 4, OperandType::RegisterB, OperandType::RegisterH),
	OpCodeInfo(0x45, OpCode::LD, 1, 4, OperandType::RegisterB, OperandType::RegisterL),
	OpCodeInfo(0x46, OpCode::LD, 1, 4, OperandType::RegisterB, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x47, OpCode::LD, 1, 4, OperandType::RegisterB, OperandType::Acculumator),
	OpCodeInfo(0x48, OpCode::LD, 1, 4, OperandType::RegisterC, OperandType::RegisterB),
	OpCodeInfo(0x49, OpCode::LD, 1, 4, OperandType::RegisterC, OperandType::RegisterC),
	OpCodeInfo(0x4A, OpCode::LD, 1, 4, OperandType::RegisterC, OperandType::RegisterD),
	OpCodeInfo(0x4B, OpCode::LD, 1, 4, OperandType::RegisterC, OperandType::RegisterE),
	OpCodeInfo(0x4C, OpCode::LD, 1, 4, OperandType::RegisterC, OperandType::RegisterH),
	OpCodeInfo(0x4D, OpCode::LD, 1, 4, OperandType::RegisterC, OperandType::RegisterL),
	OpCodeInfo(0x4E, OpCode::LD, 1, 4, OperandType::RegisterC, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x4F, OpCode::LD, 1, 4, OperandType::RegisterC, OperandType::Acculumator),

	// 0x50 - 0x5F
	OpCodeInfo(0x50, OpCode::LD, 1, 4, OperandType::RegisterD, OperandType::RegisterB),
	OpCodeInfo(0x51, OpCode::LD, 1, 4, OperandType::RegisterD, OperandType::RegisterC),
	OpCodeInfo(0x52, OpCode::LD, 1, 4, OperandType::RegisterD, OperandType::RegisterD),
	OpCodeInfo(0x53, OpCode::LD, 1, 4, OperandType::RegisterD, OperandType::RegisterE),
	OpCodeInfo(0x54, OpCode::LD, 1, 4, OperandType::RegisterD, OperandType::RegisterH),
	OpCodeInfo(0x55, OpCode::LD, 1, 4, OperandType::RegisterD, OperandType::RegisterL),
	OpCodeInfo(0x56, OpCode::LD, 1, 4, OperandType::RegisterD, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x57, OpCode::LD, 1, 4, OperandType::RegisterD, OperandType::Acculumator),
	OpCodeInfo(0x58, OpCode::LD, 1, 4, OperandType::RegisterE, OperandType::RegisterB),
	OpCodeInfo(0x59, OpCode::LD, 1, 4, OperandType::RegisterE, OperandType::RegisterC),
	OpCodeInfo(0x5A, OpCode::LD, 1, 4, OperandType::RegisterE, OperandType::RegisterD),
	OpCodeInfo(0x5B, OpCode::LD, 1, 4, OperandType::RegisterE, OperandType::RegisterE),
	OpCodeInfo(0x5C, OpCode::LD, 1, 4, OperandType::RegisterE, OperandType::RegisterH),
	OpCodeInfo(0x5D, OpCode::LD, 1, 4, OperandType::RegisterE, OperandType::RegisterL),
	OpCodeInfo(0x5E, OpCode::LD, 1, 4, OperandType::RegisterE, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x5F, OpCode::LD, 1, 4, OperandType::RegisterE, OperandType::Acculumator),

	// 0x60 - 0x6F
	OpCodeInfo(0x60, OpCode::LD, 1, 4, OperandType::RegisterH, OperandType::RegisterB),
	OpCodeInfo(0x61, OpCode::LD, 1, 4, OperandType::RegisterH, OperandType::RegisterC),
	OpCodeInfo(0x62, OpCode::LD, 1, 4, OperandType::RegisterH, OperandType::RegisterD),
	OpCodeInfo(0x63, OpCode::LD, 1, 4, OperandType::RegisterH, OperandType::RegisterE),
	OpCodeInfo(0x64, OpCode::LD, 1, 4, OperandType::RegisterH, OperandType::RegisterH),
	OpCodeInfo(0x65, OpCode::LD, 1, 4, OperandType::RegisterH, OperandType::RegisterL),
	OpCodeInfo(0x66, OpCode::LD, 1, 4, OperandType::RegisterH, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x67, OpCode::LD, 1, 4, OperandType::RegisterH, OperandType::Acculumator),
	OpCodeInfo(0x68, OpCode::LD, 1, 4, OperandType::RegisterL, OperandType::RegisterB),
	OpCodeInfo(0x69, OpCode::LD, 1, 4, OperandType::RegisterL, OperandType::RegisterC),
	OpCodeInfo(0x6A, OpCode::LD, 1, 4, OperandType::RegisterL, OperandType::RegisterD),
	OpCodeInfo(0x6B, OpCode::LD, 1, 4, OperandType::RegisterL, OperandType::RegisterE),
	OpCodeInfo(0x6C, OpCode::LD, 1, 4, OperandType::RegisterL, OperandType::RegisterH),
	OpCodeInfo(0x6D, OpCode::LD, 1, 4, OperandType::RegisterL, OperandType::RegisterL),
	OpCodeInfo(0x6E, OpCode::LD, 1, 4, OperandType::RegisterL, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x6F, OpCode::LD, 1, 4, OperandType::RegisterL, OperandType::Acculumator),

	// 0x70 - 0x7F
	OpCodeInfo(0x70, OpCode::LD, 1, 8, OperandType::RegisterHLIndirect, OperandType::RegisterB),
	OpCodeInfo(0x71, OpCode::LD, 1, 8, OperandType::RegisterHLIndirect, OperandType::RegisterC),
	OpCodeInfo(0x72, OpCode::LD, 1, 8, OperandType::RegisterHLIndirect, OperandType::RegisterD),
	OpCodeInfo(0x73, OpCode::LD, 1, 8, OperandType::RegisterHLIndirect, OperandType::RegisterE),
	OpCodeInfo(0x74, OpCode::LD, 1, 8, OperandType::RegisterHLIndirect, OperandType::RegisterH),
	OpCodeInfo(0x75, OpCode::LD, 1, 8, OperandType::RegisterHLIndirect, OperandType::RegisterL),
	OpCodeInfo(0x76, OpCode::HALT, 1, 4),
	OpCodeInfo(0x77, OpCode::LD, 1, 8, OperandType::RegisterHLIndirect, OperandType::Acculumator),
	OpCodeInfo(0x78, OpCode::LD, 1, 4, OperandType::Acculumator, OperandType::RegisterB),
	OpCodeInfo(0x79, OpCode::LD, 1, 4, OperandType::Acculumator, OperandType::RegisterC),
	OpCodeInfo(0x7A, OpCode::LD, 1, 4, OperandType::Acculumator, OperandType::RegisterD),
	OpCodeInfo(0x7B, OpCode::LD, 1, 4, OperandType::Acculumator, OperandType::RegisterE),
	OpCodeInfo(0x7C, OpCode::LD, 1, 4, OperandType::Acculumator, OperandType::RegisterH),
	OpCodeInfo(0x7D, OpCode::LD, 1, 4, OperandType::Acculumator, OperandType::RegisterL),
	OpCodeInfo(0x7E, OpCode::LD, 1, 4, OperandType::Acculumator, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x7F, OpCode::LD, 1, 4, OperandType::Acculumator, OperandType::Acculumator),

	// 0x80 - 0x8F
	OpCodeInfo(0x80, OpCode::ADD, 1, 4, OperandType::Acculumator, OperandType::RegisterB),
	OpCodeInfo(0x81, OpCode::ADD, 1, 4, OperandType::Acculumator, OperandType::RegisterC),
	OpCodeInfo(0x82, OpCode::ADD, 1, 4, OperandType::Acculumator, OperandType::RegisterD),
	OpCodeInfo(0x83, OpCode::ADD, 1, 4, OperandType::Acculumator, OperandType::RegisterE),
	OpCodeInfo(0x84, OpCode::ADD, 1, 4, OperandType::Acculumator, OperandType::RegisterH),
	OpCodeInfo(0x85, OpCode::ADD, 1, 4, OperandType::Acculumator, OperandType::RegisterL),
	OpCodeInfo(0x86, OpCode::ADD, 1, 4, OperandType::Acculumator, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x87, OpCode::ADD, 1, 4, OperandType::Acculumator, OperandType::Acculumator),
	OpCodeInfo(0x88, OpCode::ADC, 1, 4, OperandType::Acculumator, OperandType::RegisterB),
	OpCodeInfo(0x89, OpCode::ADC, 1, 4, OperandType::Acculumator, OperandType::RegisterC),
	OpCodeInfo(0x8A, OpCode::ADC, 1, 4, OperandType::Acculumator, OperandType::RegisterD),
	OpCodeInfo(0x8B, OpCode::ADC, 1, 4, OperandType::Acculumator, OperandType::RegisterE),
	OpCodeInfo(0x8C, OpCode::ADC, 1, 4, OperandType::Acculumator, OperandType::RegisterH),
	OpCodeInfo(0x8D, OpCode::ADC, 1, 4, OperandType::Acculumator, OperandType::RegisterL),
	OpCodeInfo(0x8E, OpCode::ADC, 1, 4, OperandType::Acculumator, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x8F, OpCode::ADC, 1, 4, OperandType::Acculumator, OperandType::Acculumator),

	// 0x90 - 0x9F
	OpCodeInfo(0x90, OpCode::SUB, 1, 4, OperandType::RegisterB),
	OpCodeInfo(0x91, OpCode::SUB, 1, 4, OperandType::RegisterC),
	OpCodeInfo(0x92, OpCode::SUB, 1, 4, OperandType::RegisterD),
	OpCodeInfo(0x93, OpCode::SUB, 1, 4, OperandType::RegisterE),
	OpCodeInfo(0x94, OpCode::SUB, 1, 4, OperandType::RegisterH),
	OpCodeInfo(0x95, OpCode::SUB, 1, 4, OperandType::RegisterL),
	OpCodeInfo(0x96, OpCode::SUB, 1, 4, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x97, OpCode::SUB, 1, 4, OperandType::Acculumator),
	OpCodeInfo(0x98, OpCode::SBC, 1, 4, OperandType::Acculumator, OperandType::RegisterB),
	OpCodeInfo(0x99, OpCode::SBC, 1, 4, OperandType::Acculumator, OperandType::RegisterC),
	OpCodeInfo(0x9A, OpCode::SBC, 1, 4, OperandType::Acculumator, OperandType::RegisterD),
	OpCodeInfo(0x9B, OpCode::SBC, 1, 4, OperandType::Acculumator, OperandType::RegisterE),
	OpCodeInfo(0x9C, OpCode::SBC, 1, 4, OperandType::Acculumator, OperandType::RegisterH),
	OpCodeInfo(0x9D, OpCode::SBC, 1, 4, OperandType::Acculumator, OperandType::RegisterL),
	OpCodeInfo(0x9E, OpCode::SBC, 1, 4, OperandType::Acculumator, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x9F, OpCode::SBC, 1, 4, OperandType::Acculumator, OperandType::Acculumator),

	// 0xA0 - 0xAF
	OpCodeInfo(0xA0, OpCode::AND, 1, 4, OperandType::RegisterB),
	OpCodeInfo(0xA1, OpCode::AND, 1, 4, OperandType::RegisterC),
	OpCodeInfo(0xA2, OpCode::AND, 1, 4, OperandType::RegisterD),
	OpCodeInfo(0xA3, OpCode::AND, 1, 4, OperandType::RegisterE),
	OpCodeInfo(0xA4, OpCode::AND, 1, 4, OperandType::RegisterH),
	OpCodeInfo(0xA5, OpCode::AND, 1, 4, OperandType::RegisterL),
	OpCodeInfo(0xA6, OpCode::AND, 1, 4, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xA7, OpCode::AND, 1, 4, OperandType::Acculumator),
	OpCodeInfo(0xA8, OpCode::XOR, 1, 4, OperandType::RegisterB),
	OpCodeInfo(0xA9, OpCode::XOR, 1, 4, OperandType::RegisterC),
	OpCodeInfo(0xAA, OpCode::XOR, 1, 4, OperandType::RegisterD),
	OpCodeInfo(0xAB, OpCode::XOR, 1, 4, OperandType::RegisterE),
	OpCodeInfo(0xAC, OpCode::XOR, 1, 4, OperandType::RegisterH),
	OpCodeInfo(0xAD, OpCode::XOR, 1, 4, OperandType::RegisterL),
	OpCodeInfo(0xAE, OpCode::XOR, 1, 4, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xAF, OpCode::XOR, 1, 4, OperandType::Acculumator, OperandType::Acculumator),

	// 0xB0 - 0xBF
	OpCodeInfo(0xB0, OpCode::OR, 1, 4, OperandType::RegisterB),
	OpCodeInfo(0xB1, OpCode::OR, 1, 4, OperandType::RegisterC),
	OpCodeInfo(0xB2, OpCode::OR, 1, 4, OperandType::RegisterD),
	OpCodeInfo(0xB3, OpCode::OR, 1, 4, OperandType::RegisterE),
	OpCodeInfo(0xB4, OpCode::OR, 1, 4, OperandType::RegisterH),
	OpCodeInfo(0xB5, OpCode::OR, 1, 4, OperandType::RegisterL),
	OpCodeInfo(0xB6, OpCode::OR, 1, 4, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xB7, OpCode::OR, 1, 4, OperandType::Acculumator),
	OpCodeInfo(0xB8, OpCode::CP, 1, 4, OperandType::RegisterB),
	OpCodeInfo(0xB9, OpCode::CP, 1, 4, OperandType::RegisterC),
	OpCodeInfo(0xBA, OpCode::CP, 1, 4, OperandType::RegisterD),
	OpCodeInfo(0xBB, OpCode::CP, 1, 4, OperandType::RegisterE),
	OpCodeInfo(0xBC, OpCode::CP, 1, 4, OperandType::RegisterH),
	OpCodeInfo(0xBD, OpCode::CP, 1, 4, OperandType::RegisterL),
	OpCodeInfo(0xBE, OpCode::CP, 1, 4, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xBF, OpCode::CP, 1, 4, OperandType::Acculumator, OperandType::Acculumator),

	// 0xC0 - 0xCF
	OpCodeInfo(0xC0, OpCode::RET, 1, 8, OperandType::FlagNotZero, OperandType::None, 20),
	OpCodeInfo(0xC1, OpCode::POP, 1, 12, OperandType::RegisterBC),
	OpCodeInfo(0xC2, OpCode::JP,  3, 12, OperandType::FlagNotZero, OperandType::DataUINT16, 16),
	OpCodeInfo(0xC3, OpCode::JP,  3, 4, OperandType::None, OperandType::DataUINT16),
	OpCodeInfo(0xC4, OpCode::CALL,3, 12, OperandType::FlagNotZero, OperandType::AddressUINT16, 24),
	OpCodeInfo(0xC5, OpCode::PUSH,1, 16, OperandType::RegisterBC),
	OpCodeInfo(0xC6, OpCode::ADD, 2, 8, OperandType::Acculumator, OperandType::DataUINT8),
	OpCodeInfo(0xC7, OpCode::RST, 1, 16),
	OpCodeInfo(0xC8, OpCode::RET, 1, 8, OperandType::FlagZero, OperandType::None, 20),
	OpCodeInfo(0xC9, OpCode::RET, 1, 16),
	OpCodeInfo(0xCA, OpCode::JP,  3, 12, OperandType::FlagZero, OperandType::DataUINT16, 16),
	OpCodeInfo(0xCB, OpCode::PREFIX, 1, 4),
	OpCodeInfo(0xCC, OpCode::CALL,3, 12, OperandType::FlagZero, OperandType::AddressUINT16, 24),
	OpCodeInfo(0xCD, OpCode::CALL,3, 24, OperandType::AddressUINT16),
	OpCodeInfo(0xCE, OpCode::ADC, 2, 8, OperandType::Acculumator, OperandType::DataUINT8),
	OpCodeInfo(0xCF, OpCode::RST, 1, 16),

	// 0xD0 - 0xDF
	OpCodeInfo(0xD0, OpCode::RET, 1, 8, OperandType::FlagNotCarry, OperandType::None, 20),
	OpCodeInfo(0xD1, OpCode::POP, 1, 12),
	OpCodeInfo(0xD2, OpCode::JP,  3, 12, OperandType::FlagNotCarry, OperandType::DataUINT16, 16),
	OpCodeInfo(0xD3, OpCode::XXX, 1, 4),
	OpCodeInfo(0xD4, OpCode::CALL,2, 12, OperandType::FlagNotCarry, OperandType::AddressUINT16, 24),
	OpCodeInfo(0xD5, OpCode::PUSH,1, 12, OperandType::RegisterDE),
	OpCodeInfo(0xD6, OpCode::SUB, 2, 8, OperandType::Acculumator, OperandType::DataUINT8),
	OpCodeInfo(0xD7, OpCode::RST, 1, 16),
	OpCodeInfo(0xD8, OpCode::RET, 1, 8, OperandType::FlagCarry, OperandType::None, 20),
	OpCodeInfo(0xD9, OpCode::RETI,1, 16),
	OpCodeInfo(0xDA, OpCode::JP,  3, 12, OperandType::FlagCarry, OperandType::DataUINT16, 16),
	OpCodeInfo(0xDB, OpCode::XXX, 1, 4),
	OpCodeInfo(0xDC, OpCode::CALL,3, 12, OperandType::FlagCarry, OperandType::AddressUINT16, 24),
	OpCodeInfo(0xDD, OpCode::XXX, 1, 4),
	OpCodeInfo(0xDE, OpCode::SBC, 2, 8, OperandType::Acculumator, OperandType::DataUINT8),
	OpCodeInfo(0xDF, OpCode::RST, 1, 16),

	// 0xE0 - 0xEF
	OpCodeInfo(0xE0, OpCode::LDH, 2, 12, OperandType::AddressUINT8, OperandType::Acculumator),
	OpCodeInfo(0xE1, OpCode::POP, 1, 12, OperandType::RegisterHL),
	OpCodeInfo(0xE2, OpCode::LD,  2, 8, OperandType::RegisterCIndirect, OperandType::Acculumator),
	OpCodeInfo(0xE3, OpCode::XXX, 1, 4),
	OpCodeInfo(0xE4, OpCode::XXX, 1, 4),
	OpCodeInfo(0xE5, OpCode::PUSH,1, 16, OperandType::RegisterHL),
	OpCodeInfo(0xE6, OpCode::AND, 2, 8, OperandType::Acculumator, OperandType::DataUINT8),
	OpCodeInfo(0xE7, OpCode::RST, 1, 16),
	OpCodeInfo(0xE8, OpCode::ADD, 2, 16, OperandType::Stackpointer, OperandType::DataINT8),
	OpCodeInfo(0xE9, OpCode::JP,  1, 4, OperandType::None, OperandType::RegisterHL),
	OpCodeInfo(0xEA, OpCode::LD,  3, 16, OperandType::AddressUINT16, OperandType::Acculumator),
	OpCodeInfo(0xEB, OpCode::XXX, 1, 4),
	OpCodeInfo(0xEC, OpCode::XXX, 1, 4),
	OpCodeInfo(0xED, OpCode::XXX, 1, 4),
	OpCodeInfo(0xEE, OpCode::XOR, 2, 8, OperandType::Acculumator, OperandType::DataUINT8),
	OpCodeInfo(0xEF, OpCode::RST, 1, 16),

	// 0xF0 - 0xFF
	OpCodeInfo(0xF0, OpCode::LDH, 2, 12, OperandType::Acculumator, OperandType::AddressUINT8),
	OpCodeInfo(0xF1, OpCode::POP, 1, 12, OperandType::RegisterAF),
	OpCodeInfo(0xF2, OpCode::LD,  2, 8, OperandType::Acculumator, OperandType::RegisterCIndirect),
	OpCodeInfo(0xF3, OpCode::DI,  1, 4),
	OpCodeInfo(0xF4, OpCode::XXX, 1, 4),
	OpCodeInfo(0xF5, OpCode::PUSH,1, 16, OperandType::RegisterAF),
	OpCodeInfo(0xF6, OpCode::OR,  2, 8, OperandType::Acculumator, OperandType::DataUINT8),
	OpCodeInfo(0xF7, OpCode::RST, 1, 16),
	OpCodeInfo(0xF8, OpCode::LD,  2, 12, OperandType::RegisterHL, OperandType::DataINT8),
	OpCodeInfo(0xF9, OpCode::LD,  1, 8, OperandType::Stackpointer, OperandType::RegisterHL),
	OpCodeInfo(0xFA, OpCode::LD,  3, 16, OperandType::Acculumator, OperandType::AddressUINT16),
	OpCodeInfo(0xFB, OpCode::EI,  1, 4),
	OpCodeInfo(0xFC, OpCode::XXX, 1, 4),
	OpCodeInfo(0xFD, OpCode::XXX, 1, 4),
	OpCodeInfo(0xFE, OpCode::CP,  2, 8, OperandType::Acculumator, OperandType::DataUINT8),
	OpCodeInfo(0xFF, OpCode::RST, 1, 16)
};



OpCodeInfo OpCodeInfo::OpCodesCB[256] =
{
	OpCodeInfo(0x00, OpCode::RLC, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x01, OpCode::RLC, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x02, OpCode::RLC, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x03, OpCode::RLC, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x04, OpCode::RLC, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x05, OpCode::RLC, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x06, OpCode::RLC, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x07, OpCode::RLC, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0x08, OpCode::RRC, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x09, OpCode::RRC, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x0A, OpCode::RRC, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x0B, OpCode::RRC, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x0C, OpCode::RRC, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x0D, OpCode::RRC, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x0E, OpCode::RRC, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x0F, OpCode::RRC, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0x10, OpCode::RL, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x11, OpCode::RL, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x12, OpCode::RL, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x13, OpCode::RL, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x14, OpCode::RL, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x15, OpCode::RL, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x16, OpCode::RL, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x17, OpCode::RL, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0x18, OpCode::RR, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x19, OpCode::RR, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x1A, OpCode::RR, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x1B, OpCode::RR, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x1C, OpCode::RR, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x1D, OpCode::RR, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x1E, OpCode::RR, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x1F, OpCode::RR, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0x20, OpCode::SLA, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x21, OpCode::SLA, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x22, OpCode::SLA, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x23, OpCode::SLA, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x24, OpCode::SLA, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x25, OpCode::SLA, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x26, OpCode::SLA, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x27, OpCode::SLA, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0x28, OpCode::SRA, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x29, OpCode::SRA, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x2A, OpCode::SRA, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x2B, OpCode::SRA, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x2C, OpCode::SRA, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x2D, OpCode::SRA, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x2E, OpCode::SRA, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x2F, OpCode::SRA, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0x30, OpCode::SWAP, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x31, OpCode::SWAP, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x32, OpCode::SWAP, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x33, OpCode::SWAP, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x34, OpCode::SWAP, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x35, OpCode::SWAP, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x36, OpCode::SWAP, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x37, OpCode::SWAP, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0x38, OpCode::SRL,  2, 8, OperandType::RegisterB),
	OpCodeInfo(0x39, OpCode::SRL,  2, 8, OperandType::RegisterC),
	OpCodeInfo(0x3A, OpCode::SRL,  2, 8, OperandType::RegisterD),
	OpCodeInfo(0x3B, OpCode::SRL,  2, 8, OperandType::RegisterE),
	OpCodeInfo(0x3C, OpCode::SRL,  2, 8, OperandType::RegisterH),
	OpCodeInfo(0x3D, OpCode::SRL,  2, 8, OperandType::RegisterL),
	OpCodeInfo(0x3E, OpCode::SRL,  2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x3F, OpCode::SRL,  2, 8, OperandType::Acculumator),

	OpCodeInfo(0x40, OpCode::BIT, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x41, OpCode::BIT, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x42, OpCode::BIT, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x43, OpCode::BIT, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x44, OpCode::BIT, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x45, OpCode::BIT, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x46, OpCode::BIT, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x47, OpCode::BIT, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0x48, OpCode::BIT, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x49, OpCode::BIT, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x4A, OpCode::BIT, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x4B, OpCode::BIT, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x4C, OpCode::BIT, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x4D, OpCode::BIT, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x4E, OpCode::BIT, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x4F, OpCode::BIT, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0x50, OpCode::BIT, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x51, OpCode::BIT, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x52, OpCode::BIT, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x53, OpCode::BIT, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x54, OpCode::BIT, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x55, OpCode::BIT, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x56, OpCode::BIT, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x57, OpCode::BIT, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0x58, OpCode::BIT, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x59, OpCode::BIT, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x5A, OpCode::BIT, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x5B, OpCode::BIT, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x5C, OpCode::BIT, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x5D, OpCode::BIT, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x5E, OpCode::BIT, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x5F, OpCode::BIT, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0x60, OpCode::BIT, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x61, OpCode::BIT, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x62, OpCode::BIT, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x63, OpCode::BIT, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x64, OpCode::BIT, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x65, OpCode::BIT, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x66, OpCode::BIT, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x67, OpCode::BIT, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0x68, OpCode::BIT, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x69, OpCode::BIT, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x6A, OpCode::BIT, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x6B, OpCode::BIT, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x6C, OpCode::BIT, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x6D, OpCode::BIT, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x6E, OpCode::BIT, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x6F, OpCode::BIT, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0x70, OpCode::BIT, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x71, OpCode::BIT, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x72, OpCode::BIT, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x73, OpCode::BIT, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x74, OpCode::BIT, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x75, OpCode::BIT, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x76, OpCode::BIT, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x77, OpCode::BIT, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0x78, OpCode::BIT, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x79, OpCode::BIT, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x7A, OpCode::BIT, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x7B, OpCode::BIT, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x7C, OpCode::BIT, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x7D, OpCode::BIT, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x7E, OpCode::BIT, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x7F, OpCode::BIT, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0x80, OpCode::RES, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x81, OpCode::RES, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x82, OpCode::RES, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x83, OpCode::RES, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x84, OpCode::RES, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x85, OpCode::RES, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x86, OpCode::RES, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x87, OpCode::RES, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0x88, OpCode::RES, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x89, OpCode::RES, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x8A, OpCode::RES, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x8B, OpCode::RES, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x8C, OpCode::RES, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x8D, OpCode::RES, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x8E, OpCode::RES, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x8F, OpCode::RES, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0x90, OpCode::RES, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x91, OpCode::RES, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x92, OpCode::RES, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x93, OpCode::RES, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x94, OpCode::RES, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x95, OpCode::RES, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x96, OpCode::RES, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x97, OpCode::RES, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0x98, OpCode::RES, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0x99, OpCode::RES, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0x9A, OpCode::RES, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0x9B, OpCode::RES, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0x9C, OpCode::RES, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0x9D, OpCode::RES, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0x9E, OpCode::RES, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0x9F, OpCode::RES, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0xA0, OpCode::RES, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0xA1, OpCode::RES, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0xA2, OpCode::RES, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0xA3, OpCode::RES, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0xA4, OpCode::RES, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0xA5, OpCode::RES, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0xA6, OpCode::RES, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xA7, OpCode::RES, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0xA8, OpCode::RES, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0xA9, OpCode::RES, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0xAA, OpCode::RES, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0xAB, OpCode::RES, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0xAC, OpCode::RES, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0xAD, OpCode::RES, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0xAE, OpCode::RES, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xAF, OpCode::RES, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0xB0, OpCode::RES, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0xB1, OpCode::RES, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0xB2, OpCode::RES, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0xB3, OpCode::RES, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0xB4, OpCode::RES, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0xB5, OpCode::RES, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0xB6, OpCode::RES, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xB7, OpCode::RES, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0xB8, OpCode::RES, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0xB9, OpCode::RES, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0xBA, OpCode::RES, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0xBB, OpCode::RES, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0xBC, OpCode::RES, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0xBD, OpCode::RES, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0xBE, OpCode::RES, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xBF, OpCode::RES, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0xC0, OpCode::SET, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0xC1, OpCode::SET, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0xC2, OpCode::SET, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0xC3, OpCode::SET, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0xC4, OpCode::SET, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0xC5, OpCode::SET, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0xC6, OpCode::SET, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xC7, OpCode::SET, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0xC8, OpCode::SET, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0xC9, OpCode::SET, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0xCA, OpCode::SET, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0xCB, OpCode::SET, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0xCC, OpCode::SET, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0xCD, OpCode::SET, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0xCE, OpCode::SET, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xCF, OpCode::SET, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0xD0, OpCode::SET, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0xD1, OpCode::SET, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0xD2, OpCode::SET, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0xD3, OpCode::SET, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0xD4, OpCode::SET, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0xD5, OpCode::SET, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0xD6, OpCode::SET, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xD7, OpCode::SET, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0xD8, OpCode::SET, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0xD9, OpCode::SET, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0xDA, OpCode::SET, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0xDB, OpCode::SET, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0xDC, OpCode::SET, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0xDD, OpCode::SET, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0xDE, OpCode::SET, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xDF, OpCode::SET, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0xE0, OpCode::SET, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0xE1, OpCode::SET, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0xE2, OpCode::SET, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0xE3, OpCode::SET, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0xE4, OpCode::SET, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0xE5, OpCode::SET, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0xE6, OpCode::SET, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xE7, OpCode::SET, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0xE8, OpCode::SET, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0xE9, OpCode::SET, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0xEA, OpCode::SET, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0xEB, OpCode::SET, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0xEC, OpCode::SET, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0xED, OpCode::SET, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0xEE, OpCode::SET, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xEF, OpCode::SET, 2, 8, OperandType::Acculumator),

	OpCodeInfo(0xF0, OpCode::SET, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0xF1, OpCode::SET, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0xF2, OpCode::SET, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0xF3, OpCode::SET, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0xF4, OpCode::SET, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0xF5, OpCode::SET, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0xF6, OpCode::SET, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xF7, OpCode::SET, 2, 8, OperandType::Acculumator),
	OpCodeInfo(0xF8, OpCode::SET, 2, 8, OperandType::RegisterB),
	OpCodeInfo(0xF9, OpCode::SET, 2, 8, OperandType::RegisterC),
	OpCodeInfo(0xFA, OpCode::SET, 2, 8, OperandType::RegisterD),
	OpCodeInfo(0xFB, OpCode::SET, 2, 8, OperandType::RegisterE),
	OpCodeInfo(0xFC, OpCode::SET, 2, 8, OperandType::RegisterH),
	OpCodeInfo(0xFD, OpCode::SET, 2, 8, OperandType::RegisterL),
	OpCodeInfo(0xFE, OpCode::SET, 2, 16, OperandType::RegisterHLIndirect),
	OpCodeInfo(0xFF, OpCode::SET, 2, 8, OperandType::Acculumator),

};
