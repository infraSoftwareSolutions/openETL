#include "lite/type.hpp"
#include "cgen/micros.h"

TEST_MAIN(metalite: type);

    bool val = true;
    TEST_EQU(meta::lite::type(val), "bool");

    char val1 = '9';
    TEST_EQU(meta::lite::type(val1), "char");

    short val2 = 990;
    TEST_EQU(meta::lite::type(val2), "short");

    int val3 = 10;
    TEST_EQU(meta::lite::type(val3), "int");

    long val4 = 3993;
    TEST_EQU(meta::lite::type(val4), "long");

    float val5 = 99.9f;
    TEST_EQU(meta::lite::type(val5), "float");

    double val6 = 99.9;
    TEST_EQU(meta::lite::type(val6), "double");

    long double val7 = 9993.983;
    TEST_EQU(meta::lite::type(val7), "long double");

    TEST_EQU(meta::lite::is_bool(val), true);
    TEST_EQU(meta::lite::is_bool(val1), false);
    TEST_EQU(meta::lite::is_char(val1), true);
    TEST_EQU(meta::lite::is_char(val2), false);
    TEST_EQU(meta::lite::is_short(val2), true);
    TEST_EQU(meta::lite::is_short(val3), false);
    TEST_EQU(meta::lite::is_int(val3), true);
    TEST_EQU(meta::lite::is_int(val4), false);
    TEST_EQU(meta::lite::is_float(val5), true);
    TEST_EQU(meta::lite::is_float(val4), false);
    TEST_EQU(meta::lite::is_double(val6), true);
    TEST_EQU(meta::lite::is_double(val), false);
    TEST_EQU(meta::lite::is_numeric(val2), true);
    TEST_EQU(meta::lite::is_numeric(val), false);

    str val8 = "ken";
    TEST_EQU(meta::lite::type(val8), "std: string");
    TEST_EQU(meta::lite::is_string(val8), true);
    TEST_EQU(meta::lite::is_string(val3), false);

TEST_EXIT(true)