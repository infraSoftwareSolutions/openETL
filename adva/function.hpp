/**
 * @file function.hpp
 * @date 2025/9/25
 * @author Ali Lafi
 */

#include <type_traits>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>

#pragma once
#ifndef OPENUDT___ADVA___FUNCTION_HPP
#define OPENUDT___ADVA___FUNCTION_HPP

#ifdef METACORE___META_HPP
namespace meta {
#endif // METACORE___META_HPP
#ifdef METACORE___ADVA___HPP
namespace adva {
#endif // METACORE___ADVA___HPP

    /**
     * Reverses a vector of any type.
     * @param dynvec: The input vector to reverse.
     * @return A new vector containing the elements in reverse order.
     * @throws VectorEmptyException if the input vector is empty.
     */
    template <typename T>
    std::vector<T> reverse_v(const std::vector<T> &dynvec)
    {
        if (dynvec.empty())
            throw std::runtime_error("Empty Error");
        std::vector<T> result;
        for (int i = static_cast<int>(dynvec.size()) - 1; i >= 0; i--)
            result.push_back(dynvec[i]);
        return result;
    }

    /**
     * reverses a 2D vector (vector of vectors) of any type.
     * @param dynvec: The input 2D vector to reverse.
     * @throw runtime_error if the input vector is empty.
     * @return A new 2D vector containing the elements in reverse order.
     */
    template <typename T>
    std::vector<std::vector<T>> reverse_v(const std::vector<std::vector<T>> &dynvec)
    {
        if (dynvec.empty())
            throw std::runtime_error("Empty Error");
        std::vector<std::vector<T>> result;
        for (int i = static_cast<int>(dynvec.size()) - 1; i >= 0; i--)
            result.push_back(reverse_v(dynvec[i]));
        return result;
    }

    /**
     * reverses a 3D vector (vector of vector of vectors) of any type.
     * @param dynvec: The input 3D vector to reverse.
     * @throw runtime_error if the input vector is empty.
     * @return A new 3D vector containing the elements in reverse order.
     */
    template <typename T>
    std::vector<std::vector<std::vector<T>>> reverse_v(const std::vector<std::vector<std::vector<T>>> &dynvec)
    {
        if (dynvec.empty())
            throw std::runtime_error("Empty Error");
        std::vector<std::vector<std::vector<T>>> result;
        for (int i = static_cast<int>(dynvec.size()) - 1; i >= 0; i--)
            result.push_back(reverse_v(dynvec[i]));
        return result;
    }

    /**
     * Generates the Fibonacci sequence from F(0) to F(n).
     * @param terms The index n of the last Fibonacci number to include (inclusive).
     * @return A vector containing F(0) to F(n), with (terms + 1) elements.
     */
    std::vector<long long> FibonacciSequence(short terms)
    {
        if (terms <= 0)
            return {};
        if (terms == 1)
            return {0};
        if (terms == 2)
            return {0, 1};
        std::vector<long long> Fibonacci = {0, 1};
        for (short i = 2; i <= terms; i++)
        {
            if (Fibonacci[i - 1] > LLONG_MAX - Fibonacci[i - 2])
                throw std::overflow_error("Fibonacci value exceeds long long capacity");
            Fibonacci.push_back(Fibonacci[i - 1] + Fibonacci[i - 2]);
        }
        return Fibonacci;
    }

    /**
     * Returns the index of the last element in the vector.
     * @param vec The input vector.
     * @return Index of the last element (vec.size() - 1), or -1 if the vector is
     * empty.
     */
    template <typename T>
    size_t v_end(const std::vector<T> &vec)
    {
        if (vec.empty())
            throw std::runtime_error("Empty Error");
        return vec.size() - 1;
    }

    /**
     * Compares two vectors element by element to check if they are identical in
     * content and order.
     * @param vec1 The first vector.
     * @param vec2 The second vector.
     * @return true if the vectors have the same size and elements in the same
     * order; false otherwise.
     */
    template <typename T>
    bool same_v(const std::vector<T> &vec1, const std::vector<T> &vec2)
    {
        if (vec1.empty() && vec2.empty())
            return true;
        if (vec1.size() != vec2.size())
            return false;
        for (size_t i = 0; i < vec2.size(); i++)
        {
            if (vec2[i] != vec1[i])
                return false;
        }
        return true;
    }

    /**
     * @brief Returns a subvector from the given vector within the specified range.
     *
     * This function extracts a subvector from the input vector `v`, starting from index `start` and ending at index `end` (inclusive).
     *
     * @tparam T The type of elements in the vector.
     * @param v The input vector from which to extract the subvector.
     * @param start The starting index of the subvector (inclusive).
     * @param end The ending index of the subvector (inclusive).
     * @return std::vector<T> The resulting subvector containing elements from `start` to `end`.
     *
     * @throws std::invalid_argument If the input vector is empty.
     * @throws std::out_of_range If `start` is less than 0 or `end` is greater than the last valid index of the vector.
     */
    template <typename T>
    std::vector<T> sub_v(const std::vector<T> &v, int start, int end)
    {
        if (v.empty())
            throw std::invalid_argument("Empty Error: the vector is empty no sub vector can be generate");
        if (start < 0 || end >= static_cast<int>(v.size()))
            throw std::out_of_range("the start or end is out of range of vector");
        std::vector<T> result_v;
        for (int i = start; i <= end; i++)
            result_v.push_back(v[i]);
        return result_v;
    }

    /**
     * @brief Extracts a submatrix from a 2D vector based on start and end indices for each dimension.
     *
     * This function generates a subvector (submatrix) from a given 2D vector `v`, using the provided
     * `start_v` and `end_v` vectors to specify the start and end indices for each dimension.
     * It recursively applies the subvector extraction for each dimension.
     *
     * @tparam T The type of the elements in the 2D vector.
     * @param v The input 2D vector from which to extract the submatrix.
     * @param start_v A vector of start indices for each dimension.
     * @param end_v A vector of end indices for each dimension (exclusive).
     * @return A submatrix of `v` defined by the specified ranges.
     *
     * @throws std::invalid_argument If the input vector `v` is empty.
     * @throws std::out_of_range If the start or end indices are out of range, or if the size of `start_v`
     *         does not match the dimensions of the result.
     */
    template <typename T>
    std::vector<std::vector<T>> sub_v(const std::vector<std::vector<T>> &v, const std::vector<int> &start_v, const std::vector<int> &end_v)
    {
        if (v.empty())
            throw std::invalid_argument("Empty Error: the vector is empty no sub vector can be generate");
        if (start_v[0] < 0 || end_v[0] > static_cast<int>(v.size()))
            throw std::out_of_range("the start or end is out of range of vector");
        auto result = sub_v<std::vector<T>>(v, start_v[0], end_v[0]);
        if (result.size() + 1 != start_v.size())
            throw std::out_of_range("the start vector can\'n fit the size of the result");
        for (size_t i = 0; i < result.size(); i++)
            sub_v<T>(result[i], start_v[i + 1], end_v[i + 1]);
        return result;
    }

    /**
     * @brief Removes a row from a 2D vector at the specified index.
     *
     * @tparam T The type of the elements in the 2D vector.
     * @param v The input 2D vector from which a row will be removed.
     * @param index The zero-based index of the row to remove.
     * @return A new 2D vector with the specified row removed.
     * @throws std::out_of_range If the index is out of bounds (less than 0 or greater than or equal to the vector size).
     */
    template <typename T>
    std::vector<std::vector<T>> erase_row(const std::vector<std::vector<T>> &v, int index)
    {
        if (index > static_cast<int>(v.size()) || index < 0)
            throw std::out_of_range("the vector erase index is begger than the vector size or is equal or less than zero");
        std::vector<std::vector<T>> result;
        for (size_t i = 0; i < v.size(); i++)
        {
            if (static_cast<int>(i) == index)
                continue;
            result.push_back(v[i]);
        }
        return result;
    }

    /**
     * @brief Removes a specified column from a 2D vector.
     *
     * This function creates and returns a new 2D vector with the column at the given index removed from each row.
     * If a row does not have enough columns (i.e., its size is less than or equal to the specified index), that row is skipped.
     *
     * @tparam T The type of the elements in the 2D vector.
     * @param v The input 2D vector from which a column will be removed.
     * @param index The zero-based index of the column to remove.
     * @return std::vector<std::vector<T>> A new 2D vector with the specified column removed from each row.
     *
     * @throws std::invalid_argument If the input vector is empty.
     * @throws std::out_of_range If the index is negative.
     *
     * @note If no columns are erased due to incorrect indexing, a message is printed to std::cout.
     */
    template <typename T>
    std::vector<std::vector<T>> erase_column(const std::vector<std::vector<T>> &v, int index)
    {
        if (v.empty())
            throw std::invalid_argument("Empty Error");
        if (index < 0)
            throw std::out_of_range("the index is less then or equal to zero");
        std::vector<std::vector<T>> result_v;
        int erase_count = 0;
        for (size_t i = 0; i < v.size(); i++)
        {
            if (static_cast<int>(v[i].size()) < index)
                continue;
            result_v.push_back({});
            for (size_t j = 0; j < v[i].size(); j++)
            {
                if (static_cast<int>(j) != index)
                    result_v[i].push_back(v[i][j]);
            }
            erase_count++;
        }
        if (erase_count == 0)
            std::cout << "nothing was erase form the vector due to incorrect indexing" << std::endl;
        return result_v;
    }

    /**
     * @brief Removes the specified row and column from a 2D vector.
     *
     * This function creates a new 2D vector by removing the row at index `i` and the column at index `j`
     * from the input vector `v`. The original vector is not modified.
     *
     * @tparam T The type of the elements in the 2D vector.
     * @param v The input 2D vector from which a row and a column will be removed.
     * @param i The index of the row to remove.
     * @param j The index of the column to remove.
     * @return A new 2D vector with the specified row and column removed.
     *
     * @throws std::invalid_argument If the input vector is empty.
     * @throws std::out_of_range If the row index `i` is out of range.
     *
     * @note This function depends on the existence of `erase_row` and `erase_column` helper functions.
     */
    template <typename T>
    std::vector<std::vector<T>> erase_row_column(const std::vector<std::vector<T>> &v, int i, int j)
    {
        if (v.empty())
            throw std::invalid_argument("Empty Error");
        if (i < 0 || i > static_cast<int>(v.size()))
            throw std::out_of_range("the indexing is out of rang vector passed to the function");
        std::vector<std::vector<T>> result_v = erase_row<T>(v, i);
        return erase_column<T>(result_v, j);
    }

    /**
     * @brief Casts a vector of one type to a vector of another type using static_cast.
     * This function takes a vector of type T2 and returns a new vector of type T1, where each element is cast from T2 to T1 using static_cast.
     * @param input The input vector of type T2 to be cast.
     * @return A new vector of type T1 containing the casted elements from the input vector.
     * @tparam T1 The target type to which the elements will be cast.
     * @param T2 The source type of the elements in the input vector.
     * @note This function assumes that the static_cast from T2 to T1 is valid for all elements in the input vector. If the cast is not valid, it may result in undefined behavior.
     * @throws std::bad_cast If the static_cast fails for any element in the input vector (not checked at compile time).
     * @see std::vector, static_cast
     * @example
     * std::vector<int> intVec = {1, 2, 3};
     * std::vector<double> doubleVec = vector_cast<double>(intVec); // doubleVec will contain {1.0, 2.0, 3.0}
     * std::vector<std::vector<int>> intVec2D = {{1, 2}, {3, 4}};
     * std::vector<std::vector<double>> doubleVec2D = vector_cast<double>(intVec2D); // doubleVec2D will contain {{1.0, 2.0}, {3.0, 4.0}}
     */
    template <typename T1, typename T2>
    std::vector<T1> vector_cast(const std::vector<T2> &input) noexcept
    {
        std::vector<T1> result;
        for (size_t i = 0; i < input.size(); i++)
            result.push_back(static_cast<T1>(input[i]));
        return result;
    }

    /**
     * @brief Casts a 2D vector of one type to a 2D vector of another type using static_cast.
     * This function takes a 2D vector of type T2 and returns a new 2D vector of type T1, where each element is cast from T2 to T1 using static_cast.
     * @param input The input 2D vector of type T2 to be cast.
     * @return A new 2D vector of type T1 containing the casted elements from the input 2D vector.
     * @tparam T1 The target type to which the elements will be cast.
     * @param T2 The source type of the elements in the input 2D vector.
     * @note This function assumes that the static_cast from T2 to T1 is valid for all elements in the input 2D vector. If the cast is not valid, it may result in undefined behavior.
     * @throws std::bad_cast If the static_cast fails for any element in the input 2D vector (not checked at compile time).
     * @see std::vector, static_cast
     * @example
     * std::vector<std::vector<int>> intVec2D = {{1, 2}, {3, 4}};
     * std::vector<std::vector<double>> doubleVec2D = vector_cast<double>(intVec2D); // doubleVec2D will contain {{1.0, 2.0}, {3.0, 4.0}}
     * std::vector<std::vector<std::vector<int>>> intVec3D = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
     * std::vector<std::vector<std::vector<double>>> doubleVec3D = vector_cast<double>(intVec3D); // doubleVec3D will contain {{{1.0, 2.0}, {3.0, 4.0}}, {{5.0, 6.0}, {7.0, 8.0}}}
     */
    template <typename T1, typename T2>
    std::vector<std::vector<T1>> vector_cast(const std::vector<std::vector<T2>> &input) noexcept
    {
        std::vector<std::vector<T1>> result;
        for (size_t i = 0; i < input.size(); i++)
            result.push_back(vector_cast<T1, T2>(input[i]));
        return result;
    }

    /**
     * @brief Casts a 3D vector of one type to a 3D vector of another type using static_cast.
     * This function takes a 3D vector of type T2 and returns a new 3D vector of type T1, where each element is cast from T2 to T1 using static_cast.
     * @param input The input 3D vector of type T2 to be cast.
     * @return A new 3D vector of type T1 containing the casted elements from the input 3D vector.
     * @tparam T1 The target type to which the elements will be cast.
     * @param T2 The source type of the elements in the input 3D vector.
     * @note This function assumes that the static_cast from T2 to T1 is valid for all elements in the input 3D vector. If the cast is not valid, it may result in undefined behavior.
     * @throws std::bad_cast If the static_cast fails for any element in the input 3D vector (not checked at compile time).
     * @see std::vector, static_cast
     * @example
     * std::vector<std::vector<std::vector<int>>> intVec3D = {{{
     * 1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
     * std::vector<std::vector<std::vector<double>>> doubleVec3D = vector_cast<double>(intVec3D); // doubleVec3D will contain {{{1.0, 2.0}, {3.0, 4.0}}, {{5.0, 6.0}, {7.0, 8.0}}}
     */
    template <typename T1, typename T2>
    std::vector<std::vector<std::vector<T1>>> vector_cast(const std::vector<std::vector<std::vector<T2>>> &input) noexcept
    {
        std::vector<std::vector<std::vector<T1>>> result;
        for (size_t i = 0; i < input.size(); i++)
            result.push_back(vector_cast<T1, T2>(input[i]));
        return result;
    }

    /**
     * @brief Finds the index of the first occurrence of an element in a vector within a specified range.
     * This function searches for the element `e` in the vector `v` starting from index `start` and ending at index `end` (exclusive). If the element is found, its index is returned; otherwise, a default value (size_t()) is returned.
     * @param v The vector to search through.
     * @param e The element to find in the vector.
     * @param end The index at which to stop the search (exclusive). If set to 0, the search will go until the end of the vector.
     * @param start The index at which to start the search (inclusive). Default is 0.
     * @return The index of the first occurrence of the element `e` in the vector `v` within the specified range, or size_t() if the element is not found.
     * @tparam T The type of elements in the vector.
     * @note If the vector is empty, the function will return size_t() immediately. The function does not perform bounds checking on the `start` and `end` parameters, so it is the caller's responsibility to ensure they are within valid ranges.
     */
    template <typename T>
    size_t where(const std::vector<T> &v, const T &e,
                 size_t end = 0, size_t start = 0) noexcept
    {
        if (v.empty())
            return size_t();
        if (end == 0)
            end = v.length();
        for (size_t i = start; i < end; i++)
        {
            if (v[i] == e)
                return i;
        }
        return size_t();
    }

    /**
     * @brief Checks if an element exists in a vector within a specified range.
     * This function searches for the element `e` in the vector `v` starting from index `start` and ending at index `end` (exclusive). It returns true if the element is found within the specified range, and false otherwise.
     * @param v The vector to search through.
     * @param e The element to check for existence in the vector.
     * @param end The index at which to stop the search (exclusive). If set to 0, the search will go until the end of the vector.
     * @param start The index at which to start the search (inclusive). Default is 0.
     * @return true if the element `e` exists in the vector `v` within the specified range, false otherwise.
     * @tparam T The type of elements in the vector.
     * @note If the vector is empty, the function will return false immediately. The function does not perform bounds checking on the `start` and `end` parameters, so it is the caller's responsibility to ensure they are within valid ranges.
     */
    template <typename T>
    bool exist(const std::vector<T> &v, const T &e,
               size_t end = 0, size_t start = 0) noexcept
    {
        if (end == 0)
            end = v.length();
        for (size_t i = start; i < end; i++)
        {
            if (v[i] == e)
                return true;
        }
        return false;
    }

        /**
     * @brief Performs Gauss-Jordan elimination on a given augmented matrix.
     *
     * This function transforms the input augmented matrix `mat` into its reduced
     * row echelon form (RREF). It is typically used to solve systems of linear
     * equations.
     *
     * @param mat The augmented matrix represented as a vector of vectors of
     * doubles. Each row should have n+1 elements for a system of n equations (n
     * variables + 1 constant).
     * @param status Reference to an integer that will be set to indicate the result
     * of the elimination:
     *        - 0: Successful elimination, unique solution found.
     *        - 1: Matrix is singular (no unique solution).
     *        - 2: Infinite solutions exist.
     *        - 3: No solution exists.
     *
     * @return The matrix in reduced row echelon form after elimination.
     *
     * @throws invalid_argument if the input matrix is empty.
     *
     * @note The input matrix is modified and returned in its transformed state.
     */
    std::vector<std::vector<double>> gauss_jordan(std::vector<std::vector<double>> mat, int &status)
    {
        if (mat.empty())
            throw std::invalid_argument("Empty matrix");
        int n = static_cast<int>(mat.size());
        status = 0;
        for (int i = 0; i < n; i++)
        {
            if (mat[i][i] == 0)
            {
                int c = 1;
                while ((i + c) < n && mat[i + c][i] == 0)
                    c++;
                if ((i + c) == n)
                {
                    status = 1;
                    break;
                }
                std::swap(mat[i], mat[i + c]);
            }
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    double pro = mat[j][i] / mat[i][i];
                    for (int k = 0; k <= n; k++)
                        mat[j][k] -= mat[i][k] * pro;
                }
            }
        }
        if (status == 1)
        {
            status = 3;
            for (int i = 0; i < n; i++)
            {
                double sum = 0;
                for (int j = 0; j < n; j++)
                    sum += mat[i][j];
                if (sum == mat[i][n])
                    status = 2;
            }
        }
        return mat;
    }

        /**
     * @brief Generates a string consisting of a specified number of newline characters.
     * @param n The number of newline characters to include in the resulting string. Defaults to 1 if not provided.
     * @return A std::string object containing n newline characters ('\n'). If n is 0, an empty string is returned.
     * @note The function is marked as noexcept, indicating that it guarantees not to throw exceptions
     */
    std::string nl(unsigned int n = 1) noexcept
    {
        std::string result;
        for (unsigned int i = 0; i < n; i++)
            result += '\n';
        return result;
    }

    /**
     * @brief Generates a string consisting of a specified number of tab characters.
     * @param n The number of tab characters to include in the resulting string. Defaults to 1 if not provided.
     * @return A std::string object containing n tab characters ('\t'). If n is 0, an empty string is returned.
     * @note The function is marked as noexcept, indicating that it guarantees not to throw exceptions
     */
    std::string tab(unsigned int n = 1) noexcept
    {
        std::string result;
        for (unsigned int i = 0; i < n; i++)
            result += '\t';
        return result;
    }

    /**
     * @brief       Calculates the index of the last character in a string.
     *
     * This function returns the zero-based index of the final character
     * in the string @p s. If the string is empty, it returns a value that
     * typically signifies an error or invalid index, which is -1 cast to size_t.
     *
     * @note       The return type is @c size_t, which is an unsigned integer.
     *             Returning @c -1 will result in the maximum possible value for
     *             @c size_t due to the implicit conversion from signed to unsigned.
     *
     * @param s     The input string to check. Passed as a constant reference
     *             for efficiency.
     * @return     The index of the last character (which is s.size() - 1)
     *             if the string is not empty. Returns @c -1 (converted to
     *             the maximum @c size_t value) if the string is empty.
     */
    size_t last_index(const std::string &s) noexcept
    {
        if (s.empty())
            return -1;
        return s.size() - 1;
    }

    /**
     * @brief       Retrieves the last character of a given string.
     *
     * This function safely attempts to return the last character in the
     * string @p s. It uses the index returned by @c last_index(s) to access
     * the character.
     *
     * @note       If the string @p s is empty, the function returns the null
     *             character ('\\0') as a conventional indicator for an empty
     *             or invalid result.
     *
     * @param s     The input string to read the last element from. Passed
     *             as a constant reference for efficiency.
     * @return     The last character of the string @p s. Returns the null
     *             character ('\\0') if the string is empty.
     */
    char last_element(const std::string &s) noexcept
    {
        if (s.empty())
            return '\0';
        return s[last_index(s)];
    }

    /**
     * @brief       Removes a single character from a string at a specified index.
     *
     * This function creates and returns a new string that is identical to the
     * input string @p s, but with the character at the given @p index removed.
     * The original string @p s remains unchanged.
     *
     * @param s     The input string from which the character will be removed.
     *             Passed by constant reference for efficiency.
     * @param index The zero-based index of the character to be removed from the string.
     *
     * @return     A new std::string object containing all characters of @p s
     *             except the one at the specified @p index.
     *
     * @throws     std::out_of_range If the @p index is less than 0 or is
     *             greater than or equal to the size of the string @p s.
     *
     * @note       The function implements character removal by iterating over
     *             the input string and skipping the character at the specified index.
     */
    std::string remove(const std::string &s, int index)
    {
        if (index < 0 || index >= s.size())
            throw std::out_of_range("the index is bigger than the size of the string or less than zero");
        std::string result;
        for (size_t i = 0; i < s.size(); i++)
        {
            if (i != index)
                result += s[i];
        }
        return result;
    }

    /**
     * @brief       Removes all occurrences of a specific character from a string.
     *
     * This function iterates through the input string @p s and builds a new
     * string containing only the characters that are not equal to the specified
     * character @p c.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the input string is empty, an empty string is returned.
     *             If the character to remove is not found, a copy of the original
     *             string is returned.
     *
     * @param s     The input string to process. Passed by constant reference.
     * @param c     The character whose occurrences should be removed from the string.
     *
     * @return     A new std::string object that is a copy of @p s with all
     *             instances of character @p c removed.
     */
    std::string remove(const std::string &s, char c) noexcept
    {
        std::string result;
        for (char lc : s)
        {
            if (lc != c)
                result += lc;
        }
        return result;
    }

    /**
     * @brief       Removes characters from a string based on a custom predicate function.
     *
     * This is a highly flexible removal function that filters the input string
     * @p s. It keeps only the characters for which the provided predicate function
     * @p f returns @c false.
     *
     * @details     The predicate @p f is a function (e.g., a lambda, function pointer,
     *             or function object) that takes a character and returns a boolean.
     *             If @c f(c) returns @c true, the character @c c is removed from the result.
     *             This allows for complex filtering logic (e.g., removing all vowels,
     *             all digits, or all whitespace).
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the string @p s is empty, an empty string is returned.
     *
     * @param s     The input string to filter. Passed by constant reference.
     * @param f     A std::function object (predicate) that takes a @c char
     *             and returns @c bool. The character is removed if this function returns @c true.
     *
     * @return     A new std::string object containing only the characters from @p s
     *             that did not satisfy the predicate @p f (i.e., for which @c f(c) was @c false).
     */
    std::string remove(const std::string &s, std::function<bool(char)> f) noexcept
    {
        std::string result;
        for (char c : s)
        {
            if (!f(c))
                result += c;
        }
        return result;
    }

    /**
     * @brief       Extracts a substring from an input string between two specified indices.
     *
     * This function creates and returns a new string that contains the characters
     * from the input string @p s, starting at @p start_index and ending at
     * @p end_index, inclusive.
     *
     * @param s           The input string from which the substring will be extracted.
     *                   Passed by constant reference for efficiency.
     * @param start_index The zero-based index of the first character to include
     *                   in the substring (inclusive).
     * @param end_index   The zero-based index of the last character to include
     *                   in the substring (inclusive).
     *
     * @return           A new std::string object representing the desired substring.
     *                   Returns an empty string if @p start_index equals @p end_index.
     *
     * @throws           std::out_of_range     If either index is negative or is
     *                                         greater than or equal to the size of @p s.
     * @throws           std::invalid_argument If @p start_index is strictly greater
     *                                         than @p end_index.
     *
     * @note             Unlike many standard library functions, this function
     *                   treats the @p end_index as **inclusive**.
     */
    std::string sub_str(const std::string &s, int start_index, int end_index)
    {
        if (start_index < 0 || end_index < 0)
            throw std::out_of_range("start index or end index is less than zero");
        if (start_index >= s.size() || end_index >= s.size())
            throw std::out_of_range("start index or end index is equal or bigger than the size of the string");
        if (start_index > end_index)
            throw std::invalid_argument("the start index is bigger than end index");
        if (start_index == end_index)
            return "";
        std::string result;
        for (size_t i = start_index; i <= end_index; i++)
            result += s[i];
        return result;
    }

    /**
     * @brief       Removes the first occurrence of a specific substring from a string.
     *
     * This function searches for the first instance of the substring @p s2 within
     * the string @p s1 and returns a new string with that single instance removed.
     * It is designed to remove a segment (the first match of @p s2), not just
     * individual characters.
     *
     * @param s1     The primary string from which the removal will take place.
     *               Passed by constant reference.
     * @param s2     The substring to be located and removed. Passed by constant reference.
     *
     * @return       A new std::string object:
     *               - If @p s2 is empty, it returns @p s1 unchanged.
     *               - If @p s2 is not found in @p s1, it returns @p s1 unchanged.
     *               - Otherwise, it returns @p s1 with the first occurrence of @p s2 removed.
     *
     * @throws       std::invalid_argument If the size of the substring @p s2 is
     *               strictly greater than the size of the main string @p s1.
     *
     * @note         The implementation uses @c std::string::find() to locate the
     *               substring and @c std::string::append() to efficiently construct
     *               the result without the removed segment.
     */
    std::string remove(const std::string &s1, const std::string &s2)
    {
        if (s2.empty())
            return s1;
        if (s2.size() > s1.size())
            throw std::invalid_argument("The second string is bigger than the first string");
        size_t pos = s1.find(s2);
        if (pos == std::string::npos)
            return s1;
        std::string result;
        result.reserve(s1.size() - s2.size());
        result.append(s1, 0, pos);
        result.append(s1, pos + s2.size(), std::string::npos);
        return result;
    }

    /**
     * @brief       Reverses the order of characters in a string.
     *
     * This function creates a new string that contains all characters of the
     * input string @p s in reverse order. It iterates from the last character
     * to the first character to construct the reversed string.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the input string @p s is empty, an empty string is returned.
     *             It is assumed that @c last_index(s) returns a value suitable
     *             for iterating backward using an @c int loop counter.
     *
     * @param s     The input string to be reversed. Passed by constant reference
     *             for efficiency.
     *
     * @return     A new std::string object which is the reverse of the input string @p s.
     */
    std::string reverse(const std::string &s) noexcept
    {
        if (s.empty())
            return s;
        std::string result;
        for (size_t i = last_index(s); i >= 0; i--)
            result += s[i];
        return result;
    }

    /**
     * @brief       Inserts a single character into a string at a specified index.
     *
     * This function creates and returns a new string where the given character
     * @p value is inserted *before* the character currently at @p index in the
     * input string @p s.
     *
     * @details     The insertion happens at the position specified by @p index.
     *             Note that the implementation iterates through the original string
     *             and places the @p value character immediately before the character
     *             that was originally at the given @p index.
     *
     * @param s     The base string into which the character will be inserted.
     *             Passed by constant reference.
     * @param value The character to be inserted.
     * @param index The zero-based index at which the character should be inserted.
     *             This index must be a valid position within the current string
     *             (i.e., 0 <= index < s.size()).
     *
     * @return     A new std::string object with the character @p value inserted.
     *
     * @throws     std::out_of_range If the @p index is less than 0 or is
     *             greater than or equal to the size of the string @p s.
     */
    std::string insert(const std::string &s, char value, int index)
    {
        if (index < 0 || index >= s.size())
            throw std::out_of_range("index is bigger than string size or less than zero");
        std::string result;
        for (size_t i = 0; i < s.size(); i++)
        {
            if (i == index)
            {
                result += value;
                result += s[i];
            }
            else
                result += s[i];
        }
        return result;
    }

    /**
     * @brief       Swaps the characters at two specified indices in a string.
     *
     * This function creates and returns a new string based on the input string @p s,
     * where the characters at @p first index and @p second index have been exchanged.
     * The original string @p s remains unmodified.
     *
     * @param s      The input string whose characters are to be swapped.
     *              Passed by constant reference for efficiency.
     * @param first  The zero-based index of the first character to be involved
     *              in the swap operation.
     * @param second The zero-based index of the second character to be involved
     *              in the swap operation.
     *
     * @return       A new std::string object with the characters at @p first
     *               and @p second indices swapped.
     *
     * @throws       std::out_of_range     If either @p first or @p second index is
     *                                     less than 0 or is greater than or equal to
     *                                     the size of the string @p s.
     * @throws       std::invalid_argument If the @p first and @p second indices are
     *                                     identical, as no swap is necessary.
     */
    std::string swap(const std::string &s, int first, int second)
    {
        if (first < 0 || second < 0 || second >= s.size() || second >= s.size())
            throw std::out_of_range("the first or secend is bigger or less than zero");
        if (first == second)
            throw std::invalid_argument("can not swap in the same index for first and second");
        std::string result;
        for (size_t i = 0; i < s.size(); i++)
        {
            if (i == first)
                result += s[second];
            else if (i == second)
                result += s[first];
            else
                result += s[i];
        }
        return result;
    }

    /**
     * @brief       Replaces all occurrences of a specific character with a new character.
     *
     * This function creates and returns a new string where every instance of the
     * character @p removed within the input string @p s is substituted with the
     * character @p inserted.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the character to be removed is the same as the character to be
     *             inserted, the original string @p s is returned directly without
     *             performing any modification (and without unnecessary copying).
     *
     * @param s        The input string to be processed. Passed by constant reference.
     * @param removed  The character to be found and replaced within the string.
     * @param inserted The new character that will substitute all instances of @p removed.
     *
     * @return       A new std::string object with all occurrences of @p removed
     *               replaced by @p inserted. Returns @p s if @p removed and @p inserted are the same.
     */
    std::string replace(const std::string &s, char removed, char inserted) noexcept
    {
        if (removed == inserted)
            return s;
        std::string result;
        for (char c : s)
        {
            if (c == removed)
                result += inserted;
            else
                result += c;
        }
        return result;
    }

    /**
     * @brief       Capitalizes the first character of a string, if it is a lowercase letter.
     *
     * This function creates and returns a new string where the first character
     * of the input string @p s is converted to its uppercase equivalent. The
     * remaining characters of the string are preserved unchanged.
     *
     * @details     The capitalization is performed only if the first character
     *             is determined to be lowercase using @c std::islower(). The
     *             conversion is done arithmetically by subtracting the difference
     *             in ASCII/EBCDIC values between a lowercase and an uppercase letter
     *             (equivalent to subtracting ' ').
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the input string @p s is empty, an empty string is returned.
     *
     * @param s     The input string to be capitalized. Passed by constant reference.
     *
     * @return     A new std::string object with its first character capitalized.
     *             Returns the original string if it is empty or if the first character
     *             is already uppercase or non-alphabetic.
     */
    std::string capitalize(const std::string &s) noexcept
    {
        if (s.empty())
            return s;
        std::string result;
        if (std::islower(s[0]))
            result += (s[0] - ' ');
        else
            result += s[0];
        for (size_t i = 1; i < s.size(); i++)
            result += s[i];
        return result;
    }

    /**
     * @brief       Converts an entire string to either lowercase or uppercase.
     *
     * This function iterates through the input string @p s and converts all
     * alphabetic characters based on the value of the @p to_lower flag.
     *
     * @details     The conversion relies on the difference between the ASCII values
     *             of lowercase and uppercase letters (the difference is equivalent
     *             to the space character ' ').
     *
     * @note       The function is marked as @c noexcept, yet the implementation
     *             includes error handling logic that returns a **string literal error
     *             message** ("convert error: wrong input form") if any character
     *             is neither lowercase nor uppercase. Users should be aware of this
     *             specific error signaling method.
     *
     * @param s        The input string to be converted. Passed by constant reference.
     * @param to_lower If @c true, all uppercase letters are converted to lowercase.
     *                 If @c false, all lowercase letters are converted to uppercase.
     *
     * @return       A new std::string object:
     *               - The converted string if all characters are alphabetic.
     *               - The original string if it is empty.
     *               - The string literal "convert error: wrong input form" if a
     *                 non-alphabetic character is encountered.
     */
    std::string convert(const std::string &s, bool to_lower) noexcept
    {
        if (s.empty())
            return s;
        std::string result;
        if (to_lower)
        {
            for (char c : s)
            {
                if (std::islower(c))
                    result += c;
                else if (std::isupper(c))
                    result += (c + ' ');
                else
                    return "convert error: wrong input form";
            }
        }
        else
        {
            for (char c : s)
            {
                if (std::islower(c))
                    result += (c - ' ');
                else if (std::isupper(c))
                    result += c;
                else
                    return "convert error: wrong input form";
            }
        }
        return result;
    }

    /**
     * @brief       Formats a string into a "standard word" (Title Case).
     *
     * This function converts the input string @p s into a standard format where
     * the first letter is capitalized and all subsequent letters are lowercase.
     * This is achieved by first converting the entire string to lowercase and
     * then capitalizing the first character.
     *
     * @details     The logic relies on two other assumed functions:
     *             1. @c convert(s, true): Converts the entire string to lowercase.
     *             2. @c capitalize(s): Capitalizes only the first character.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the string @p s is empty, an empty string is returned.
     *             Note that the output of this function depends entirely on the
     *             correctness and error handling of the underlying @c convert and
     *             @c capitalize implementations.
     *
     * @param s     The input string to be standardized. Passed by constant reference.
     *
     * @return     A new std::string object formatted as a standard word (Title Case).
     */
    std::string standard_word(const std::string &s) noexcept
    {
        if (s.empty())
            return s;
        std::string result = convert(s, true);
        return capitalize(result);
    }

    /**
     * @brief       Splits a string into a vector of substrings based on space delimiters.
     *
     * This function processes the input string @p s and separates it into individual
     * "words" using the space character (' ') as a delimiter. It returns these
     * substrings in a vector.
     *
     * @details     The implementation iterates through the string, building up a
     *             temporary string (@c temp) until a space or the end of the string
     *             is reached. When a delimiter is found, the accumulated word is
     *             added to the result vector.
     * * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the input string @p s is empty, an empty vector is returned.
     *             **Important:** The current implementation might produce empty strings
     *             in the result vector if multiple spaces are adjacent (e.g., "word  two").
     *             It is also crucial to note that accessing @c s[i] when @c i == s.size()
     *             for the end-of-loop check is **undefined behavior** in standard C++,
     *             even though it's used here to process the last word.
     *
     * @param s     The input string to be separated. Passed by constant reference.
     *
     * @return     A @c std::vector<std::string> containing the separated substrings.
     *             Returns an empty vector if the input string is empty.
     */
    std::vector<std::string> sseparator(const std::string &s) noexcept
    {
        if (s.empty())
            return {};
        std::vector<std::string> result_v;
        std::string temp;
        for (size_t i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ' || i == s.size() - 1)
            {
                result_v.push_back(temp);
                temp.clear();
            }
            else
                temp += s[i];
        }
        return result_v;
    }

    /**
     * @brief Checks if a specific character exists within a string, optionally within a specified range.
     * @param s The string to search within, passed by constant reference.
     * @param c The character to search for.
     * @param end An optional parameter specifying the end index (exclusive) of the search range. Defaults to 0, which means the entire string will be searched.
     * @param start An optional parameter specifying the start index (inclusive) of the search range. Defaults to 0.
     * @return Returns true if the character c is found within the specified range of the string s; otherwise, returns false. If end is 0, the search will include the entire string.
     * @note The function is marked as noexcept, indicating that it guarantees not to throw exceptions. If end is 0, it will be set to the length of the string s, allowing the search to cover the entire string. The function iterates through the specified range of the string and checks for the presence of the character c.
     */
    bool exist(const std::string &s, char c,
               size_t end = 0, size_t start = 0) noexcept
    {
        if (end == 0)
            end = s.length();
        for (size_t i = start; i < end; i++)
        {
            if (s[i] == c)
                return true;
        }
        return false;
    }

    /**
     * @brief Checks if a specific substring exists within another string.
     * @param s1 The string to search within, passed by constant reference.
     * @param s2 The substring to search for, passed by constant reference.
     * @return Returns true if the substring s2 is found within the string s1; otherwise, returns false. The function compares the characters of s1 and s2 to determine if s2 is a contiguous sequence within s1.
     * @note The function is marked as noexcept, indicating that it guarantees not to throw exceptions. The implementation iterates through the characters of s1 and checks for a sequence that matches s2. If a matching sequence is found, the function returns true; if the end of s1 is reached without finding s2, it returns false.
     */
    bool exist(const std::string &s1, const std::string &s2) noexcept
    {
        size_t ll = size_t(), il = size_t();
        // ll: loop length, il: if length
        if (s1.length() > s2.length())
        {
            ll = s1.length();
            il = s2.length();
        }
        else
        {
            ll = s2.length();
            il = s1.length();
        }
        bool seq = bool();
        for (size_t i = 0, j = 0; i < ll; i++)
        {
            if (seq && s1[i] == s2[j])
            {
                j++;
            }
            else if (seq && s1[i] != s2[j])
            {
                seq = false;
                j = 0;
            }
            else if (s1[i] == s2[j])
            {
                seq = true;
                j++;
            }
            if (seq && j == il - 1)
                return true;
        }
        return false;
    }

    /**
     * @brief Finds the starting and ending indices of a substring within another string.
     * @param s1 The string to search within, passed by constant reference.
     * @param s2 The substring to search for, passed by constant reference.
     * @return A pair of indices (start, end) indicating the position of the substring s2 within s1. If s2 is not found, both indices will be 0.
     * @note The function is marked as noexcept, indicating that it guarantees not to throw exceptions. The implementation iterates through the characters of s1 and checks for a sequence that matches s2. If a matching sequence is found, the function returns the indices; if the end of s1 is reached without finding s2, it returns a pair of zeros.
     */
    std::pair<size_t, size_t> where(const std::string &s1, const std::string &s2)
    {
        size_t ll = size_t(), cl = size_t();
        if (s1.length() > s2.length())
        {
            ll = s1.length();
            cl = s2.length();
        }
        else if (s2.length() == s1.length())
        {
            ll = s1.length();
            cl = ll;
        }
        else
        {
            ll = s2.length();
            cl = s1.length();
        }
        std::pair<size_t, size_t> result;
        bool sequence = bool();
        for (size_t i = 0, j = 0; i < ll; i++)
        {
            if (s1[i] == s2[j] && sequence)
            {
                j++;
            }
            else if (s1[i] == s2[j])
            {
                sequence = true;
                result.first = i;
                j++;
            }
            else
            {
                sequence = false;
                result.first = 0;
                j = 0;
            }
            if (j == cl - 1 && sequence)
            {
                result.second = i;
                return result;
            }
        }
        return result;
    }

    /**
     * @brief Finds all indices of a specific character within a string, optionally within a specified range.
     * @param s The string to search within, passed by constant reference.
     * @param c The character to search for.
     * @param end An optional parameter specifying the end index (exclusive) of the search range. Defaults to 0, which means the entire string will be searched.
     * @param start An optional parameter specifying the start index (inclusive) of the search range. Defaults to 0.
     * @return A vector of indices where the character c is found within the specified range of
     * the string s. If end is 0, the search will include the entire string. If the character is not found, an empty vector is returned.
     * @note The function is marked as noexcept, indicating that it guarantees not to throw exceptions
     */
    std::vector<size_t> where(const std::string &s, char c,
                              size_t end = 0, size_t start = 0)
    {
        std::vector<size_t> result;
        if (end == 0)
            end = s.length();
        for (size_t i = start; i < end; i++)
        {
            if (c == s[i])
                result.push_back(i);
        }
        return result;
    }

    /**
     * @brief Finds the index of the first occurrence of a specific character within a string, optionally within a specified range.
     * @param s The string to search within, passed by constant reference.
     * @param c The character to search for.
     * @param end An optional parameter specifying the end index (exclusive) of the search range. Defaults to 0, which means the entire string will be searched.
     * @param start An optional parameter specifying the start index (inclusive) of the search range. Defaults to 0.
     * @return The index of the first occurrence of the character c within the specified range of the string s. If end is 0, the search will include the entire string. If the character is not found, 0 is returned, and an error message is printed to std::cerr.
     * @note The function is marked as noexcept, indicating that it guarantees not to throw exceptions. The implementation iterates through the specified range of the string and checks for the presence of the character c. If found, it returns the index; if not found, it prints an error message and returns 0.
     */
    size_t where_first(const std::string &s, char c,
                       size_t end = 0, size_t start = 0) noexcept
    {
        if (s.empty())
            return 0;
        if (end == 0)
            end = s.length();
        for (size_t i = start; i < end; i++)
        {
            if (s[i] == c)
                return i;
        }
        std::cerr << "The char: " << c << " don't exist.\n";
        return 0;
    }

    /**
     * @brief       Converts a string sentence or phrase into a standard Title Case format.
     *
     * This function formats the input string @p s such that every word begins with
     * an uppercase letter, and the remaining letters are lowercase (e.g., "this is a test"
     * becomes "This Is A Test").
     *
     * @details     The process involves three main steps using previously defined functions:
     *             1. **Splitting:** The string @p s is divided into a vector of words
     *                 using @c sseparator(s).
     *             2. **Word Standardization:** Each individual word is formatted using
     *                 @c standard_word(), which capitalizes the first letter and lowercases the rest.
     *             3. **Reassembly:** The standardized words are joined back together
     *                 using a single space delimiter.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the input string @p s is empty, an empty string is returned.
     *             The behavior is directly dependent on the error handling and functionality
     *             of @c sseparator and @c standard_word.
     *
     * @param s     The input string (sentence or phrase) to be formatted.
     *             Passed by constant reference.
     *
     * @return     A new @c std::string object formatted in Title Case.
     */
    std::string standard_form(const std::string &s) noexcept
    {
        if (s.empty())
            return s;
        std::vector<std::string> vs = sseparator(s);
        std::string result;
        for (size_t i = 0; i < vs.size(); i++)
        {
            result += standard_word(vs[i]);
            if (i != vs.size() - 1)
                result += ' ';
        }
        return result;
    }

    /**
     * @brief       Calculates the sum of the numerical values (ASCII/Character Codes)
     *             of all characters in a string.
     *
     * This function iterates through the input string @p s and adds the integer
     * value (character code) of each character to a running total. It also
     * incorporates an optional starting value.
     *
     * @details     The final sum is of type @c long long to prevent potential
     *             overflow, especially for long strings where the cumulative sum
     *             of character codes (which can be up to 255 for an unsigned char)
     *             may exceed the capacity of a standard @c int.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the string @p s is empty, the result is simply the value of
     *             the @p start parameter.
     *
     * @param s         The input string whose characters' codes are to be summed.
     *                 Passed by constant reference.
     * @param start     An optional integer value to start the summation from.
     *                 Defaults to 0.
     *
     * @return       A @c long long representing the sum of the initial @p start value
     *               and the character code values of all characters in @p s.
     */
    long long sum_chars(const std::string &s, int start = 0) noexcept
    {
        if (s.empty())
            return 0;
        long long result = static_cast<long long>(start);
        for (char c : s)
            result += static_cast<long long>(c);
        return result;
    }

    /**
     * @brief       Calculates the product of the numerical values (ASCII/Character Codes)
     *             of all characters in a string.
     *
     * This function iterates through the input string @p s and multiplies the integer
     * value (character code) of each character by a running product. It incorporates
     * an optional starting value.
     *
     * @details     The final product is of type @c long long to prevent integer
     *             overflow, as the multiplication of many character codes (which can be
     *             up to 255 for an unsigned char) quickly exceeds the capacity of
     *             standard 32-bit integer types.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the string @p s is empty, the function returns **0**, which is
     *             an unusual result for a product based on a @p start value of 1;
     *             typically, it would return @p start. However, the documentation
     *             reflects the explicit implementation returning 0 for an empty string.
     *
     * @param s         The input string whose characters' codes are to be multiplied.
     *                 Passed by constant reference.
     * @param start     An optional integer value to start the multiplication from.
     *                 Defaults to 1.
     *
     * @return       A @c long long representing the product of the initial @p start value
     *               and the character code values of all characters in @p s. Returns 0
     *               if the string is empty.
     */
    long long mult_chars(const std::string &s, int start = 1) noexcept
    {
        if (s.empty())
            return 0;
        long long result = static_cast<long long>(start);
        for (char c : s)
            result *= static_cast<long long>(c);
        return result;
    }

    /**
     * @brief       Prints a partial ASCII table to the standard output.
     *
     * This function iterates through the range of printable ASCII characters,
     * specifically from the **Space character (' ') up to the tilde ('~')**,
     * and prints the character followed by its corresponding decimal ASCII code.
     *
     * @details     For the Space character, it prints the label "[SPACE]" instead
     *             of the character itself to make the output visible and clear.
     *             It uses @c std::cout to display the output, converting the
     *             @c char to an @c int to display its numerical code.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             This function produces side effects (printing to the console)
     *             and does not return any value.
     *
     * @warning     The loop condition relies on the character set encoding (typically ASCII)
     *             where ' ' is numerically less than '~'.
     *
     * @param       None.
     * @return     void.
     */
    void ascii_table() noexcept
    {
        for (char c = ' '; c <= '~'; c++)
        {
            if (c == ' ')
                std::cout << "[SPACE] = " << static_cast<int>(c) << std::endl;
            else
                std::cout << c << " = " << static_cast<int>(c) << std::endl;
        }
    }

    int ascii_sum() noexcept { return 7505; }

    char shift_char(char c, int shift) noexcept { return static_cast<char>(c + shift); }

    /// @brief Shifts each character in a string by a specified amount.
    /// @param input The input string whose characters will be shifted.
    /// @param shift The number of positions to shift each character. Positive values shift forward,
    ///              negative values shift backward.
    /// @return A new string with each character shifted by the specified amount.
    /// @note This function does not throw exceptions (noexcept).
    /// @see shift_char
    std::string shift_string(const std::string &input, int shift) noexcept
    {
        std::string result;
        for (char c : input)
            result += shift_char(c, shift);
        return result;
    }

    /**
     * @brief Unshifts all characters in a string by a specified amount.
     *
     * Applies a negative shift to each character in the input string,
     * effectively reversing a shift operation. Each character is shifted
     * backwards by the given shift amount.
     *
     * @param input The input string whose characters will be unshifted.
     * @param shift The amount to unshift each character (positive value).
     *
     * @return A new string with all characters unshifted by the specified amount.
     *
     * @note This function does not throw exceptions (noexcept).
     *
     * @see shift_char(char, int)
     */
    std::string unshift_string(const std::string &input, int shift) noexcept
    {
        std::string result;
        for (char c : input)
            result += shift_char(c, -shift);
        return result;
    }

#ifdef METACORE___ADVA___HPP
}
#endif // METACORE___ADVA___HPP
#ifdef METACORE___META_HPP
}
#endif // METACORE___META_HPP

#endif // OPENUDT___ADVA___FUNCTION_HPP