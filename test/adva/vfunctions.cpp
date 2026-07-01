#include "meta/adva/function.hpp"
#include "meta/lite.hpp"

bool utest_1()
{
    bool result = true;
    std::vector<int> v1 = {10, 9, 39, 23};
    std::vector<int> v2 = {23, 39, 9, 10};
    result &= meta::lite::test::vector<int>(meta::adva::reverse<int>(v1), v2);
    result &= meta::lite::test::equal<bool>(meta::adva::isEqual(meta::adva::reverse<int>(v1), v2), true);
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

bool utest_2()
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

bool utest_3()
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
bool utest_4()
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
bool utest_5()
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
    UTS << utest_1;
    UTS << utest_2;
    UTS << utest_3;
    UTS << utest_4;
    UTS << utest_5;
    UTS.print_summary();
    meta::lite::benchmark_stream<false> UTB = 6;
    UTB << utest_1;
    UTB << utest_2;
    UTB << utest_3;
    UTB << utest_4;
    UTB << utest_5;
    UTB.print_summary();
    return 0;
}