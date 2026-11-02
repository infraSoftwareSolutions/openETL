/**
 * @file io.hpp
 * @brief A simple I/O utility class for handling standard input and output operations.
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 * @details This library provides a simple I/O utility class for handling standard input and output operations.
 * The `io` class encapsulates various functions for printing to the console, taking user input, and formatting output.
 * It includes methods for printing values with or without newLines, printing error messages, and taking user input for different types of variables and vectors.
 * Additionally, it offers functions for printing formatted test outputs and separators for better readability.
 * Overall, this library is designed to simplify common I/O tasks in C++ and enhance the user experience when interacting with the console.
 * - newLines: Prints a specified number of newline characters.
 * - println: Prints a value followed by a newline to standard output.
 * - print: Prints a value without a newline to standard output.
 * - println_error: Prints an error message followed by a newline to standard error.
 * - print_error: Prints an error message without a newline to standard error.
 * - input: Prints a prompt message and takes user input of the same type.
 * - input (overload): Prints a prompt message and takes user input of a different type.
 * - inputinputtor: Prints a prompt message and takes user input for a vector of a different type.
 * - inputinputtor_2d: Prompts the user for input to fill a 2D vector.
 * - inputinputtor_3d: Prompts the user for input to fill a 3D vector.
 * - Tabs: Prints a specified number of tab characters.
 * - print_test: Prints a standardized test output with optional vector content.
 * - print (vector overload): Prints all elements in a vector with formatting.
 * - print (2D vector overload): Prints a 2D vector to the standard output in a formatted manner.
 * - print (3D vector overload): Prints a 3D vector to the standard output in a formatted manner.
 * - println (2D vector overload): Prints a 2D vector to the standard output in a formatted manner.
 * - println (3D vector overload): Prints a 3D vector to the standard output in a formatted manner.
 * @note This library is designed for C++23 and is part of the metaCore library, specifically within the CXXLite module, and is intended for simplifying I/O operations in C++.
 */

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <climits>
#include <stdexcept>

#include "cfrost/structure.h"
#include "cfrost/types.h"


#pragma once
#ifndef ETL___IO_HPP
#define ETL___IO_HPP

namespace etl {
    namespace io
    {

        /**
         * @brief Prints a number of newline characters.
         * @param num Number of new lines to print (default = 2).
         */
        inline void newLines(size_t num = 1) noexcept
        {
            for(iter_less(i, num))
                std::cout << '\n';
        }

        /**
         * @brief Prints a horizontal line using a specific character.
         * @param length The number of characters in the line.
         * @param ch The character to use (must be one of: ~, -, #, *, =).
         */
        inline void separator(size_t length, char ch = '-') noexcept
        {
            for(iter_less(i, length))
                std::cout << ch;
            std::cout << '\n';
        }

        /**
         * @brief Prints multiple separator lines.
         * @param numsep The number of separator lines to print.
         * @param length The number of characters in each separator line.
         * @param ch The character to use for the separator lines (must be one of: ~, -, #, *, =).
         * @details This function prints a specified number of separator lines, each consisting of a specific character repeated a certain number of times. The character used for the separator lines must be one of the following: ~, -, #, *, =. If an invalid character is provided, an exception is thrown.
         */
        inline void separators(size_t numsep, size_t length, char ch) noexcept
        {
            for (iter_less(i, numsep))
                separator(length, ch);
        }

        /**
         * @brief Prints a value followed by a newline to standard output.
         * @tparam T Type of the value to print.
         * @param output The value to be printed.
         */
        void println() noexcept { std::cout << '\n'; }
        template <typename T, typename... Args>
        void println(const T &output, Args... remaining_t) noexcept
        {
            std::cout << output;
            println(remaining_t...);
        }

        /**
         * @brief Prints a value without a newline to standard output.
         * @tparam T Type of the value to print.
         * @param output The value to be printed.
         */
        void print() noexcept { return; }
        template <typename T, typename... Args>
        void print(const T &output, Args... remaining_t) noexcept
        {
            std::cout << output;
            print(remaining_t...);
        }

        /**
         * @brief Prints an error message followed by a newline to standard error.
         * @tparam T Type of the message to print.
         * @param output The error message to be printed.
         */
        void println_error() noexcept { std::cerr << '\n'; }
        template <typename T, typename... Args>
        void println_error(const T &output, Args... remaining_t) noexcept
        {
            std::cerr << output;
            println_error(remaining_t...);
        }

        /**
         * @brief Prints an error message without a newline to standard error.
         * @tparam T Type of the message to print.
         * @param output The error message to be printed.
         */
        void print_error() noexcept { return; }
        template <typename T, typename... Args>
        void print_error(const T &output, Args... remaining_t) noexcept
        {
            std::cerr << output;
            print_error(remaining_t...);
        }

        /**
         * @brief Prints a prompt message and takes user input of a different type.
         * @tparam T Type of the input variable.
         * @param output The prompt message to display.
         * @return T The user input.
         */
        template <typename T>
        inline T input(const ocf::str &output)
        {
            T var;
            std::cout << output;
            std::cin >> var;
            return var;
        }

        /**
         * @brief Prints a prompt message and takes user input for a vector of a different type.
         * @tparam T Type of the input variable.
         * @param output The prompt message to display.
         * @param size The number of elements in the vector.
         * @return ocf::vec<T> The user input vector.
         */
        template <typename T>
        ocf::vec<T>& input(const ocf::str &output, size_t size)
        {
            ocf::vec<T> input;
            T var;
            std::cout << output << " {";
            for (size_t i = 0; i < size; i++)
            {
                std::cin >> var;
                input.push_back(var);
                if(i == size - 1) std::cout << "}\n";
                else std::cout << ", ";
            }
            return input;
        }

        /**
         * @brief Prompts the user for input to fill a 2D vector.
         * @tparam T The type of elements in the 2D vector.
         * @param output The prompt message to display.
         * @param rows The number of rows (must be > 0).
         * @param cols The number of columns (must be > 0).
         * @return A 2D vector filled with user input.
         * @throws std::invalid_argument if rows or cols is less than or equal to zero
         */
        template <typename T>
        ocf::vec<ocf::vec<T>> input_2d(const ocf::str &output, size_t rows, size_t cols)
        {
            ocf::vec<ocf::vec<T>> vec2d;
            T var;
            std::cout << output << "{\n";
            for (size_t i = 0; i < rows; i++)
            {
                ocf::vec<T> row;
                for (size_t j = 0; j < cols; j++)
                {
                    if(j == 0) std::cout << "\t{";
                    std::cin >> var;
                    row.push_back(var);
                    if(j == cols - 1) std::cout << "},\n"
                    else std::cout ", ";
                }
                vec2d.push_back(row);
                if(i == rows - 1) std::cout << "}\n"
            }
            return vec2d;
        }

        /**
         * @brief Prompts the user for input to fill a 3D vector.
         * @tparam T The type of elements in the 3D vector.
         * @param output The prompt message to display.
         * @param x The size of the first dimension (must be > 0).
         * @param y The size of the second dimension (must be > 0).
         * @param z The size of the third dimension (must be > 0).
         * @return A 3D vector filled with user input.
         * @throws std::invalid_argument if any dimension is less than or equal to zero.
         */
        template <typename T>
        ocf::vec<ocf::vec<ocf::vec<T>>> input_3d(const ocf::str &output, size_t x, size_t y, size_t z)
        {
            ocf::vec<ocf::vec<ocf::vec<T>>> vec3d;
            T var;
            std::cout << output << "{\n";
            for (size_t i = 0; i < x; i++)
            {
                ocf::vec<ocf::vec<T>> layer;
                for (size_t j = 0; j < y; j++)
                {
                    if(j == 0) std::cout << "\t{\n";
                    ocf::vec<T> row;
                    for (size_t k = 0; k < z; k++)
                    {
                        if(k == 0) std::cout << "\t\t{";
                        std::cin >> var;
                        row.push_back(var);
                        if(k == z - 1) std::cout << "},\n";
                        else std::cout << ", ";
                    }
                    layer.push_back(row);
                    if(j == y - 1) "\t},\n";
                }
                vec3d.push_back(layer);
                if(i == x - 1) std::cout << "}\n";
            }
            return vec3d;
        }

        /**
         * @brief Prints a number of tab characters.
         * @param num Number of tabs to print (default = 2).
         */
        inline void tabs(size_t num = 1) noexcept
        {
            for (iter_less(i, num))
                std::cout << '\t';
        }

        /**
         * @brief Prints a standardized test output.
         * @tparam T The type of the output value.
         * @param testNum The test number.
         * @param OutPut The output value to print.
         */
        template <typename T>
        inline void print_test(size_t testNum, const T &OutPut) noexcept
        {
            std::cout << "Test("
            << testNum << "): " 
            << OutPut << '\n';
        }

        /**
         * @brief Prints a standardized test output without a specific value.
         * @param testNum The test number.
         */
        inline void print_test(size_t testNum) noexcept
        {
            std::cout << "Test(" 
            << testNum << "): " 
            << '\n';
        }

        void print_test(const ocf::str& name,
            const ocf::str& description,
            bool result, size_t testNum,
            size_t whiteSpace = 2,
            size_t seplen = 25,
            size_t sepch = '-') noexcept {
            newLines(whiteSpace);
            separator(seplen, sepch);
            println("<<< TEST >>>");
            separator(seplen, sepch);
            if(name.length() != 0) {
                println("NAME: ", name);
            }
            if(description.length() != 0) {
                println("DESCRIPTION: ", description);
            }
            println("NUMBER: ", testNum);
            println("RESULT: ", result ? "PASSED" : "FAILED");
            separator(seplen, sepch);
        }

        /**
         * @brief Prints all elements in a vector with formatting.
         * @tparam T The type of vector elements.
         * @param input The vector to print.
         */
        template <typename T>
        void print(const ocf::vec<T> &input) noexcept
        {
            if (input.empty())
                std::cout << "[]";
            if (input.size() == 1)
            {
                std::cout << " [" << input[0] << "] ";
                return;
            }
            for (iter_less(i, input.size()))
            {
                if (i == 0)
                    std::cout << " [" << input[i] << ", ";
                else if (i == input.size() - 1)
                    std::cout << input[i] << "] ";
                else
                    std::cout << input[i] << ", ";
            }
        }

        /**
         * @brief Prints the contents of a vec to the standard output in a formatted manner.
         *
         * This function outputs the elements of the given vector enclosed in square brackets and separated by commas.
         * If the vector is empty, it prints "[]".
         *
         * @tparam T The type of the elements stored in the vector.
         * @param output The vector whose contents are to be printed.
         * @note The function is marked noexcept and does not throw exceptions.
         */
        template <typename T>
        void println(const ocf::vec<T> &output) noexcept
        {
            if (output.empty())
            {
                std::cout << "[]" << '\n';
                return;
            }
            std::cout << "[";
            for (iter_less(i, output.size()))
            {
                std::cout << output[i];
                if (i != output.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "]" << '\n';
        }

        /**
         * @brief Prints a 2D vector to the standard output in a formatted manner.
         *
         * This function outputs the contents of a two-dimensional vec to std::cout,
         * formatting it as nested lists (e.g., [[1, 2], [3, 4]]). If the input vector is empty,
         * it prints "[]".
         *
         * @tparam T The type of the elements stored in the inner vectors.
         * @param output The 2D vector to be printed.
         */
        template <typename T>
        void print(const ocf::vec<ocf::vec<T>> &output) noexcept
        {
            if (output.empty())
            {
                std::cout << "[]";
                return;
            }
            std::cout << "[";
            for (iter_less(i, output.size()))
            {
                std::cout << "[";
                for (iter_less(j, output[i].size()))
                {
                    std::cout << output[i][j];
                    if (j != output[i].size() - 1)
                        std::cout << ", ";
                }
                std::cout << "]";
                if (i != output.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "]";
        }

        /**
         * @brief Prints a 2D vector to the standard output in a formatted manner.
         *
         * This function outputs the contents of a two-dimensional vec to std::cout,
         * formatting it as nested lists (e.g., [[1, 2], [3, 4]]). If the input vector is empty,
         * it prints "[]".
         *
         * @tparam T The type of the elements stored in the inner vectors.
         * @param output The 2D vector to be printed.
         */
        template <typename T>
        void println(const ocf::vec<ocf::vec<T>> &output) noexcept
        {
            if (output.empty())
            {
                std::cout << "[]" << '\n';
                return;
            }
            std::cout << "[";
            for (iter_less(i, output.size()))
            {
                std::cout << "[";
                for (iter_less(j, output[i].size()))
                {
                    std::cout << output[i][j];
                    if (j != output[i].size() - 1)
                        std::cout << ", ";
                }
                std::cout << "]";
                if (i != output.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "]" << '\n';
        }

        /**
         * @brief Prints a 3D vector to the standard output in a formatted manner.
         * This function outputs the contents of a three-dimensional vec to std::cout,
         * formatting it as nested lists (e.g., [[[1, 2], [3, 4]], [[5, 6], [7, 8]]]). If the input vector is empty,
         * it prints "[]".
         * @param output The 3D vector to be printed.
         * @tparam T The type of the elements stored in the innermost vectors.
         * @note The function is marked noexcept and does not throw exceptions.
         * @example
         * ocf::vec<ocf::vec<ocf::vec<int>>> vec3d = {
         *     {{1, 2}, {3, 4}},
         *     {{5, 6}, {7, 8}}
         * };
         */
        template <typename T>
        void print(const ocf::vec<ocf::vec<ocf::vec<T>>> &output) noexcept
        {
            if (output.empty())
            {
                std::cout << "[]";
                return;
            }
            std::cout << "[";
            for (iter_less(i, output.size()))
            {
                std::cout << "[";
                for (iter_less(j, output[i].size()))
                {
                    std::cout << "[";
                    for (iter_less(k, output[i][j].size()))
                    {
                        std::cout << output[i][j][k];
                        if (k != output[i][j].size() - 1)
                            std::cout << ", ";
                    }
                    std::cout << "]";
                    if (j != output[i].size() - 1)
                        std::cout << ", ";
                }
                std::cout << "]";
                if (i != output.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "]";
        }

        /**
         * @brief Prints a 3D vector to the standard output in a formatted manner.
         * This function outputs the contents of a three-dimensional vec to std::cout,
         * formatting it as nested lists (e.g., [[[1, 2], [3, 4]], [[5, 6], [7, 8]]]). If the input vector is empty,\
         * it prints "[]".
         * @param output The 3D vector to be printed.
         * @tparam T The type of the elements stored in the innermost vectors.
         * @note The function is marked noexcept and does not throw exceptions.
         * @example
         * ocf::vec<ocf::vec<ocf::vec<int>>> vec3d = {
         *     {{1, 2}, {3, 4}},
         *     {{5, 6}, {7, 8}}
         * };
         */
        template <typename T>
        void println(const ocf::vec<ocf::vec<ocf::vec<T>>> &output) noexcept
        {
            if (output.empty())
            {
                std::cout << "[]" << '\n';
                return;
            }
            std::cout << "[";
            for (iter_less(i, output.size()))
            {
                std::cout << "[";
                for (iter_less(j, output[i].size()))
                {
                    std::cout << "[";
                    for (iter_less(k, output[i][j].size()))
                    {
                        std::cout << output[i][j][k];
                        if (k != output[i][j].size() - 1)
                            std::cout << ", ";
                    }
                    std::cout << "]";
                    if (j != output[i].size() - 1)
                        std::cout << ", ";
                }
                std::cout << "]";
                if (i != output.size() - 1)
                    std::cout << ", ";
            }
            std::cout << "]" << '\n';
        }

        /**
         * @brief Combines Test() and PrintVec() to test and print vector content.
         * @tparam T The type of vector elements.
         * @param testNum Test number.
         * @param input The vector to test and print.
         */
        template <typename T>
        inline void print_test(size_t testNum,
            const ocf::vec<T> &input) noexcept
        {
            print_test(testNum);
            print<T>(input);
        }

        /**
         * @brief Combines Test() and PrintVec() to test and print 2D vector content.
         * @tparam T The type of vector elements.
         * @param testNum Test number.
         * @param input The 2D vector to test and print.
         * @note This function throws an exception if the input vector is empty.
         * @example
         * ocf::vec<ocf::vec<int>> vec2d = {
         *    {1, 2},
         *    {3, 4}
         * };
         */
        template <typename T>
        inline void print_test(size_t testNum,
            const ocf::vec<ocf::vec<T>> &input) noexcept
        {
            print_test(testNum);
            print<T>(input);
        }

        /**
         * @brief Combines Test() and PrintVec() to test and print 3D vector content.
         * @tparam T The type of vector elements.
         * @param testNum Test number.
         * @param input The 3D vector to test and print.
         * @note This function throws an exception if the input vector is empty.
         * @example
         * ocf::vec<ocf::vec<ocf::vec<int>>> vec3d = {
         *    {{1, 2}, {3, 4}},
         *    {{5, 6}, {7, 8}}
         * };
         */
        template <typename T>
        inline void print_test(size_t testNum,
            const ocf::vec<ocf::vec<ocf::vec<T>>> &input) noexcept
        {
            print_test(testNum);
            print<T>(input);
        }

        /**
         * @brief Prints characters of a string individually starting from a given
         * index.
         * @param ocf::str The string to print.
         * @param index Starting index (default = 0). If out of range, starts from 0.
         */
        inline void print_char_str(const ocf::str &input, size_t index) noexcept
        {
            if (index >= input.length())
                index = 0;
            for (size_t i = index; i < input.length(); i++)
                std::cout << input[i] << ' ';
            std::cout << '\n';
        }

        /**
         * @brief Prints a decorated category title.
         * @param category The category title to print.
         */
        inline void print_category(const ocf::str &category) noexcept
        {
            separator(2 * category.length());
            tabs(category.length() / 10);
            std::cout << category << '\n';
            separator(2 * category.length());
        }

        /**
         * @brief Prints a formatted category name with separators and indentation.
         *
         * This function outputs the given category string (`category_s`) to the
         * standard output stream, surrounded by separator lines of a specified
         * length and character. It also indents the category text by a given
         * number of tab characters before printing.
         *
         * @param category_s  The category name to be printed.
         * @param tabs_num    Number of tab characters to print before the category text.
         * @param seplen      The length of the separator line (number of repeated characters).
         * @param sepch       The character used to build the separator line.
         *
         * @note This function relies on external helper functions:
         *       - separator(int length, char ch): prints a separator line.
         *       - Tabs(int n): prints a number of tab characters.
         *
         * @example
         * // Example: print the word "Settings" with 1 tab,
         * // a separator of length 20 made of '=' characters:
         * print_category("Settings", 1, 20, '=');
         *
         * // Expected output:
         * ====================
         *     Settings
         * ====================
         */
        inline void print_category(
            const ocf::str &category_s,
            size_t tabs_num, size_t seplen,
            char sepch) noexcept
        {
            separator(seplen, sepch);
            tabs(tabs_num);
            std::cout << category_s << '\n';
            separator(seplen, sepch);
        }

        /**
         * @brief Prints a value followed by a newline to standard output if a given condition is true.
         * @tparam T Type of the value to print.
         * @param Fp A function that takes a value of type T and returns a boolean indicating whether to print the value.
         * @param data The value to be evaluated and potentially printed.
         * @details This function evaluates the provided value using the given function pointer (or lambda). If the function returns true for the provided data, the value is printed to standard output followed by a newline. If the function returns false, nothing is printed.
         */
        template<typename T>
        inline void print_if(
            ocf::func<bool(T)> Fp, 
            const T& data) noexcept { if(Fp(data)) print(data); }

        /**
         * @brief Prints a value followed by a newline to standard output if a given condition is true.
         * @tparam T Type of the value to print.
         * @param Fp A function that takes a value of type T and returns a boolean indicating whether to print the value.
         * @param data The value to be evaluated and potentially printed.
         * @details This function evaluates the provided value using the given function pointer (or lambda). If the function returns true for the provided data, the value is printed to standard output followed by a newline. If the function returns false, nothing is printed.
         */
        template<typename T>
        inline void println_if(
            ocf::func<bool(T)> Fp,
            const T& data) noexcept { if(Fp(data)) println(data); }

        template<typename T>
        inline void print_if(bool result, const T& data) noexcept { if(result) print(data); }

        template<typename T>
        inline void println_if(bool result, const T& data) noexcept { if(result) print(data); }
        
        template<typename T, typename U>
        inline void print_if(bool result, const T& ifData, const T& elseData) noexcept {
            if(result) std::cout << ifData;
            else std::cout << elseData;
        }

        template<typename T, typename U>
        inline void println_if(bool result, const T& ifData, const T& elseData) noexcept {
            if(result) std::cout << ifData << '\n';
            else std::cout << elseData << '\n';
        }
    }
}
#endif // ETL___IO_HPP