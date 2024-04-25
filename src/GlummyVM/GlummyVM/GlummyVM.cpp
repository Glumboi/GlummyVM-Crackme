#include <iostream>
#include <vector>
#include "VM.h"

void InsertStringToCode(const char* str, uint32_t indexToInsert, std::vector<i32>& code)
{
    auto iter = code.begin() + indexToInsert;

    for (size_t i = 0; i < strlen(str); i++)
    {
        code.insert(iter, str[i]);
        iter = code.begin() + ++indexToInsert;
    }

    code.insert(iter, '\0');
}

i32 GenKey(const char* userName)
{
    i32 result = 0;
    for (i32 i = 0; i < strlen(userName); i++)
    {
        i32 c = (userName[i] << 2) + userName[i]; // Multiply by 4 and then add the original value
        result += c;
    }
    return result;
}

int main()
{
    VM vm;
    std::string userName;
    i32 realKey;
    i32 inKey;

    std::vector<i32> code = {
        VM::OPCODE::PRINT_STR,
        //Insert string below
        VM::OPCODE::HALT
    };
    InsertStringToCode("Please your username: ", 1, code);
    vm.Run(code.data());
    std::cin >> userName;

    realKey = GenKey(userName.c_str());
    
    code = {
        VM::OPCODE::PRINT_STR,
        //Insert string below
        VM::OPCODE::HALT
    };
    InsertStringToCode("Please your user key: ", 1, code);
    vm.Run(code.data());

    std::cin >> inKey;

    code =
    {
        VM::OPCODE::PUSH, //0
        inKey, //1
        VM::OPCODE::PUSH, //2
        realKey, //3 -> User key
        VM::OPCODE::IS_EQUAL, //4
        VM::OPCODE::JMP_IF_TRUE, //5
        24, //6 -> Jump to the 24th instruction, keep in mind that we add new instructions below in form of strings
        VM::OPCODE::PRINT_STR, // 7
        //Insert string below
        VM::OPCODE::PRINT_NEW_LINE, // Extra newline
        VM::OPCODE::HALT,
        VM::OPCODE::PRINT_STR,
        //Insert string below
        VM::OPCODE::PRINT_NEW_LINE, // Extra newline
        VM::OPCODE::HALT,
    };
    
    // Load string into code, each character is one instruction that'll be added to the code, including the new line
    InsertStringToCode("Key invalid!\n", 8, code);
    InsertStringToCode("Key valid!\n", 25, code);

    vm.Run(code.data()); // Run code
    system("pause");
}
