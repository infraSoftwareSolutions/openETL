#ifndef METACORE___CGEN___MICROS_TEST_H
#define METACORE___CGEN___MICROS_TEST_H

    #define TEST_INIT(name)        \
        double tests_passed = 0.0; \
        double tests_failed = 0.0; \
        double total_tests = 0.0;  \
        char testName[] = #name

    #define TEST_SUMMARY                               \
        printf("\n-------------------------------");   \
        printf("\n<<<<<<<<< test summary >>>>>>>>");   \
        printf("\n-------------------------------");   \
        printf("\nTEST NAME: %s", testName);           \
        printf("\npassed tests: %i", tests_passed);    \
        printf("\nfailed tests: %i", tests_failed);    \
        printf("\ntotal tests: %i", total_tests);      \
        if (total_tests > 0)                           \
        {                                              \
            printf(                                    \
                "\npassed tests ratio: %f",            \
                (double)                               \
                (100 * (tests_passed / total_tests))); \
            printf(                                    \
                "\nfailed tests ratio: %f",            \
                (double)                               \
                (100 * (tests_failed / total_tests))); \
        }                                              \
        else                                           \
        {                                              \
            printf("\npassed tests ratio: 0.0");       \
            printf("\nfailed tests ratio: 0.0");       \
        }                                              \
        printf("\n-------------------------------\n")

    #define TEST_MAIN(name)         \
        int main()                   \
        {                            \
            size_t tests_passed = 0; \
            size_t tests_failed = 0; \
            size_t total_tests = 0;  \
            char testName[] = #name

    #define TEST_EXIT(PS)            \
            if (PS) TEST_SUMMARY;     \
            return (int)tests_failed; \
        }

    #define TEST_ASSERT(cond)                   \
        if (cond) { tests_passed++; }            \
        else                                     \
        {                                        \
            tests_failed++;                      \
            printf("FAIL:\n");                   \
            printf("\tNUMBER: %d", total_tests); \
            printf("\tLINE: %d", __LINE__);      \
            printf("\tFILE: %s", __FILE__);      \
        }                                        \
        total_tests++

    #define TEST_MSG(cond, msg)                 \
        if (cond) { tests_passed++; }            \
        else                                     \
        {                                        \
            tests_failed++;                      \
            printf("FAIL: %s\n", msg);           \
            printf("\tNUMBER: %d", total_tests); \
            printf("\tLINE: %d", __LINE__);      \
            printf("\tFILE: %s", __FILE__);      \
        }                                        \
        total_tests++

    #define TEST_EQU(real, expected)             \
        if (real == expected) { tests_passed++; } \
        else                                      \
        {                                         \
            tests_failed++;                       \
            printf("FAIL:\n");                    \
            printf("\tNUMBER: %d", total_tests);  \
            printf("\tLINE: %d", __LINE__);       \
            printf("\tFILE: %s", __FILE__);       \
        }                                         \
        total_tests++

    #define TEST_EQU_MSG(real, expected, msg)    \
        if (real == expected) { tests_passed++; } \
        else                                      \
        {                                         \
            tests_failed++;                       \
            printf("FAIL: %s\n", msg);            \
            printf("\tNUMBER: %d", total_tests);  \
            printf("\tLINE: %d", __LINE__);       \
            printf("\tFILE: %s", __FILE__);       \
        }                                         \
        total_tests++

#endif // METACORE___CGEN___MICROS_TEST_H