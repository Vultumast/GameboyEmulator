#pragma once

#include "Constants.hpp"

/// <summary>
/// Structure containing information for how long an OpCode takes, what function it invokes, and it's operands
/// </summary>
struct OpCodeInfo
{
private:
	uint8_t _originalHexCode = 0x00;
	OpCode _opCode = OpCode::NOP;
	uint8_t _byteLength = 1;
	uint8_t _cycleLengthMin = 1;
	uint8_t _cycleLengthMax = 1;
	OperandType _lhs = OperandType::None;
	OperandType _rhs = OperandType::None;
public:
	OpCodeInfo()
	{

	}

	OpCodeInfo(uint8_t hexCode, OpCode opCode, uint8_t byteLength, uint8_t cycleLengthMin, OperandType lhs = OperandType::None, OperandType rhs = OperandType::None, uint8_t cycleLengthMax = 0)
	{
		_originalHexCode = hexCode;
		_opCode = opCode;
		_byteLength = byteLength;
		_cycleLengthMin = cycleLengthMin;
		_cycleLengthMax = cycleLengthMax;
		if (cycleLengthMax == 0)
			_cycleLengthMax = _cycleLengthMin;
		_lhs = lhs;
		_rhs = rhs;
	}

	uint8_t GetHexCode() const { return _originalHexCode; }
	OpCode GetOpCode() const { return _opCode; }
	uint8_t GetByteLength() const { return _byteLength; }
	uint8_t GetCycleLengthMax() const { return _cycleLengthMin; }
	uint8_t GetCycleLengthMin() const { return _cycleLengthMax; }

	OperandType GetLeftHandOperand() const { return _lhs; }
	OperandType GetRightHandOperand() const { return _rhs; }

	bool LeftHandOperatorIsRegister() const { return _lhs >= OperandType::Acculumator && _lhs <= OperandType::RegisterHLIndirect; }
	bool RightHandOperatorIsRegister() const { return _rhs >= OperandType::Acculumator && _rhs <= OperandType::RegisterHLIndirect; }

	static OpCodeInfo OpCodes[256];
	static OpCodeInfo OpCodesCB[256];
};
