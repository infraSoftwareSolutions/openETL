#ifndef METACORE___CGEN___MICROS_STRUCTURE_H
#define METACORE___CGEN___MICROS_STRUCTURE_H

    #define nl '\n'

    #define tab '\t'

    #define ___main___ \
        int main() {

    #define ___ret(retval) \
            return (int)retval; }

    #define jump(label) goto label

    #define jump_if(condition, label) \
        if (condition) goto label    

    #ifndef __cplusplus

        #define object typedef struct 

        #define cenum typedef enum

        #define cstr(name, sizeValue) \
            char name[sizeValue]

    #endif // __cplusplus

    #ifdef __cplusplus

        #include <string>
        #include <functional>
        #include <vector>
        #include <queue>

        using str = std::string;

        template<typename T>
        using func = std::function<T>;

        template<typename T>
        using vec = std::vector<T>;

        template<typename T>
        using que = std::queue<T>;

        #define lambda_func(capture_clause, parameters, return_type, script) \
            [capture_clause] parameters -> return_type { script }

    #endif // __cplusplus

#endif // METACORE___CGEN___MICROS_STRUCTURE_H