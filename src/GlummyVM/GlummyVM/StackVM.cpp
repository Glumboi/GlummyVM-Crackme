#include "StackVM.h"

StackVM::StackVM()
{
	memory.reserve(1000000);
}

i32 StackVM::getType(i32 instruction)
{
	i32 type = 0xc0000000;
	type = (type & instruction) >> 30;
}