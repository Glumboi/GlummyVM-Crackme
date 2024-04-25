#pragma once
#include <unordered_map>

std::unordered_map<OPCODE, const char*> opcodeStrings{
	{OPCODE::HALT, "OPCODE_HALT"}
};

enum class OPCODE
{
	HALT
};
