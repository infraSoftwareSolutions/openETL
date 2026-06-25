#ifndef METACORE___CGEN___MICROS_STRUCTURE_H
#define METACORE___CGEN___MICROS_STRUCTURE_H

    #define nl '\n'

    #define tab '\t'

    #define metaMain \
        int main(int argc, char* argv[]) {

    #define meta_main \
        int main() {

    #define meta_ret(retval) \
            return (int)retval; }

    #define jump(label) goto label

    #define jump_if(condition, label) \
        if (condition) goto label

    // note used only with jump_if
    #define jump_elif(condition, label) \
        else if(condition) goto label
    
    // note used only with jump_if
    #define jump_else(label) \
        else goto label

    #ifndef __cplusplus

        #define object typedef struct 

        #define cenum typedef enum

        #define cstring(name, sizeValue) \
            char name[sizeValue]

    #endif // __cplusplus

    #ifdef __cplusplus

        #define lambda_func(capture_clause, parameters, return_type, script) \
            [capture_clause] parameters -> return_type { script }
        
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

    #endif // __cplusplus

#endif // METACORE___CGEN___MICROS_STRUCTURE_H