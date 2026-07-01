#include "meta/lite/stream.hpp"
#include "meta/adva/function.hpp"

bool utest_1()
{
    return meta::lite::test::equal<std::string>(
        meta::adva::capitalize("string"),
        "String");
}

bool utest_2()
{
    return meta::lite::test::equal<size_t>(
        meta::adva::last_index("capitalize"),
        9);
}

bool utest_3()
{
    return meta::lite::test::equal<char>(
        meta::adva::last_element("capitalize"),
        'e');
}

bool utest_4()
{
    return meta::lite::test::equal<std::string>(
        meta::adva::remove("unit test", 4),
        "unittest");
}

bool utest_5()
{
    return meta::lite::test::equal<std::string>(
        meta::adva::remove("mind", 'i'),
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
    return meta::lite::test::equal<std::string>(
        meta::adva::remove("remove", filter_1),
        "reove");
}

bool utest_7()
{
    return meta::lite::test::equal<std::string>(
        meta::adva::sub_str("History", 2, 5),
        "stor");
}

bool utest_8()
{
    return meta::lite::test::equal<std::string>(
        meta::adva::remove("Sam Altman", "Altman"),
        "Sam ");
}

bool utest_9()
{
    return meta::lite::test::equal<std::string>(
        meta::adva::reverse("function"),
        "noitcnuf");
}

bool utest_10()
{
    return meta::lite::test::equal<std::string>(
        meta::adva::insert("reerse", 'v', 2),
        "reverse");
}

bool utest_11()
{
    return meta::lite::test::equal<std::string>(
        meta::adva::swap("today", 1, 3),
        "tadoy");
}

bool utest_12()
{
    return meta::lite::test::equal<std::string>(
        meta::adva::replace("Success", 's', '*'),
        "Succe**");
}

bool utest_13()
{
    return meta::lite::test::equal<std::string>(
        meta::adva::convert("EDcIlPuB", true),
        "edcilpub");
}

bool utest_14()
{
    return meta::lite::test::equal<std::string>(
        meta::adva::convert("EDcIlPuB", false),
        "EDCILPUB");
}

bool utest_15()
{
    return meta::lite::test::equal<std::string>(
        meta::adva::standard_word("eDcIlPuB"),
        "Edcilpub");
}

bool utest_16()
{
    return meta::lite::test::equal<std::string>(
        meta::adva::standard_form("uNiT teSt"),
        "Unit Test");
}

bool utest_17()
{
    std::string s = "Unit Test";
    int result = 0;
    for (char c : s)
        result += static_cast<int>(c);
    return meta::lite::test::equal<int>(
        meta::adva::sum_chars(s),
        result);
}

bool utest_18()
{
    std::string s = "Unit Test";
    long long result = 1;
    for (char c : s)
        result *= static_cast<long long>(c);
    return meta::lite::test::equal<long long>(
        meta::adva::mult_chars(s),
        result);
}

bool utest_19()
{
    std::vector<std::string> result_v = meta::adva::split("Unit Test");
    std::vector<std::string> exp_v = {"Unit", "Test"};
    return meta::lite::test::vector<std::string>(result_v, exp_v);
}

bool utest_20()
{
    int result = 0;
    for (char c = ' '; c <= '~'; c++)
        result += static_cast<int>(c);
    return meta::lite::test::equal<int>(meta::adva::ascii_sum(), result);
}

bool utest_21()
{
    bool result = true;
    std::vector<int> v1 = {10, 9, 39, 23};
    std::vector<int> v2 = {23, 39, 9, 10};
    result &= meta::lite::test::vector<int>(meta::adva::reverse<int>(v1), v2);
    result &= meta::lite::test::equal<bool>(meta::adva::isEqual(meta::adva::reverse_v<int>(v1), v2), true);
    v1.pop_back();
    result &= meta::lite::test::equal<size_t>(meta::adva::end(v1), 2);
    result &= meta::lite::test::equal<size_t>(meta::adva::end(v2), 3);
    result &= meta::lite::test::equal<bool>(meta::adva::isEqual(v1, v2), false);
    v2.push_back(100);
    v2.push_back(88);
    v2.push_back(66);
    std::vector<int> v3 = {9, 10, 100};
    result &= meta::lite::test::vector<int>(meta::adva::sub(v2, 2, 4), v3);
    return result;
}

bool utest_22()
{
    std::vector<std::vector<int>> v1 = {
        {10, 29, 38},
        {29, 38},
        {2, 39, 39},
        {1}};
    std::vector<std::vector<int>> v2 = {
        {1},
        {39, 39, 2},
        {38, 29},
        {38, 29, 10}};
    return meta::lite::test::vector_2d<int>(meta::adva::reverse(v1), v2);
}

bool utest_23()
{
    std::vector<std::vector<int>> v1 = {
        {77, 29, 39, 38, 29},
        {55, 32, 19, 20, 22},
        {33, 44, 90, 92, 35},
        {12, 11, 39, 38, 29}};
    std::vector<std::vector<int>> v2 = {
        {77, 29, 39, 38, 29},
        {55, 32, 19, 20, 22},
        {12, 11, 39, 38, 29}};
    return meta::lite::test::vector_2d<int>(meta::adva::erase_row<int>(v1, 2), v2);
}

bool utest_24()
{
    std::vector<std::vector<int>> v1 = {
        {77, 29, 39, 38, 29},
        {55, 32, 19, 20, 22},
        {33, 44, 90, 92, 35},
        {12, 11, 39, 38, 29}};
    std::vector<std::vector<int>> v2 = {
        {77, 29, 38, 29},
        {55, 32, 20, 22},
        {33, 44, 92, 35},
        {12, 11, 38, 29}};
    return meta::lite::test::vector_2d<int>(meta::adva::erase_column<int>(v1, 2), v2);
}

bool utest_25()
{
    std::vector<std::vector<int>> v1 = {
        {77, 29, 39, 38, 29},
        {55, 32, 19, 20, 22},
        {33, 44, 90, 92, 35},
        {12, 11, 39, 38, 29}};
    std::vector<std::vector<int>> v2 = {
        {77, 29, 38, 29},
        {55, 32, 20, 22},
        {12, 11, 38, 29}};
    return meta::lite::test::vector_2d<int>(meta::adva::erase_row_column<int>(v1, 2, 2), v2);
}

int main()
{
    meta::lite::test_stream UTS;
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
    UTS << utest_21;
    UTS << utest_22;
    UTS << utest_23;
    UTS << utest_24;
    UTS << utest_25;
    UTS.print_summary();
    meta::lite::benchmark_stream<false> UTB = 6;
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
    UTB << utest_21;
    UTB << utest_22;
    UTB << utest_23;
    UTB << utest_24;
    UTB << utest_25;
    UTB.print_summary();
    return 0;
}