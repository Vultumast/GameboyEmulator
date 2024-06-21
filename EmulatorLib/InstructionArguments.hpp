#pragma once

#include "Constants.hpp"
#include "OpCodeInfo.hpp"


class Processor;
class MemoryBus;

class InstructionArguments
{
private:
	Processor* _processor = nullptr;
	MemoryBus* _memoryBus = nullptr;
	OpCodeInfo* _opcodeInfo = nullptr;

	OperandType _lhs = OperandType::None;
	OperandType _rhs = OperandType::None;

	uint16_t _lhsValue = 0;
	uint16_t _rhsValue = 0;

public:
	InstructionArguments(Processor& processor, MemoryBus& memoryBus, OpCodeInfo& opcodeInfo, OperandType lhs, OperandType rhs, uint16_t lhsValue, uint16_t rhsValue)
	{
		_processor = &processor;
		_memoryBus = &memoryBus;
		_opcodeInfo = &opcodeInfo;

		_lhs = lhs;
		_rhs = rhs;

		_lhsValue = lhsValue;
		_rhsValue = rhsValue;
	}


	/// <summary>
	/// The active CPU
	/// </summary>
	/// <returns></returns>
	Processor& Processor()
	{
		return *_processor;
	}

	/// <summary>
	/// The active MMU
	/// </summary>
	/// <returns></returns>
	MemoryBus& MemoryBus()
	{
		return *_memoryBus;
	}

	const OpCodeInfo& OpCodeInfo() const
	{
		return *_opcodeInfo;
	}

	OperandType GetLeftHandOperand() const
	{
		return _lhs;
	}
	OperandType GetRightHandOperand() const
	{
		return _rhs;
	}

	uint16_t GetLeftHandValue() const
	{
		return _lhsValue;
	}
	uint16_t GetRightHandValue() const
	{
		return _rhsValue;
	}

	friend class Processor;
};