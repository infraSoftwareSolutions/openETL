#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <exception>
#include <cctype>
#include "meta/adva/function.hpp"
#include "meta/cgen/micros/structure.h"
#include "meta/adva/token.hpp"
#include "meta/lite/file.hpp"

namespace ILI
{
    enum operant
    {
        unknown,
        var,
        boolean,
        number,
        string,
        array,
        filePath
    };

    struct instruction
    {
        meta::adva::token opCode;
        meta::adva::token op1;
        meta::adva::token op2;
    };

    class analysis {
        private:
        
        public:
    };

    size_t line = 1;
    hash_map<str, bool> conditions;
    hash_map<str, double> numbers;
    hash_map<str, str> strings;
    hash_map<str, vec<double>> arrays;
    meta::adva::hash_enum iop = {
        "NONE",
        "LD", 
        "LDN", 
        "LDI", 
        "LDNOT",
        "AND", 
        "A", 
        "ANDN", 
        "ANI",
        "ANDNOT", 
        "AN", 
        "OR", 
        "O",
        "ORN", 
        "ORI", 
        "ORNOT", 
        "ON",
        "ST", 
        "OUT", 
        "=", 
        "MOV", 
        "INC", 
        "DEC", 
        "SUB", 
        "ADD", 
        "MUL", 
        "DIV",
        "SAVE"
    };

    bool is_instruction(const str &ins)
    {
        for (auto s : iop)
        {
            if (meta::adva::exist(ins, s.first))
                return true;
        }
        return false;
    }

    bool is_var(const str oper) noexcept
    {
        if (numbers.contains(oper))
            return true;
        if (arrays.contains(oper))
            return true;
        if (strings.contains(oper))
            return true;
        if (conditions.contains(oper))
            return true;
        return false;
    }

    operant varType(const str oper)
    {
        if (numbers.contains(oper))
            return operant::number;
        if (arrays.contains(oper))
            return operant::array;
        if (strings.contains(oper))
            return operant::string;
        if (conditions.contains(oper))
            return operant::boolean;
        return operant::unknown;
    }

    str preformater(const str &value) noexcept
    {
        bool between = false, mid_con = false;
        str result;
        for (size_t i = 0; i < value.length(); i++)
        {
            if (between)
            {
                if (value[i] == ' ')
                {
                    if (!mid_con)
                    {
                        result += ',';
                        mid_con = true;
                    }
                    else
                        mid_con = false;
                }
                else
                    result += value[i];
            }
            else if (value[i] != ' ')
            {
                between = true;
                result += value[i];
            }
        }
    }



    instruction organizer() {}

    void executor(const std::stack<str> &ops)
    {
        std::stack<str> temp = ops;
        if (temp.top() == "mov")
        {
            temp.pop();
            if (is_var(temp.top()))
            {
                ILI::numbers[temp.top()];
            }
        }
    }
}

metaMain

    str command;
    while (true)
    {
        command.clear();
        std::cout << "IL >> ";
        std::cin >> command;
        command = meta::adva::to_lower(command);

        if (meta::adva::exist(command, "ld")) {}
        else if (meta::adva::exist(command, "or")) {}
        else if (meta::adva::exist(command, "and")) {}

        if (command == "exit") { break; }
        else
        {
            std::cout << "Unknown instruction" << nl;
            return 1;
        }
    }

meta_ret(true)