#include "VM.h"

void VM::Push(i32 v)
{
    stack[++sp] = v;
}

i32 VM::Pop()
{
    return stack[sp--];
}

i32 VM::NextInstruction()
{
    return code[ip++];
}

void VM::Run(i32* code)
{
    sp = 0;
    ip = 0;
    stack = (i32*)malloc(sizeof(i32) * STACK_SIZE);

    this->code = code;

    do
    {
        i32 op = NextInstruction();
        i32 a, b; // Registers
        i32 addr; // Store jump address

        switch (op)
        {
        case NOP:
            break;
        case PUSH:
            Push(NextInstruction());
            break;
        case POP:
            Pop();
            break;
        case IADD:
            b = Pop();
            a = Pop();
            Push(a + b);
            break;
        case ISUB:
            b = Pop();
            a = Pop();
            Push(a - b);
            break;
        case IMUL:
            b = Pop();
            a = Pop();
            Push(a * b);
            break;
        case IDIV:
            b = Pop();
            a = Pop();
            Push(a / b);
            break;
        case PRINT_LAST_I32:
            a = Pop();
            printf("%d\n", a);
            break;
        case PRINT_STR:
            {
                i32 character;
                while ((character = NextInstruction()) != (i32)'\0')
                {
                    printf("%c", (char)character);
                }
            }
            break;
        case PRINT_NEW_LINE:
            printf("\n");
            break;
        case HALT:
            return;
        case IS_EQUAL:
            b = Pop();
            a = Pop();

            Push((a == b) ? 1 : 0);
            break;
        case IS_NOT_EQUAL:
            b = Pop();
            a = Pop();

            Push((a != b) ? 1 : 0);
            break;
        case IS_GREATER:
            b = Pop();
            a = Pop();

            Push((a > b) ? 1 : 0);
            break;
        case IS_LESS:
            b = Pop();
            a = Pop();

            Push((a < b) ? 1 : 0);
            break;
        case JMP:
            addr = NextInstruction();
            ip = addr;
            break;
        case JMP_IF_TRUE:
            addr = NextInstruction();
            if (Pop())
            {
                ip = addr;
            }
            break;
        case JMP_IF_FALSE:
            addr = NextInstruction();
            if (!Pop())
            {
                ip = addr;
            }
            break;
        default:
            break;
        }
    }
    while (true);
}

VM::VM()
{
}

VM::~VM()
{
    free(stack);
}
