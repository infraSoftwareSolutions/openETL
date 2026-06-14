
#ifndef METACORE___CGEN___MICROS_STRUCTURE_H
#define METACORE___CGEN___MICROS_STRUCTURE_H

    #define nl '\n'
    
    #define tab '\t'

    #define meta_main   \
        int main() {

    #define ASSERT(cond)                \
        if (!(cond))                    \
        {                               \
            retval = 1;                 \
            printf("FAILED: %s", cond); \
        }

    #define ret(retval)         \
            return (int)retval; }

    #define cobject typedef struct 

    #define cenum typedef enum

    #define jump(label) goto label

    #define jump_if(condition, label) \
        if (condition) goto label

    #ifdef __cplusplus

        #include <string>
        #include <functional>
        #include <vector>
        #include <queue>

        #define object class

        #define func std::function
        
        #define vec std::vector

        #define str std::string

        #define que std::queue

        #define lambda_func(capture_clause, parameters, return_type, script) \
            [capture_clause] parameters -> return_type { script }

    #endif // __cplusplus

#endif // METACORE___CGEN___MICROS_STRUCTURE_H