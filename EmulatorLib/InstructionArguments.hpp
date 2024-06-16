#pragma once

#include "Constants.hpp"



class Processor;
class MemoryBus;


class InstructionArguments
{
private:
	Processor* _processor = nullptr;
	MemoryBus* _memorybus = nullptr;
	OperandType _lhs = OperandType::None;
	OperandType _rhs = OperandType::None;

	uint16_t _lhsValue = 0;
	uint16_t _rhsValue = 0;

public:
	InstructionArguments(Processor& processor, MemoryBus& memorybus, OperandType lhs, OperandType rhs, uint16_t lhsValue, uint16_t rhsValue)
	{
		_processor = &processor;
		_memorybus = &memorybus;
		_lhs = lhs;
		_rhs = rhs;
	}

	Processor& Processor();
	MemoryBus& MemoryBus();

	OperandType GetLeftHandOperand() const
	{
		return _lhs;
	}
	OperandType GetRightHandOperand() const
	{
		return _rhs;
	}
};