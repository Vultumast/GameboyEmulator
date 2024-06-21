#pragma once

#include <cstdint>

#pragma region Addresses
/// <summary>
/// Address for start of non-swappable ROM bank (always bank0)
/// </summary>
constexpr std::uint16_t Addr_ROM_Start = 0x0000;
/// <summary>
/// Address for end of non-swappable ROM bank (always bank0)
/// </summary>
constexpr std::uint16_t Addr_ROM_End = 0x3FFF;


/// <summary>
/// Address for start of swappable ROM bank
/// </summary>
constexpr std::uint16_t Addr_ROMSwap_Start = 0x4000;
/// <summary>
/// Address for end of swappable ROM bank
/// </summary>
constexpr std::uint16_t Addr_ROMSwap_End = 0x7FFF;


constexpr std::uint16_t Addr_VRAM_Start = 0x8000;
constexpr std::uint16_t Addr_VRAM_End = 0x9FFF;

constexpr std::uint16_t Addr_SRAM_Start = 0xA000;
constexpr std::uint16_t Addr_SRAM_End = 0xBFFF;

constexpr std::uint16_t Addr_ERAM_Start = 0xE000;
constexpr std::uint16_t Addr_ERAM_End = 0xFE9F;
#pragma endregion


/// <summary>
/// Addresses used by the gameboy to share data/state with other internal chips
/// </summary>
enum HardwareRegister : uint16_t
{
	/// <summary>
	/// Joypad
	/// </summary>
	P1_JOYP = 0xFF00,

	/// <summary>
	/// Serial Transfer Data
	/// </summary>
	SB = 0xFF01,
	/// <summary>
	/// Serial Transfer Control
	/// </summary>
	SC = 0xFF02,

	/// <summary>
	/// Divider Register
	/// </summary>
	DIV = 0xFF04,

	/// <summary>
	/// Timer Counter
	/// </summary>
	TIMA  = 0xFF05,
	/// <summary>
	/// Timer Modulo
	/// </summary>
	TMA = 0xFF06,
	/// <summary>
	/// Timer Control
	/// </summary>
	TAC = 0xFF07,

	/// <summary>
	/// Interrupt Flag
	/// </summary>
	IF = 0xFF0F,

	/// <summary>
	/// Sound Channel 1 Sweep
	/// </summary>
	NR10 = 0xFF10,
	/// <summary>
	/// Sound Channel 1 Length Timer & Duty Cycle
	/// </summary>
	NR11,
	/// <summary>
	/// Sound channel 1 Volume & Envelope
	/// </summary>
	NR12,
	/// <summary>
	/// Sound Channel 1 Period Low
	/// </summary>
	NR13,
	/// <summary>
	/// Sound Channel 1 Period High & Control
	/// </summary>
	NR14,

	/// <summary>
	/// Sound Channel 2 Length Timer & Duty Cycle
	/// </summary>
	NR21 = 0xFF16,
	/// <summary>
	/// Sound Channel 2 Volume & Envelope
	/// </summary>
	NR22,
	/// <summary>
	/// Sound Channel 2 Period Low
	/// </summary>
	NR23,
	/// <summary>
	/// Sound Channel 2 Period High & Control
	/// </summary>
	NR24,

	/// <summary>
	/// Sound Channel 3 DAC Enable
	/// </summary>
	NR30,
	/// <summary>
	/// Sound Channel 3 Length Timer
	/// </summary>
	NR31,
	/// <summary>
	/// Sound Channel 3 Output Level
	/// </summary>
	NR32,
	/// <summary>
	/// Sound Channel 3 Period Low
	/// </summary>
	NR33,
	/// <summary>
	/// Sound Channel 3 Period High & Control
	/// </summary>
	NR34,

	/// <summary>
	/// Sound Channel 4 Length Timer
	/// </summary>
	NR41 = 0xFF20,
	/// <summary>
	/// Sound Channel 4 Volume & Envelope
	/// </summary>
	NR42,
	/// <summary>
	/// Sound Channel 4 Frequency & Randomness
	/// </summary>
	NR43,
	/// <summary>
	/// Sound Channel 4 Control
	/// </summary>
	NR44,

	/// <summary>
	/// Master Volume & VIN Panning
	/// </summary>
	NR50,
	/// <summary>
	/// Sound Panning
	/// </summary>
	NR51,
	/// <summary>
	/// Sound On/Off
	/// </summary>
	NR52,

	WAVE_RAM_START = 0xFF30,
	WAVE_RAM_END = 0xFF3F,

	/// <summary>
	/// LCD Control
	/// </summary>
	LCDC,
	/// <summary>
	/// LCD Status
	/// </summary>
	STAT,
	/// <summary>
	/// Viewport Y
	/// </summary>
	SCY,
	/// <summary>
	/// Viewport X
	/// </summary>
	SCX,
	/// <summary>
	/// LCD Y Coordinate 
	/// </summary>
	LY,
	/// <summary>
	/// LY Compare
	/// </summary>
	LYC,

	/// <summary>
	/// OAM DMA Source Addresses & Start
	/// </summary>
	DMA,

	/// <summary>
	/// BG Palette Data (DMG)
	/// </summary>
	BGP,
	/// <summary>
	/// OBJ Palette 0 Data (DMG)
	/// </summary>
	OBP0,
	/// <summary>
	/// OBJ Palette 1 Data (DMG)
	/// </summary>
	OBP1,
	/// <summary>
	/// Windows Y Position
	/// </summary>
	WY,
	/// <summary>
	/// Window X Position + 7
	/// </summary>
	WX,

	/// <summary>
	/// Prepare Speed Switch (CGB)
	/// </summary>
	KEY = 0xFF4D,
	/// <summary>
	/// VRAM Bank (CGB)
	/// </summary>
	VBK = 0xFF4F,
	/// <summary>
	/// VRAM DMA Source High (CGB)
	/// </summary>
	HDMA1 = 0xFF51,
	/// <summary>
	/// VRAM DMA Source Low (CGB)
	/// </summary>
	HDMA2,
	/// <summary>
	/// VRAM DMA Destination High (CGB)
	/// </summary>
	HDMA3,
	/// <summary>
	/// VRAM DMA Destination Low (CGB)
	/// </summary>
	HDMA4,
	/// <summary>
	/// VRAM DMA Length/Mode/Start (CGB)
	/// </summary>
	HDMA5,
	/// <summary>
	/// Infrared Communications Port (CGB)
	/// </summary>
	RP,

	/// <summary>
	/// Background Color Palette Specification / Background Color Palette Index (CGB)
	/// </summary>
	BCPS_BCPI = 0xFF68,

	/// <summary>
	/// Background Color Palette Data / Background Palette Data (CGB)
	/// </summary>
	BCPD_BGPD,

	/// <summary>
	/// OBJ Color Palette Specification / OBJ Palette Index (CGB)
	/// </summary>
	OCPS_OBPI,

	/// <summary>
	/// OBJ Priority Mode (CGB)
	/// </summary>
	OPRI,

	/// <summary>
	/// WRAM Bank (CGB)
	/// </summary>
	SVBK = 0xFF70,

	/// <summary>
	/// Audio Digital Outputs 1 & 2 (CGB)
	/// </summary>
	PCM12 = 0xFF76,
	/// <summary>
	/// Audio Digital Outputs 3 & 4 (CGB)
	/// </summary>
	PCM34,

	/// <summary>
	/// Interrupt Enable
	/// </summary>
	IE = 0xFFFF
};


constexpr std::uint32_t CyclesPerSecond = 4194304;

enum class OpCode
{
	// Misc Instructions
	NOP,
	STOP,
	HALT,
	PREFIX,
	DI,
	EI,

	// Jump
	JR,
	RET,
	JP,
	CALL,
	RST,
	RETI,

	// SHARED 8/16 bit load/move/store instuctions
	LD,

	// 8 Bit load/move/store Instructions 
	// LD_8,
	LDH,

	// 16 bit load/move/store Instructions
	// LD_16,
	POP,
	PUSH,

	// SHARED 8/16 bit arithmetic/logical Instructions 
	INC,
	DEC,
	ADD,

	// 8 Bit arithmetic/logical Instructions 
	// INC_8,
	// DEC,
	DAA,
	SCF,
	CPL,
	CCF,
	// ADD,
	ADC,
	SUB,
	SBC,
	AND,
	XOR,
	OR,
	CP,

	// 8 Bit rotations/shifts and bit Instructions
	RLCA,
	RRCA,
	RLA,
	RRA,
	RLC,
	RRC,
	RL,
	RR,
	SLA,
	SRA,
	SWAP,
	SRL,
	BIT,
	RES,
	SET,


	XXX
};

enum class Register : uint8_t
{
	A,
	B,
	C,
	D,
	E,
	H,
	L,

	AF,
	BC,
	DE,
	HL,
	SP,
	PC
};

/// <summary>
/// Type defining all possible "inputs" and "outputs" of an instruction
/// </summary>
enum class OperandType
{
	None,

	Acculumator,
	RegisterB,
	RegisterC,
	RegisterD,
	RegisterE,
	RegisterH,
	RegisterL,

	RegisterAF,
	RegisterBC,
	RegisterDE,
	RegisterHL,
	Stackpointer,
	ProgramCounter,

	IncrementHL,
	DecrementHL,

	RegisterCIndirect,

	RegisterBCIndirect,
	RegisterDEIndirect,
	RegisterHLIndirect,

	DataUINT8,
	DataUINT16,

	AddressUINT8,
	AddressUINT16,

	FlagCarry,
	FlagHalfCarry,
	FlagNegative,
	FlagZero,
	
	FlagNotCarry,
	FlagNotHalfCarry,
	FlagNotNegative,
	FlagNotZero,
};

/// <summary>
/// Type representing possible hardware interrupts
/// </summary>
enum Interrupt : uint8_t
{
	VBLANK = (1 << 0),
	LCD    = (1 << 1),
	TIMER  = (1 << 2),
	SERIAL = (1 << 3),
	JOYPAD = (1 << 4),
};

enum DMGColor : uint8_t
{
	WHITE,
	LIGHT_GREY,
	DARK_GREY,
	BLACK
};