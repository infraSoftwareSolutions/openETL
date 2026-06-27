#include "adva/function.hpp"
#include "lite.hpp"
bool utest_1()
{
    bool result = true;
    std::vector<int> v1 = {10, 9, 39, 23};
    std::vector<int> v2 = {23, 39, 9, 10};
    result &= meta::lite::test::vector<int>(meta::adva::reverse_v<int>(v1), v2);
    result &= meta::lite::test::basic<bool>(meta::adva::same_v(meta::adva::reverse_v<int>(v1), v2), true);
    v1.pop_back();
    result &= meta::lite::test::basic<size_t>(meta::adva::v_end(v1), 2);
    result &= meta::lite::test::basic<size_t>(meta::adva::v_end(v2), 3);
    result &= meta::lite::test::basic<bool>(meta::adva::same_v(v1, v2), false);
    v2.push_back(100);
    v2.push_back(88);
    v2.push_back(66);
    std::vector<int> v3 = {9, 10, 100};
    result &= meta::lite::test::vector<int>(meta::adva::sub_v(v2, 2, 4), v3);
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
    return meta::lite::test::vector_2d<int>(meta::adva::reverse_v(v1), v2);
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
    meta::lite::io::NewLines(5);
    bool bresult;
    float fresult;
    meta::lite::test_stream UTS;
    UTS << utest_1;
    UTS << utest_2;
    UTS << utest_3;
    UTS << utest_4;
    UTS << utest_5;
    UTS >> bresult;
    meta::lite::io::print<std::string>("All test result: ");
    meta::lite::io::println(meta::lite::test::test_message(bresult));
    meta::lite::benchmark_stream<false> UTB = 6;
    UTB << utest_1;
    UTB << utest_2;
    UTB << utest_3;
    UTB << utest_4;
    UTB << utest_5;
    UTB >> fresult;
    meta::lite::io::print<std::string>(
        "The average time for all unit test: " +
        std::to_string(fresult) + " us");
    return 0;
}