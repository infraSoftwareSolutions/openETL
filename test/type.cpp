#include "etl/type.hpp"
#include "cformat.h"

TEST_MAIN(etl_type);

    bool val = true;
    CTEST_EQU(etl::type(val), "bool");

    char val1 = '9';
    CTEST_EQU(etl::type(val1), "char");

    short val2 = 990;
    CTEST_EQU(etl::type(val2), "short");

    int val3 = 10;
    CTEST_EQU(etl::type(val3), "int");

    long val4 = 3993;
    CTEST_EQU(etl::type(val4), "long");

    float val5 = 99.9f;
    CTEST_EQU(etl::type(val5), "float");

    double val6 = 99.9;
    CTEST_EQU(etl::type(val6), "double");

    long double val7 = 9993.983;
    CTEST_EQU(etl::type(val7), "long double");

    CTEST_EQU(etl::is_bool(val), true);
    CTEST_EQU(etl::is_bool(val1), false);
    CTEST_EQU(etl::is_char(val1), true);
    CTEST_EQU(etl::is_char(val2), false);
    CTEST_EQU(etl::is_short(val2), true);
    CTEST_EQU(etl::is_short(val3), false);
    CTEST_EQU(etl::is_int(val3), true);
    CTEST_EQU(etl::is_int(val4), false);
    CTEST_EQU(etl::is_float(val5), true);
    CTEST_EQU(etl::is_float(val4), false);
    CTEST_EQU(etl::is_double(val6), true);
    CTEST_EQU(etl::is_double(val), false);
    CTEST_EQU(etl::is_numeric(val2), true);
    CTEST_EQU(etl::is_numeric(val), false);

    str val8 = "ken";
    CTEST_EQU(etl::type(val8), "std: string");
    CTEST_EQU(etl::is_string(val8), true);
    CTEST_EQU(etl::is_string(val3), false);

TEST_EXIT(true)