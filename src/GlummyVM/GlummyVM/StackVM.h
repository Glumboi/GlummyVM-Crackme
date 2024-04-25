#pragma once

#include <iostream>
#include <vector>

//Type defs
typedef int32_t i32;

class StackVM
{
	i32 pc = 100; //Program counter
	i32 sp = 0; //Stack pointer
	std::vector<i32> memory;
	i32 typ = 0;
	i32 dat = 0;
	i32 running = 1;

	i32 getType(i32 instruction);
	i32 getData(i32 instruction);
	void fetch();
	void decode();
	void execute();
	void doPrimitive();

public:
	StackVM();
	void run();
	void loadProgram(std::vector<i32> prog);
};
