#pragma once
#include <malloc.h>
#include <cstdint>
#include <iostream>

#define STACK_SIZE 100
#define UNDEFINED_OPCODE "UNDEFINED_OPCODE"

#define RANDOM_OPCODE \
    NOP = __LINE__ ^ __COUNTER__, \
    HALT = __LINE__ ^ __COUNTER__, \
    PUSH = __LINE__ ^ __COUNTER__, \
    POP = __LINE__ ^ __COUNTER__, \
    IADD = __LINE__ ^ __COUNTER__, \
    ISUB = __LINE__ ^ __COUNTER__, \
    IMUL = __LINE__ ^ __COUNTER__, \
    IDIV = __LINE__ ^ __COUNTER__, \
    PRINT_LAST_I32 = __LINE__ ^ __COUNTER__, \
    PRINT_STR = __LINE__ ^ __COUNTER__, \
    PRINT_NEW_LINE = __LINE__ ^ __COUNTER__,\
	IS_EQUAL = __LINE__ ^ __COUNTER__,\
	IS_NOT_EQUAL = __LINE__ ^ __COUNTER__,\
	IS_GREATER = __LINE__ ^ __COUNTER__,\
	IS_LESS = __LINE__ ^ __COUNTER__,\
	JMP  = __LINE__ ^ __COUNTER__,\
	JMP_IF_TRUE  = __LINE__ ^ __COUNTER__,\
	JMP_IF_FALSE  = __LINE__ ^ __COUNTER__,
#define STRING_LITERAL(str) {str}

typedef int32_t i32;
typedef uint32_t u32;

class VM
{
public:
    enum OPCODE
    {
        RANDOM_OPCODE
    };

private:
    i32* stack;
    i32* code;
    i32 sp;
    i32 ip;

    void Push(i32 v);
    i32 Pop();
    i32 NextInstruction();

public:
    VM();
    void Run(i32* code);
    ~VM();
};
