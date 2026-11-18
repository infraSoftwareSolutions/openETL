/**
 * @file function.hpp
 * @date 2025/9/25
 * @author Ali Lafi
 */

#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "cformat/structure.h"
#include "cformat/types.h"

#pragma once
#ifndef ETL___FUNCTION_HPP
#define ETL___FUNCTION_HPP

namespace etl {
    size_t to_hash(const ocf::str& s) {
        short shift = 0;
        size_t xor_val = 1;
        size_t result = 0;
        size_t index = 1;
        for(char c : s) {
            shift += (size_t)c % 2;
            result += (size_t)c * index;
            xor_val *= c;
            index++;
        }
        shift = shift >= 9 ? shift % 9 : shift + s.length() % 3;
        result = (result * s.length()) << shift;
        return result ^ (xor_val % 16);
    }

    /**
     * Reverses a vector of any type.
     * @param input: The input vector to reverse.
     * @return A new vector containing the elements in reverse order.
     */
    template <typename T>
    ocf::vec<T> reverse(const ocf::vec<T> &input) noexcept
    {
        if(input.empty()) return ocf::vec<T>();
        ocf::vec<T> result;
        for(iter_high(i, input.size())) {
            result.push_back(input[i - 1]);
        }
        return result;
    }

    /**
     * reverses a 2D vector (vector of vectors) of any type.
     * @param input: The input 2D vector to reverse.
     * @return A new 2D vector containing the elements in reverse order.
     */
    template <typename T>
    ocf::vec<ocf::vec<T>>& reverse_2d(const ocf::vec<ocf::vec<T>> &input) noexcept
    {
        if(input.empty()) ocf::vec<ocf::vec<T>>();
        ocf::vec<ocf::vec<T>> result;
        for(iter_high(i, input.size())) {
            result.push_back(reverse_v(input[i - 1]));
        }
        return result;
    }

    /**
     * reverses a 3D vector (vector of vector of vectors) of any type.
     * @param input: The input 3D vector to reverse.
     * @return A new 3D vector containing the elements in reverse order.
     */
    template <typename T>
    ocf::vec<ocf::vec<ocf::vec<T>>>& reverse_3d(const ocf::vec<ocf::vec<ocf::vec<T>>> &input) noexcept
    {
        if(input.empty()) return ocf::vec<ocf::vec<ocf::vec<T>>>();
        ocf::vec<ocf::vec<ocf::vec<T>>> result;
        for(iter_high(i, input.size())) {
            result.push_back(reverse_v(input[i - 1]));
        }
        return result;
    }

    /**
     * Generates the Fibonacci sequence from F(0) to F(n).
     * @param terms The index n of the last Fibonacci number to include (inclusive).
     * @return A vector containing F(0) to F(n), with (terms + 1) elements.
     */
    ocf::vec<size_t> FibonacciSequence(uint8_t terms) noexcept
    {
        if(terms <= 0) {
            return {};
        }
        if(terms == 1) {
            return {0};
        }
        if(terms == 2) {
            return {0, 1};
        }
        ocf::vec<size_t> Fibonacci = {0, 1};
        for(uint8_t i = 2; i <= terms; i++)
        {
            if(Fibonacci[i - 1] > LLONG_MAX - Fibonacci[i - 2]) {
                return Fibonacci;
            }
            Fibonacci.push_back(Fibonacci[i - 1] + Fibonacci[i - 2]);
        }
        return Fibonacci;
    }

    /**
     * Returns the index of the last element in the vector.
     * @param input The input vector.
     * @return Index of the last element (vec.size() - 1), or -1 if the vector is empty.
     */
    template <typename T>
    size_t end(const ocf::vec<T> &input) noexcept
    {
        if(input.empty()) return 0;
        return input.size() - 1;
    }

    /**
     * Compares two vectors element by element to check if they are identical in
     * content and order.
     * @param in1 The first vector.
     * @param in2 The second vector.
     * @return true if the vectors have the same size and elements in the same order; false otherwise.
     */
    template <typename T>
    bool isEqual(const ocf::vec<T> &in1, const ocf::vec<T> &in2) noexcept
    {
        if(in1.empty() && in2.empty()) return true;
        if(in1.size() != in2.size()) return false;
        for(iter_less(i, in1.size()))
        {
            if(in2[i] != in1[i])
                return false;
        }
        return true;
    }

    /**
     * @brief Returns a subvector from the given vector within the specified range.
     *
     * This function extracts a subvector from the input vector `input`, starting from index `start` and ending at index `end` (inclusive).
     *
     * @tparam T The type of elements in the vector.
     * @param input The input vector from which to extract the subvector.
     * @param start The starting index of the subvector (inclusive).
     * @param end The ending index of the subvector (inclusive).
     * @return ocf::vec<T> The resulting subvector containing elements from `start` to `end`.
     *
     * @note this function is noexcept.
     */
    template <typename T>
    ocf::vec<T> sub(const ocf::vec<T> &input, size_t start, size_t end)
    {
        if(v.empty()) return ocf::vec<T>();
        if(end >= input.size()) end = input.length();
        ocf::vec<T> result;
        for(iter_in_range(i, start, end, 1)) {
            result.push_back(input[i]);
        }
        return result;
    }

    /**
     * @brief Extracts a submatrix from a 2D vector based on start and end indices for each dimension.
     *
     * This function generates a subvector (submatrix) from a given 2D vector `input`, using the provided
     * `indexs` unordered map to specify the start and end indices for each dimension.
     * It recursively applies the subvector extraction for each dimension.
     *
     * @tparam T The type of the elements in the 2D vector.
     * @param input The input 2D vector from which to extract the submatrix.
     * @param indexs A vector of start indices for each dimension.
     * @return A submatrix of `input` defined by the specified ranges.
     * 
     * @note this function is noexcept.
     */
    template <typename T>
    ocf::vec<ocf::vec<T>> sub_2d(
        const ocf::vec<ocf::vec<T>> &input, 
        const std::unordered_map<size_t, size_t> indexs) noexcept
    {
        if(v.empty()) return ocf::vec<ocf::vec<T>>();
        ocf::vec<ocf::vec<T>> result;
        for(auto loop : indexs) {
            result.push_back(sub(input, loop.first, loop.second))
        }
        return result;
    }

    /**
     * @brief Removes a row from a 2D vector at the specified index.
     *
     * @tparam T The type of the elements in the 2D vector.
     * @param intput The input 2D vector from which a row will be removed.
     * @param index The zero-based index of the row to remove.
     * @return A new 2D vector with the specified row removed.
     */
    template <typename T>
    ocf::vec<ocf::vec<T>> erase_row(const ocf::vec<ocf::vec<T>> &input, int index)
    {
        if(index > static_cast<int>(v.size()) || index < 0)
            throw std::out_of_range("the vector erase index is begger than the vector size or is equal or less than zero");
        ocf::vec<ocf::vec<T>> result;
        for(iter_less(i, v.size()))
        {
            if(static_cast<int>(i) == index)
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
     * @param input The input 2D vector from which a column will be removed.
     * @param index The zero-based index of the column to remove.
     * @return ocf::vec<ocf::vec<T>> A new 2D vector with the specified column removed from each row.
     *
     * @note If no columns are erased due to incorrect indexing, a message is printed to std::cout.
     */
    template <typename T>
    ocf::vec<ocf::vec<T>> erase_column(const ocf::vec<ocf::vec<T>> &input, size_t index)
    {
        if(input.empty()) return input;
        if(index > input.size()) {
            std::cerr << "Out Of Range indexing" << '\n';
            return input;
        }
        ocf::vec<ocf::vec<T>> result;
        int erase_count = 0;
        for(iter_less(i, v.size()))
        {
            if(static_cast<int>(v[i].size()) < index)
                continue;
            result.push_back({});
            for(iter_less(j, v[i].size()))
            {
                if(static_cast<int>(j) != index)
                    result[i].push_back(v[i][j]);
            }
            erase_count++;
        }
        if(erase_count == 0)
            std::cout << "nothing was erase form the vector due to incorrect indexing" << std::endl;
        return result;
    }

    /**
     * @brief Removes the specified row and column from a 2D vector.
     *
     * This function creates a new 2D vector by removing the row at index `i` and the column at index `j`
     * from the input vector `v`. The original vector is not modified.
     *
     * @tparam T The type of the elements in the 2D vector.
     * @param input The input 2D vector from which a row and a column will be removed.
     * @param i The index of the row to remove.
     * @param j The index of the column to remove.
     * @return A new 2D vector with the specified row and column removed.
     *
     * @note This function depends on the existence of `erase_row` and `erase_column` helper functions.
     */
    template <typename T>
    ocf::vec<ocf::vec<T>> erase_row_column(
        const ocf::vec<ocf::vec<T>> &input, 
        size_t i, size_t j) noexcept
    {
        if(input.empty()) return input;
        if(i > input.empty()) {
            std::cerr << "Out of Range indexing" << '\n';
            return input;
        }
        ocf::vec<ocf::vec<T>> result_v = erase_row<T>(input, i);
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
     * @see ocf::vec, static_cast
     * @example
     * ocf::vec<int> intVec = {1, 2, 3};
     * ocf::vec<double> doubleVec = vector_cast<double>(intVec); // doubleVec will contain {1.0, 2.0, 3.0}
     * ocf::vec<ocf::vec<int>> intVec2D = {{1, 2}, {3, 4}};
     * ocf::vec<ocf::vec<double>> doubleVec2D = vector_cast<double>(intVec2D); // doubleVec2D will contain {{1.0, 2.0}, {3.0, 4.0}}
     */
    template <typename T1, typename T2>
    ocf::vec<T1> vector_cast(const ocf::vec<T2> &input) noexcept
    {
        ocf::vec<T1> result;
        for(iter_less(i, input.size()))
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
     * @see ocf::vec, static_cast
     * @example
     * ocf::vec<ocf::vec<int>> intVec2D = {{1, 2}, {3, 4}};
     * ocf::vec<ocf::vec<double>> doubleVec2D = vector_cast<double>(intVec2D); // doubleVec2D will contain {{1.0, 2.0}, {3.0, 4.0}}
     * ocf::vec<ocf::vec<ocf::vec<int>>> intVec3D = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
     * ocf::vec<ocf::vec<ocf::vec<double>>> doubleVec3D = vector_cast<double>(intVec3D); // doubleVec3D will contain {{{1.0, 2.0}, {3.0, 4.0}}, {{5.0, 6.0}, {7.0, 8.0}}}
     */
    template <typename T1, typename T2>
    ocf::vec<ocf::vec<T1>> vector_cast(const ocf::vec<ocf::vec<T2>> &input) noexcept
    {
        ocf::vec<ocf::vec<T1>> result;
        for(iter_less(i, input.size()))
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
     * @see ocf::vec, static_cast
     * @example
     * ocf::vec<ocf::vec<ocf::vec<int>>> intVec3D = {{{
     * 1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
     * ocf::vec<ocf::vec<ocf::vec<double>>> doubleVec3D = vector_cast<double>(intVec3D); // doubleVec3D will contain {{{1.0, 2.0}, {3.0, 4.0}}, {{5.0, 6.0}, {7.0, 8.0}}}
     */
    template <typename T1, typename T2>
    ocf::vec<ocf::vec<ocf::vec<T1>>> vector_cast(const ocf::vec<ocf::vec<ocf::vec<T2>>> &input) noexcept
    {
        ocf::vec<ocf::vec<ocf::vec<T1>>> result;
        for(iter_less(i, input.size()))
            result.push_back(vector_cast<T1, T2>(input[i]));
        return result;
    }

    /**
     * @brief Finds the index of the first occurrence of an element in a vector within a specified range.
     * This function searches for the element `e` in the vector `v` starting from index `start` and ending at index `end` (exclusive). If the element is found, its index is returned; otherwise, a default value (size_t()) is returned.
     * @param input The vector to search through.
     * @param element The element to find in the vector.
     * @param end The index at which to stop the search (exclusive). If set to 0, the search will go until the end of the vector.
     * @param start The index at which to start the search (inclusive). Default is 0.
     * @return The index of the first occurrence of the element `e` in the vector `v` within the specified range, or size_t() if the element is not found.
     * @tparam T The type of elements in the vector.
     * @note If the vector is empty, the function will return size_t() immediately. The function does not perform bounds checking on the `start` and `end` parameters, so it is the caller's responsibility to ensure they are within valid ranges.
     */
    template <typename T>
    size_t where(const ocf::vec<T> &input, const T &element,
                size_t end = 0, size_t start = 0) noexcept
    {
        if(input.empty())
            return size_t();
        if(end == 0 || end > input.length())
            end = input.length();
        for(iter_in_range(i, start, end, 1))
        {
            if(input[i] == element)
                return i;
        }
        return size_t();
    }

    /**
     * @brief Checks if an element exists in a vector within a specified range.
     * This function searches for the element `e` in the vector `v` starting from index `start` and ending at index `end` (exclusive). It returns true if the element is found within the specified range, and false otherwise.
     * @param input The vector to search through.
     * @param element The element to check for existence in the vector.
     * @param end The index at which to stop the search (exclusive). If set to 0, the search will go until the end of the vector.
     * @param start The index at which to start the search (inclusive). Default is 0.
     * @return true if the element `e` exists in the vector `v` within the specified range, false otherwise.
     * @tparam T The type of elements in the vector.
     * @note If the vector is empty, the function will return false immediately. The function does not perform bounds checking on the `start` and `end` parameters, so it is the caller's responsibility to ensure they are within valid ranges.
     */
    template <typename T>
    bool exist(const ocf::vec<T> &input, const T &element,
            size_t end = 0, size_t start = 0) noexcept
    {
        if(end == 0 || end > input.size())
            end = input.size();
        for(iter_in_range(i, start, end, 1))
        {
            if(input[i] == element)
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
     * @param input The augmented matrix represented as a vector of vectors of
     * doubles. Each row should have n+1 elements for a system of n equations (n
     * variables + 1 constant).
     * @param status Reference to an integer that will be set to indicate the result
     * of the elimination:
     *        - 0: Successful elimination, unique solution found.
     *        - 1: Matrix is singular (no unique solution).
     *        - 2: Infinite solutions exist.
     *        - 3: No solution exists.
     *        - 4: empty matrix
     *
     * @return The matrix in reduced row echelon form after elimination.
     *
     * @throws invalid_argument if the input matrix is empty.
     *
     * @note The input matrix is modified and returned in its transformed state.
     */
    ocf::vec<ocf::vec<double>> gauss_jordan(ocf::vec<ocf::vec<double>> input, size_t &status)
    {
        if(input.empty()) {
            status = 4;
            return input;
        }
        status = 0;
        for(iter_less(i, input.size()))
        {
            if(input[i][i] == 0)
            {
                size_t c = 1;
                while ((i + c) < input.size() && input[i + c][i] == 0)
                    c++;
                if((i + c) == input.size())
                {
                    status = 1;
                    break;
                }
                std::swap(input[i], input[i + c]);
            }
            for(iter_less(j, input.size()))
            {
                if(i != j)
                {
                    double pro = input[j][i] / input[i][i];
                    for(size_t k = 0; k <= input.size(); k++)
                        input[j][k] -= input[i][k] * pro;
                }
            }
        }
        if(status == 1)
        {
            status = 3;
            for(iter_less(i, input.size()))
            {
                double sum = 0;
                for(iter_less(j, input.size()))
                    sum += input[i][j];
                if(sum == input[i][input.size()])
                    status = 2;
            }
        }
        return input;
    }

    /**
     * @brief Generates a string consisting of a specified number of newline characters.
     * @param input The number of newline characters to include in the resulting string. Defaults to 1 if not provided.
     * @return A ocf::str object containing n newline characters ('\n'). If n is 0, an empty string is returned.
     * @note The function is marked as noexcept, indicating that it guarantees not to throw exceptions
     */
    const ocf::str& new_lines(size_t input = 1) noexcept
    {
        ocf::str result;
        for(iter_less(i, input))
            result += '\n';
        return result;
    }

    /**
     * @brief Generates a string consisting of a specified number of tab characters.
     * @param input The number of tab characters to include in the resulting string. Defaults to 1 if not provided.
     * @return A ocf::str object containing n tab characters ('\t'). If n is 0, an empty string is returned.
     * @note The function is marked as noexcept, indicating that it guarantees not to throw exceptions
     */
    const ocf::str& Tabs(size_t input = 1) noexcept
    {
        ocf::str result;
        for(iter_less(i, input))
            result += '\t';
        return result;
    }

    /**
     * @brief Calculates the index of the last character in a string.
     *
     * This function returns the zero-based index of the final character in the string input.
     * If the string is empty, it returns a value that typically signifies an error or invalid index, which is 0 cast to size_t.
     *
     * @note The return type is size_t, which is an unsigned integer.
     *       Returning 0 will result in the maximum possible value for size_t due to the implicit conversion from signed to unsigned.
     *
     * @param input The input string to check.
     *              Passed as a constant reference for efficiency.
     * @return The index of the last character (which is input.size() - 1) if the string is not empty.
     *         Returns 0 (converted to the maximum size_t value) if the string is empty.
     */
    size_t last_index(const ocf::str &input) noexcept
    {
        return input.empty() ? 0 : input.size() - 1;
    }

    /**
     * @brief Retrieves the last character of a given string.
     *
     * This function safely attempts to return the last character in the string input.
     * It uses the index returned by last_index(input) to access the character.
     *
     * @note If the string input is empty, the function returns the null character ('\\0') as a conventional indicator for an empty or invalid result.
     *
     * @param input The input string to read the last element from.
     *              Passed as a constant reference for efficiency.
     * 
     * @return The last character of the string input.
     *         Returns the null character ('\\0') if the string is empty.
     */
    char last_element(const ocf::str &input) noexcept
    {
        return input.empty() ? '\0' : input[last_index(input)];
    }

    /**
     * @brief Removes a single character from a string at a specified index.
     *
     * This function creates and returns a new string that is identical to the input string input, but with the character at the given index removed.
     * The original string input remains unchanged.
     *
     * @param input The input string from which the character will be removed.
     *              Passed by constant reference for efficiency.
     * @param index The zero-based index of the character to be removed from the string.
     *
     * @return A new ocf::str object containing all characters of input except the one at the specified index.
     * 
     * @note The function implements character removal by iterating over the input string and skipping the character at the specified index.
     */
    ocf::str remove(const ocf::str &input, size_t index) noexcept
    {
        if(index >= input.size()) {
            std::cerr << "out of range indexing" << '\n';
            return input;
        }
        ocf::str result;
        for(iter_less(i, input.size()))
        {
            if(i != index)
                result += input[i];
        }
        return result;
    }

    /**
     * @brief Removes all occurrences of a specific character from a string.
     *
     * This function iterates through the input string s and builds a new
     * string containing only the characters that are not equal to the specified
     * character c.
     *
     * @note The function guarantees not to throw exceptions (noexcept).
     *       If the input string is empty, an empty string is returned.
     *       If the character to remove is not found, a copy of the original string is returned.
     *
     * @param input The input string to process.
     *              Passed by constant reference.
     * @param rmch  The character whose occurrences should be removed from the string.
     *
     * @return A new ocf::str object that is a copy of s with all
     *         instances of character c removed.
     */
    ocf::str& remove(const ocf::str &input, char rmch) noexcept
    {
        ocf::str result;
        for(char lc : input)
        {
            if(lc != rmch)
                result += lc;
        }
        return result;
    }

    /**
     * @brief Removes characters from a string based on a custom predicate function.
     *
     * This is a highly flexible removal function that filters the input string
     * input.
     * It keeps only the characters for which the provided predicate function filter returns false.
     *
     * @details    The predicate f is a function (e.g., a lambda, function pointer, or function object) that takes a character and returns a boolean.
     *             If filter(c) returns true, the character c is removed from the result.
     *             This allows for complex filtering logic (e.g., removing all vowels, all digits, or all whitespace).
     *
     * @note       The function guarantees not to throw exceptions (noexcept).
     *             If the string s is empty, an empty string is returned.
     *
     * @param input The input string to filter.
     *              Passed by constant reference.
     * @param filter A ocf::func object (predicate) that takes a char and returns bool.
     *               The character is removed if this function returns true.
     *
     * @return A new ocf::str object containing only the characters from input
     *         that did not satisfy the predicate filter (i.e., for which filter(c) was false).
     */
    ocf::str& remove(const ocf::str &input, ocf::func<bool(char)> filter) noexcept
    {
        ocf::str result;
        for(char c : input)
        {
            if(!filter(c))
                result += c;
        }
        return result;
    }

    /**
     * @brief Extracts a substring from an input string between two specified indices.
     *
     * This function creates and returns a new string that contains the characters
     * from the input string input, starting at start and ending at
     * end, inclusive.
     *
     * @param input The input string from which the substring will be extracted.
     *              Passed by constant reference for efficiency.
     * @param start The zero-based index of the first character to include in the substring (inclusive).
     * @param end   The zero-based index of the last character to include in the substring (inclusive).
     *
     * @return A new ocf::str object representing the desired substring.
     *         Returns an empty string if start equals end.
     *
     * @note Unlike many standard library functions, this function treats the end as **inclusive**.
     */
    ocf::str sub_str(const ocf::str &input, size_t start, size_t end)
    {
        if(start >= input.size() || end >= input.size()) return input;
        if(start > end) return input;
        if(start == end) return ocf::str("");
        ocf::str result;
        for(iter_in_range(i, start, end, 1))
            result += input[i];
        return result;
    }

    /**
     * @brief       Removes the first occurrence of a specific substring from a string.
     *
     * This function searches for the first instance of the substring input2 within
     * the string input1 and returns a new string with that single instance removed.
     * It is designed to remove a segment (the first match of input2), not just
     * individual characters.
     *
     * @param input1 The primary string from which the removal will take place.
     *               Passed by constant reference.
     * @param input2 The substring to be located and removed. Passed by constant reference.
     *
     * @return       A new ocf::str object:
     *               - If input2 is empty, it returns input1 unchanged.
     *               - If input2 is not found in input1, it returns input1 unchanged.
     *               - Otherwise, it returns input1 with the first occurrence of input2 removed.
     *
     * @note         The implementation uses ocf::str::find() to locate the
     *               substring and ocf::str::append() to efficiently construct
     *               the result without the removed segment.
     */
    ocf::str remove(const ocf::str &input1, const ocf::str &input2) noexcept
    {
        if(input2.empty())
            return input1;
        if(input2.size() > input1.size())
            return input2;
        size_t pos = input1.find(input2);
        if(pos == ocf::str::npos)
            return input1;
        ocf::str result;
        result.reserve(input1.size() - input2.size());
        result.append(input1, 0, pos);
        result.append(input1, pos + input2.size(), ocf::str::npos);
        return result;
    }

    /**
     * @brief       Reverses the order of characters in a string.
     *
     * This function creates a new string that contains all characters of the
     * input string s in reverse order. It iterates from the last character
     * to the first character to construct the reversed string.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the input string s is empty, an empty string is returned.
     *             It is assumed that last_index(s) returns a value suitable
     *             for iterating backward using an int loop counter.
     *
     * @param input The input string to be reversed. Passed by constant reference
     *             for efficiency.
     *
     * @return     A new ocf::str object which is the reverse of the input string s.
     */
    ocf::str reverse(const ocf::str &input) noexcept
    {
        if(input.empty())
            return input;
        ocf::str result;
        for(iter_high(i, input.length()))
            result += input[i - 1];
        return result;
    }

    /**
     * @brief       Inserts a single character into a string at a specified index.
     *
     * This function creates and returns a new string where the given character
     * value is inserted *before* the character currently at index in the
     * input string s.
     *
     * @details     The insertion happens at the position specified by index.
     *             Note that the implementation iterates through the original string
     *             and places the value character immediately before the character
     *             that was originally at the given index.
     *
     * @param input The base string into which the character will be inserted.
     *              Passed by constant reference.
     * @param value The character to be inserted.
     * @param index The zero-based index at which the character should be inserted.
     *             This index must be a valid position within the current string
     *             (i.e., 0 <= index < s.size()).
     *
     * @return     A new ocf::str object with the character value inserted.
     */
    ocf::str insert(const ocf::str &input, char value, size_t index)
    {
        if(index >= input.size())
            return input;
        ocf::str result;
        for(iter_less(i, input.size()))
        {
            if(i == index)
            {
                result += value;
                result += input[i];
            }
            else
                result += input[i];
        }
        return result;
    }

    /**
     * @brief       Swaps the characters at two specified indices in a string.
     *
     * This function creates and returns a new string based on the input string s,
     * where the characters at first index and second index have been exchanged.
     * The original string s remains unmodified.
     *
     * @param s      The input string whose characters are to be swapped.
     *              Passed by constant reference for efficiency.
     * @param first  The zero-based index of the first character to be involved
     *              in the swap operation.
     * @param second The zero-based index of the second character to be involved
     *              in the swap operation.
     *
     * @return       A new ocf::str object with the characters at first
     *               and second indices swapped.
     *
     * @throws       std::out_of_range     If either first or second index is
     *                                     less than 0 or is greater than or equal to
     *                                     the size of the string s.
     * @throws       std::invalid_argument If the first and second indices are
     *                                     identical, as no swap is necessary.
     */
    ocf::str swap(const ocf::str &s, size_t first, size_t second)
    {
        if(first < 0 || second < 0 || second >= s.size() || second >= s.size())
            throw std::out_of_range("the first or secend is bigger or less than zero");
        if(first == second)
            throw std::invalid_argument("can not swap in the same index for first and second");
        ocf::str result;
        for(iter_less(i, s.length()))
        {
            if(i == first)
                result += s[second];
            else if(i == second)
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
     * character removed within the input string s is substituted with the
     * character inserted.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the character to be removed is the same as the character to be
     *             inserted, the original string s is returned directly without
     *             performing any modification (and without unnecessary copying).
     *
     * @param s        The input string to be processed. Passed by constant reference.
     * @param removed  The character to be found and replaced within the string.
     * @param inserted The new character that will substitute all instances of removed.
     *
     * @return       A new ocf::str object with all occurrences of removed
     *               replaced by inserted. Returns s if removed and inserted are the same.
     */
    ocf::str replace(const ocf::str &s, char removed, char inserted) noexcept
    {
        if(removed == inserted)
            return s;
        ocf::str result;
        for(char c : s)
        {
            if(c == removed)
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
     * of the input string s is converted to its uppercase equivalent. The
     * remaining characters of the string are preserved unchanged.
     *
     * @details     The capitalization is performed only if the first character
     *             is determined to be lowercase using std::islower(). The
     *             conversion is done arithmetically by subtracting the difference
     *             in ASCII/EBCDIC values between a lowercase and an uppercase letter
     *             (equivalent to subtracting ' ').
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the input string s is empty, an empty string is returned.
     *
     * @param s     The input string to be capitalized. Passed by constant reference.
     *
     * @return     A new ocf::str object with its first character capitalized.
     *             Returns the original string if it is empty or if the first character
     *             is already uppercase or non-alphabetic.
     */
    ocf::str capitalize(const ocf::str &s) noexcept
    {
        if(s.empty())
            return s;
        ocf::str result;
        if(std::islower(s[0]))
            result += (s[0] - ' ');
        else
            result += s[0];
        for(size_t i = 1; i < s.size(); i++)
            result += s[i];
        return result;
    }

    /**
     * @brief       Converts an entire string to either lowercase or uppercase.
     *
     * This function iterates through the input string s and converts all
     * alphabetic characters based on the value of the to_lower flag.
     *
     * @details     The conversion relies on the difference between the ASCII values
     *             of lowercase and uppercase letters (the difference is equivalent
     *             to the space character ' ').
     *
     * @note       The function is marked as noexcept, yet the implementation
     *             includes error handling logic that returns a **string literal error
     *             message** ("convert error: wrong input form") if any character
     *             is neither lowercase nor uppercase. Users should be aware of this
     *             specific error signaling method.
     *
     * @param s        The input string to be converted. Passed by constant reference.
     * @param to_lower If true, all uppercase letters are converted to lowercase.
     *                 If false, all lowercase letters are converted to uppercase.
     *
     * @return       A new ocf::str object:
     *               - The converted string if all characters are alphabetic.
     *               - The original string if it is empty.
     *               - The string literal "convert error: wrong input form" if a
     *                 non-alphabetic character is encountered.
     */
    ocf::str convert(const ocf::str &s, bool to_lower) noexcept
    {
        if(s.empty())
            return s;
        ocf::str result;
        if(to_lower)
        {
            for(char c : s)
            {
                if(std::islower(c))
                    result += c;
                else if(std::isupper(c))
                    result += (c + ' ');
                else
                    return "convert error: wrong input form";
            }
        }
        else
        {
            for(char c : s)
            {
                if(std::islower(c))
                    result += (c - ' ');
                else if(std::isupper(c))
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
     * This function converts the input string s into a standard format where
     * the first letter is capitalized and all subsequent letters are lowercase.
     * This is achieved by first converting the entire string to lowercase and
     * then capitalizing the first character.
     *
     * @details     The logic relies on two other assumed functions:
     *             1. convert(s, true): Converts the entire string to lowercase.
     *             2. capitalize(s): Capitalizes only the first character.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the string s is empty, an empty string is returned.
     *             Note that the output of this function depends entirely on the
     *             correctness and error handling of the underlying convert and
     *             capitalize implementations.
     *
     * @param s     The input string to be standardized. Passed by constant reference.
     *
     * @return     A new ocf::str object formatted as a standard word (Title Case).
     */
    ocf::str standard_word(const ocf::str &s) noexcept
    {
        if(s.empty())
            return s;
        ocf::str result = convert(s, true);
        return capitalize(result);
    }

    /**
     * @brief       Splits a string into a vector of substrings based on space delimiters.
     *
     * This function processes the input string s and separates it into individual
     * "words" using the space character (' ') as a delimiter. It returns these
     * substrings in a vector.
     *
     * @details     The implementation iterates through the string, building up a
     *             temporary string (@c temp) until a space or the end of the string
     *             is reached. When a delimiter is found, the accumulated word is
     *             added to the result vector.
     * * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the input string s is empty, an empty vector is returned.
     *             **Important:** The current implementation might produce empty strings
     *             in the result vector if multiple spaces are adjacent (e.g., "word  two").
     *             It is also crucial to note that accessing s[i] when i == s.size()
     *             for the end-of-loop check is **undefined behavior** in standard C++,
     *             even though it's used here to process the last word.
     *
     * @param s     The input string to be separated. Passed by constant reference.
     *
     * @return     A ocf::vec<ocf::str> containing the separated substrings.
     *             Returns an empty vector if the input string is empty.
     */
    ocf::vec<ocf::str> split(const ocf::str &s, char c = ' ') noexcept
    {
        if(s.empty())
            return {};
        ocf::vec<ocf::str> result;
        ocf::str temp;
        for(iter_less(i, s.length()))
        {
            if(s[i] == c || i == s.size() - 1)
            {
                result.push_back(temp);
                temp.clear();
            }
            else
                temp += s[i];
        }
        return result;
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
    bool exist(const ocf::str &s, char c,
            size_t end = 0, size_t start = 0) noexcept
    {
        if(end == 0)
            end = s.length();
        for(iter_in_range(i, start, end, 1))
        {
            if(s[i] == c)
                return true;
        }
        return false;
    }

    /**
     * @brief Checks if a specific substring exists within another string.
     * @param input1 The string to search within, passed by constant reference.
     * @param input2 The substring to search for, passed by constant reference.
     * @return Returns true if the substring input2 is found within the string input1; otherwise, returns false. The function compares the characters of input1 and input2 to determine if input2 is a contiguous sequence within input1.
     * @note The function is marked as noexcept, indicating that it guarantees not to throw exceptions. The implementation iterates through the characters of input1 and checks for a sequence that matches input2. If a matching sequence is found, the function returns true; if the end of input1 is reached without finding input2, it returns false.
     */
    bool exist(const ocf::str &input1, const ocf::str &input2) noexcept
    {
        size_t ll = size_t(), il = size_t();
        // ll: loop length, il: if length
        if(input1.length() > input2.length())
        {
            ll = input1.length();
            il = input2.length();
        }
        else
        {
            ll = input2.length();
            il = input1.length();
        }
        bool seq = bool();
        size_t j = 0;
        for(iter_less(i, ll))
        {
            if(seq && input1[i] == input2[j])
            {
                j++;
            }
            else if(seq && input1[i] != input2[j])
            {
                seq = false;
                j = 0;
            }
            else if(input1[i] == input2[j])
            {
                seq = true;
                j++;
            }
            if(seq && j == il - 1)
                return true;
        }
        return false;
    }

    /**
     * @brief Finds the starting and ending indices of a substring within another string.
     * @param input1 The string to search within, passed by constant reference.
     * @param input2 The substring to search for, passed by constant reference.
     * @return A pair of indices (start, end) indicating the position of the substring input2 within input1. If input2 is not found, both indices will be 0.
     * @note The function is marked as noexcept, indicating that it guarantees not to throw exceptions. The implementation iterates through the characters of input1 and checks for a sequence that matches input2. If a matching sequence is found, the function returns the indices; if the end of input1 is reached without finding input2, it returns a pair of zeros.
     */
    std::pair<size_t, size_t> where(const ocf::str &input1, const ocf::str &input2)
    {
        size_t ll = size_t(), cl = size_t();
        if(input1.length() > input2.length())
        {
            ll = input1.length();
            cl = input2.length();
        }
        else if(input2.length() == input1.length())
        {
            ll = input1.length();
            cl = ll;
        }
        else
        {
            ll = input2.length();
            cl = input1.length();
        }
        std::pair<size_t, size_t> result;
        bool sequence = bool();
        size_t j = 0;
        for(iter_less(i, ll))
        {
            if(input1[i] == input2[j] && sequence)
            {
                j++;
            }
            else if(input1[i] == input2[j])
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
            if(j == cl - 1 && sequence)
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
    ocf::vec<size_t> where(const ocf::str &s, char c,
                            size_t end = 0, size_t start = 0)
    {
        ocf::vec<size_t> result;
        if(end == 0)
            end = s.length();
        for(iter_in_range(i, start, end, 1))
        {
            if(c == s[i])
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
    size_t where_first(const ocf::str &s, char c,
                    size_t end = 0, size_t start = 0) noexcept
    {
        if(s.empty())
            return 0;
        if(end == 0)
            end = s.length();
        for(iter_in_range(i, start, end, 1))
        {
            if(s[i] == c)
                return i;
        }
        std::cerr << "The char: " << c << " don't exist.\n";
        return 0;
    }

    /**
     * @brief       Converts a string sentence or phrase into a standard Title Case format.
     *
     * This function formats the input string s such that every word begins with
     * an uppercase letter, and the remaining letters are lowercase (e.g., "this is a test"
     * becomes "This Is A Test").
     *
     * @details     The process involves three main steps using previously defined functions:
     *             1. **Splitting:** The string s is divided into a vector of words
     *                 using sseparator(s).
     *             2. **Word Standardization:** Each individual word is formatted using
     *                 standard_word(), which capitalizes the first letter and lowercases the rest.
     *             3. **Reassembly:** The standardized words are joined back together
     *                 using a single space delimiter.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the input string s is empty, an empty string is returned.
     *             The behavior is directly dependent on the error handling and functionality
     *             of sseparator and standard_word.
     *
     * @param s     The input string (sentence or phrase) to be formatted.
     *             Passed by constant reference.
     *
     * @return     A new ocf::str object formatted in Title Case.
     */
    ocf::str standard_form(const ocf::str &s) noexcept
    {
        if(s.empty())
            return s;
        ocf::vec<ocf::str> vs = split(s);
        ocf::str result;
        for(iter_less(i, vs.size()))
        {
            result += standard_word(vs[i]);
            if(i != vs.size() - 1)
                result += ' ';
        }
        return result;
    }

    /**
     * @brief       Calculates the sum of the numerical values (ASCII/Character Codes)
     *             of all characters in a string.
     *
     * This function iterates through the input string s and adds the integer
     * value (character code) of each character to a running total. It also
     * incorporates an optional starting value.
     *
     * @details     The final sum is of type long long to prevent potential
     *             overflow, especially for long strings where the cumulative sum
     *             of character codes (which can be up to 255 for an unsigned char)
     *             may exceed the capacity of a standard int.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the string s is empty, the result is simply the value of
     *             the start parameter.
     *
     * @param s         The input string whose characters' codes are to be summed.
     *                 Passed by constant reference.
     * @param start     An optional integer value to start the summation from.
     *                 Defaults to 0.
     *
     * @return       A long long representing the sum of the initial start value
     *               and the character code values of all characters in s.
     */
    size_t sum_chars(const ocf::str &s, size_t start = 0) noexcept
    {
        if(s.empty())
            return 0;
        size_t result = start;
        for(char c : s)
            result += static_cast<size_t>(c);
        return result;
    }

    /**
     * @brief       Calculates the product of the numerical values (ASCII/Character Codes)
     *             of all characters in a string.
     *
     * This function iterates through the input string s and multiplies the integer
     * value (character code) of each character by a running product. It incorporates
     * an optional starting value.
     *
     * @details     The final product is of type long long to prevent integer
     *             overflow, as the multiplication of many character codes (which can be
     *             up to 255 for an unsigned char) quickly exceeds the capacity of
     *             standard 32-bit integer types.
     *
     * @note       The function guarantees not to throw exceptions (@c noexcept).
     *             If the string s is empty, the function returns **0**, which is
     *             an unusual result for a product based on a start value of 1;
     *             typically, it would return start. However, the documentation
     *             reflects the explicit implementation returning 0 for an empty string.
     *
     * @param s         The input string whose characters' codes are to be multiplied.
     *                 Passed by constant reference.
     * @param start     An optional integer value to start the multiplication from.
     *                 Defaults to 1.
     *
     * @return       A long long representing the product of the initial start value
     *               and the character code values of all characters in s. Returns 0
     *               if the string is empty.
     */
    size_t mult_chars(const ocf::str &s, size_t start = 1) noexcept
    {
        if(s.empty())
            return 0;
        size_t result = start;
        for(char c : s)
            result *= static_cast<size_t>(c);
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
     *             It uses std::cout to display the output, converting the
     *             char to an int to display its numerical code.
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
    inline void ascii_table() noexcept
    {
        for(char c = ' '; c <= '~'; c++)
        {
            if(c == ' ')
                std::cout << "[SPACE] = " << static_cast<int>(c) << std::endl;
            else
                std::cout << c << " = " << static_cast<int>(c) << std::endl;
        }
    }

    size_t ascii_sum() noexcept { return 7505; }

    char shift_char(char c, int8_t shift) noexcept { return static_cast<char>(c + shift); }

    /// @brief Shifts each character in a string by a specified amount.
    /// @param input The input string whose characters will be shifted.
    /// @param shift The number of positions to shift each character. Positive values shift forward,
    ///              negative values shift backward.
    /// @return A new string with each character shifted by the specified amount.
    /// @note This function does not throw exceptions (noexcept).
    /// @see shift_char
    ocf::str& shift_string(const ocf::str &input, int shift) noexcept
    {
        ocf::str result;
        for(char c : input)
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
     * @see shift_char(char, int8_t)
     */
    ocf::str& unshift_string(const ocf::str &input, int8_t shift) noexcept
    {
        ocf::str result;
        for(char c : input)
            result += shift_char(c, -shift);
        return result;
    }

    inline char to_lower(char input) noexcept { return (char)std::tolower(input); }

    inline char to_upper(char input) noexcept { return (char)std::toupper(input); }

    inline ocf::str& to_lower(const ocf::str &s) noexcept
    {
        ocf::str result;
        for(char c : s) {
            result += (char)std::tolower(c);
        }
        return result;
    }

    inline ocf::str& to_upper(const ocf::str &s) noexcept {
        ocf::str result;
        for(char c : s) {
            result += (char)std::toupper(c);
        }
        return result;
    }

    inline bool is_digit(char input, char numSystem = 'd') noexcept {
        if(to_lower(numSystem) == 'd') { // decimal
            return input <= '9' && input >= '0';
        } else if(to_lower(numSystem) == 'o') { // octal
            return input <= '7' && input >= '0';
        } else if(to_lower(numSystem) == 'b') { // binary
            return input == '1' || input == '0';
        } else if(to_lower(numSystem) == 't') { // ternary
            return input == '2' || 
                    input == '1' || 
                    input == '0';
        } else if(to_lower(numSystem) == 'h') { // hexdecimal
            return input <= '9' && input >= '0' || 
                    to_lower(input) <= 'f' && 
                    to_lower(input) >= 'a';
        } else {
            std::cerr << "unknown numbering system";
            return false;
        }
    }

    inline bool is_valid_int(const ocf::str& input, char numSystem = 'd') {
        if(input.empty()) return false;
        for(char c : input) {
            if(!is_digit(c, numSystem)) return false;
        }
        return true;
    }

    inline bool is_valid_float(const ocf::str& input, char numSystem = 'd') noexcept {
        if(input.empty()) return false;
        if((input.length() == 1 && input[0] == '.') || 
            input[0] == '.') return false;
        bool fpoint = false;
        for(char c : input) {
            if(c == '.' && fpoint) return false;
            else if(c == '.') fpoint = true;
            else if(!is_digit(c, numSystem)) return false;
        }
        return true;
    }
}
#endif // ETL___FUNCTION_HPP