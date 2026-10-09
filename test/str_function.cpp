#include "etl/stream.hpp"
#include "etl/function.hpp"

bool utest_1()
{
    return etl::test::equal<std::string>(
        etl::capitalize("string"),
        "String");
}

bool utest_2()
{
    return etl::test::equal<size_t>(
        etl::last_index("capitalize"),
        9);
}

bool utest_3()
{
    return etl::test::equal<char>(
        etl::last_element("capitalize"),
        'e');
}

bool utest_4()
{
    return etl::test::equal<std::string>(
        etl::remove("unit test", 4),
        "unittest");
}

bool utest_5()
{
    return etl::test::equal<std::string>(
        etl::remove("mind", 'i'),
        "mnd");
}

bool filter_1(char c)
{
    if (c == 'm')
        return true;
    return false;
}

bool utest_6()
{
    return etl::test::equal<std::string>(
        etl::remove("remove", filter_1),
        "reove");
}

bool utest_7()
{
    return etl::test::equal<std::string>(
        etl::sub_str("History", 2, 5),
        "stor");
}

bool utest_8()
{
    return etl::test::equal<std::string>(
        etl::remove("Sam Altman", "Altman"),
        "Sam ");
}

bool utest_9()
{
    return etl::test::equal<std::string>(
        etl::reverse("function"),
        "noitcnuf");
}

bool utest_10()
{
    return etl::test::equal<std::string>(
        etl::insert("reerse", 'v', 2),
        "reverse");
}

bool utest_11()
{
    return etl::test::equal<std::string>(
        etl::swap("today", 1, 3),
        "tadoy");
}

bool utest_12()
{
    return etl::test::equal<std::string>(
        etl::replace("Success", 's', '*'),
        "Succe**");
}

bool utest_13()
{
    return etl::test::equal<std::string>(
        etl::convert("EDcIlPuB", true),
        "edcilpub");
}

bool utest_14()
{
    return etl::test::equal<std::string>(
        etl::convert("EDcIlPuB", false),
        "EDCILPUB");
}

bool utest_15()
{
    return etl::test::equal<std::string>(
        etl::standard_word("eDcIlPuB"),
        "Edcilpub");
}

bool utest_16()
{
    return etl::test::equal<std::string>(
        etl::standard_form("uNiT teSt"),
        "Unit Test");
}

bool utest_17()
{
    std::string s = "Unit Test";
    int result = 0;
    for (char c : s)
        result += static_cast<int>(c);
    return etl::test::equal<int>(
        etl::sum_chars(s),
        result);
}

bool utest_18()
{
    std::string s = "Unit Test";
    long long result = 1;
    for (char c : s)
        result *= static_cast<long long>(c);
    return etl::test::equal<long long>(
        etl::mult_chars(s),
        result);
}

bool utest_19()
{
    std::vector<std::string> result_v = etl::split("Unit Test");
    std::vector<std::string> exp_v = {"Unit", "Test"};
    return etl::test::vector<std::string>(result_v, exp_v);
}

bool utest_20()
{
    int result = 0;
    for (char c = ' '; c <= '~'; c++)
        result += static_cast<int>(c);
    return etl::test::equal<int>(etl::ascii_sum(), result);
}

int main()
{
    etl::test_stream UTS;
    // UTS: unit test stream
    UTS << utest_1;
    UTS << utest_2;
    UTS << utest_3;
    UTS << utest_4;
    UTS << utest_5;
    UTS << utest_6;
    UTS << utest_7;
    UTS << utest_8;
    UTS << utest_9;
    UTS << utest_10;
    UTS << utest_11;
    UTS << utest_12;
    UTS << utest_13;
    UTS << utest_14;
    UTS << utest_15;
    UTS << utest_16;
    UTS << utest_17;
    UTS << utest_18;
    UTS << utest_19;
    UTS << utest_20;
    UTS.print_summary();
    etl::benchmark_stream<false> UTB = 6;
    UTB << utest_1;
    UTB << utest_2;
    UTB << utest_3;
    UTB << utest_4;
    UTB << utest_5;
    UTB << utest_6;
    UTB << utest_7;
    UTB << utest_8;
    UTB << utest_9;
    UTB << utest_10;
    UTB << utest_11;
    UTB << utest_12;
    UTB << utest_13;
    UTB << utest_14;
    UTB << utest_15;
    UTB << utest_16;
    UTB << utest_17;
    UTB << utest_18;
    UTB << utest_19;
    UTB << utest_20;
    UTB.print_summary();
    return 0;
}