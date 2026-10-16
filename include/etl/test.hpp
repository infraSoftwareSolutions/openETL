/**
 * @file test.hpp
 * @brief Lightweight C++ Unit Testing Framework
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 * 
 * @overview
 * A comprehensive and easy-to-use unit testing framework for C++23 projects.
 * This header provides a complete set of testing utilities for validating functions,
 * vectors (1D, 2D, 3D), and basic data type comparisons. The framework is designed
 * for simplicity and efficiency, with minimal overhead and clear reporting.
 * 
 * @main_components
 * 
 * 1. TEST Class
 *    - Represents a single test case with name, description, and result
 *    - Supports copy construction and assignment operators
 *    - Provides logical operators (==, !=, ||, &&, ^, |=, &=, ^=)
 *    - Methods: set(), get(), operator[]()
 * 
 * 2. test Namespace
 *    - count struct: Tracks test counts for different categories (function, vector, basic)
 *    - index: Global counter instance
 * 
 * @functions_overview
 * 
 * Basic Testing:
 *   - basic<T>()                : Compare single values (with/without metadata)
 * 
 * Vector Testing:
 *   - vector<T>()               : Compare 1D vectors
 *   - vector_2d<T>()            : Compare 2D vectors
 *   - vector_3d<T>()            : Compare 3D vectors
 * 
 * Function Testing:
 *   - function<T>()             : Test parameterless functions
 *   - function<T>(T, T)         : Test single-parameter functions
 *   - function<T1, T2>()        : Test functions with type conversion
 *   - function<T1, T2, T3>()    : Test two-parameter functions
 * 
 * Utility Functions:
 *   - test_message()            : Convert test result to "Success" or "Failed"
 *   - reset_count()             : Reset basic test counter
 *   - reset_vector_count()      : Reset vector test counter
 *   - reset_function_count()    : Reset function test counter
 *   - reset_all_counts()        : Reset all counters
 * 
 * @features
 * - Template-based for type flexibility
 * - No-throw guarantee (noexcept)
 * - Support for parameterized tests with names and descriptions
 * - Automatic test counting and categorization
 * - Works with STL containers (ocf::vec)
 * - Compile-time evaluation support (constexpr)
 * 
 * @usage_example
 * TEST result = lite::test::basic<int>(42, 42, "Integer Test", "Testing if 42 equals 42");
 * std::cout << result.get(true) << ": " << lite::test::test_message(result.get());
 * 
 * @note Requires C++23 or later for full compatibility.
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "io.hpp"
#include "cfrost/structure.h"
#include "cfrost/types.h"

#pragma once
#ifndef ETL___TEST_HPP
#define ETL___TEST_HPP
namespace etl {
            /**
         * @class TEST
         * @brief Represents a single test case with metadata and result tracking.
         * 
         * The TEST class encapsulates a test case with optional name, description,
         * and boolean result. It provides comprehensive operators for logical operations.
         */
        class TEST
        {
        private:
            ocf::str name;
            ocf::str description;
            bool result;
        public:
            /**
             * @brief Default constructor initializing a test with default values.
             */
            TEST() : name("default"),
            description("no description"),
            result(false) {};

            /**
             * @brief Constructor with test result only.
             * @param value The boolean result of the test
             */
            TEST(bool value) noexcept :
            name("default"),
            description("no description"),
            result(value) {}
            
            /**
             * @brief Constructor with test name only.
             * @param name The name/identifier of the test
             */
            TEST(const ocf::str& Name) noexcept : 
            name(Name), 
            description("no description"), 
            result(false) {}
            
            /**
             * @brief Constructor with test name and description.
             * @param name The name/identifier of the test
             * @param description The detailed description of the test
             */
            TEST(const ocf::str& name, const ocf::str& description) noexcept {
                this->name = name;
                this->description = description;
                result = false;
            }
            
            /**
             * @brief Full constructor with all test properties.
             * @param name The name/identifier of the test
             * @param description The detailed description of the test
             * @param result The boolean result of the test
             */
            TEST(const ocf::str& Name,
                const ocf::str& Description,
                bool Result) noexcept : 
                name(Name),
                description(Description),
                result(Result) {}

            /**
             * @brief Copy constructor.
             * @param other The TEST class to copy from
             */
            TEST(const TEST& other) noexcept : 
            name(other.name),
            description(other.description),
            result(other.result) {}

            /**
             * @brief Destructor.
             */
            ~TEST() noexcept = default;

            /**
             * @brief Set the test name.
             * @param name The new test name
             */
            void set(const ocf::str& name) noexcept {
                this->name = name;
            }

            /**
             * @brief Set the test result.
             * @param result The new test result (true = pass, false = fail)
             */
            constexpr void set(bool result) noexcept {
                this->result = result;
            }

            /**
             * @brief Get the test name or description.
             * @param isName If true, returns the name; if false, returns the description
             * @return The requested string property
             */
            ocf::str get(bool isName) noexcept {
                return isName ? name : description;
            }

            /**
             * @brief Get the test result.
             * @return The test result (true = pass, false = fail)
             */
            constexpr bool get() noexcept {
                return result;
            }

            /**
             * @brief Assignment operator for boolean value.
             * @param result The new result value
             */
            void operator=(bool result) noexcept {
                this->result = result;
            }

            /**
             * @brief Equality comparison operator with boolean.
             * @param value The value to compare with
             * @return True if result equals value
             */
            constexpr bool operator==(bool value) noexcept {
                return result == value;
            }

            /**
             * @brief Inequality comparison operator with boolean.
             * @param value The value to compare with
             * @return True if result does not equal value
             */
            constexpr bool operator!=(bool value) noexcept {
                return result != value;
            }

            /**
             * @brief Logical OR operator with boolean.
             * @param value The value to OR with
             * @return Logical OR of result and value
             */
            constexpr bool operator||(bool value) noexcept {
                return result || value;
            }

            /**
             * @brief Logical AND operator with boolean.
             * @param value The value to AND with
             * @return Logical AND of result and value
             */
            constexpr bool operator&&(bool value) noexcept {
                return result && value;
            }

            /**
             * @brief Bitwise XOR operator with boolean.
             * @param value The value to XOR with
             * @return Bitwise XOR of result and value
             */
            constexpr bool operator^(bool value) noexcept {
                return result ^ value;
            }

            /**
             * @brief Bitwise OR assignment operator with boolean.
             * @param value The value to OR assign with
             */
            constexpr void operator|=(bool value) noexcept {
                result |= value;
            }

            /**
             * @brief Bitwise AND assignment operator with boolean.
             * @param value The value to AND assign with
             */
            constexpr void operator&=(bool value) noexcept {
                result &= value;
            }

            /**
             * @brief Bitwise XOR assignment operator with boolean.
             * @param value The value to XOR assign with
             */
            constexpr void operator^=(bool value) noexcept {
                result ^= value;
            }

            /**
             * @brief Copy assignment operator with another TEST object.
             * @param other The TEST class to copy from
             */
            void operator=(const TEST& other) noexcept {
                name = other.name;
                description = other.description;
                result = other.result;
            }

            /**
             * @brief Equality comparison operator with another TEST object.
             * @param value The TEST class to compare with
             * @return True if both results are equal
             */
            constexpr bool operator==(const TEST& value) noexcept {
                return result == value.result;
            }

            /**
             * @brief Inequality comparison operator with another TEST object.
             * @param value The TEST class to compare with
             * @return True if results are not equal
             */
            constexpr bool operator!=(const TEST& value) noexcept {
                return result != value.result;
            }

            /**
             * @brief Logical OR operator with another TEST object.
             * @param value The TEST class to OR with
             * @return Logical OR of both results
             */
            constexpr bool operator||(const TEST& value) noexcept {
                return result || value.result;
            }

            /**
             * @brief Logical AND operator with another TEST object.
             * @param value The TEST class to AND with
             * @return Logical AND of both results
             */
            constexpr bool operator&&(const TEST& value) noexcept {
                return result && value.result;
            }

            /**
             * @brief Bitwise XOR operator with another TEST object.
             * @param value The TEST class to XOR with
             * @return Bitwise XOR of both results
             */
            constexpr bool operator^(const TEST& value) noexcept {
                return result ^ value.result;
            }

            /**
             * @brief Bitwise OR assignment operator with another TEST object.
             * @param value The TEST class to OR assign with
             */
            constexpr void operator|=(const TEST& value) noexcept {
                result |= value.result;
            }

            /**
             * @brief Bitwise AND assignment operator with another TEST object.
             * @param value The TEST class to AND assign with
             */
            constexpr void operator&=(const TEST& value) noexcept {
                result &= value.result;
            }

            /**
             * @brief Bitwise XOR assignment operator with another TEST object.
             * @param value The TEST class to XOR assign with
             */
            constexpr void operator^=(const TEST& value) noexcept {
                result ^= value.result;
            }

            /**
             * @brief Subscript operator to retrieve result by test name.
             * @param name The test name to look up
             * @return The test result if name matches, bool() otherwise with error message
             */
            bool operator[](const ocf::str& name) noexcept {
                if(name == this->name) return result;
                std::cerr << "Name Error: Unknown name." << std::endl;
                return bool();
            }
        };

        namespace test
        {
            /**
             * @brief Structure to keep track of test counts for different categories.
             *
             * This structure contains counters for various test categories:
             * - function: Number of function-related tests.
             * - vector: Number of vector-related tests.
             * - basic: Number of basic tests.
             *
             * The default value for each counter is 1.
             */
            struct count
            {
                size_t function = 0;
                size_t vector = 0;
                size_t basic = 0;
            } index;

            /**
             * @brief Returns a message indicating the result of a test.
             *
             * This function returns "Success" if the test_result is true,
             * otherwise it returns "Failed".
             *
             * @param test_result The result of the test (true for success, false for failure).
             * @return const char* A string message representing the test result.
             * @note This function is noexcept and guarantees not to throw exceptions.
             */
            const ocf::str test_message(bool test_result) noexcept
            {
                return test_result ? 
                "Success" : "Failed";
            }

            /**
             * @brief Basic template test function comparing two values.
             * @tparam T The type of values being compared
             * @param realvalue The actual value from code execution
             * @param expvalue The expected value
             * @return True if values are equal, false otherwise
             * @note Increments the basic test counter
             */
            template <typename T>
            inline bool equal(const T& realvalue, const T& expvalue) noexcept
            {
                index.basic++;
                return realvalue == expvalue;
            }

            /**
             * @brief Basic template test function with metadata.
             * @tparam T The type of values being compared
             * @param realvalue The actual value from code execution
             * @param expvalue The expected value
             * @param name The test name
             * @param description The test description
             * @return TEST class containing result and metadata
             * @note Increments the basic test counter
             */
            template <typename T>
            TEST equal(
                const T& realvalue,
                const T& expvalue,
                const ocf::str& name,
                const ocf::str& description) noexcept
            {
                index.basic++;
                return !(name.empty()) && !(description.empty()) ?
                TEST{name, description, realvalue == expvalue} :
                TEST{realvalue == expvalue};
            }

            template <typename T>
            bool range(T realvalue, T uplimit, T downlimit) noexcept {
                return realvalue < uplimit && realvalue > downlimit;
            }

            template <typename T>
            TEST range(T realvalue, T uplimit, T downlimit,
                const ocf::str& name, const ocf::str& description) noexcept {
                return name.empty() && description.empty() ? 
                TEST{range(realvalue, uplimit, downlimit)} : 
                TEST{name, description, range(realvalue, uplimit, downlimit)};
            }

            /**
             * @brief Test function for comparing 1D vectors.
             * @tparam T The type of elements in the vectors
             * @param real_v The actual vector from code execution
             * @param expected_v The expected vector
             * @return True if vectors are equal, false otherwise
             * @note Increments the vector test counter
             */
            template <typename T>
            bool vector(const ocf::vec<T>& real_v, const ocf::vec<T>& expected_v) noexcept
            {
                index.vector++;
                if (real_v.size() != expected_v.size()) {
                    return false;
                }
                for (size_t i = 0; i < real_v.size(); i++) {
                    if(real_v[i] != expected_v[i])
                        return false;
                }
                return true;
            }

            /**
             * @brief Test function for comparing 1D vectors with metadata.
             * @tparam T The type of elements in the vectors
             * @param real_v The actual vector from code execution
             * @param expected_v The expected vector
             * @param name The test name
             * @param description The test description
             * @return TEST class containing result and metadata
             * @note Increments the vector test counter
             */
            template <typename T>
            TEST vector(
                const ocf::vec<T>& real_v,
                const ocf::vec<T>& expected_v,
                const ocf::str& name,
                const ocf::str& description) noexcept
            {
                index.vector++;
                if (real_v.size() != expected_v.size()) {
                    return !(name.empty()) && !(description.empty()) ? 
                    TEST{name, description, false} : TEST{false};
                }
                for (size_t i = 0; i < real_v.size(); i++) {
                    if(real_v[i] != expected_v[i]) {
                        return !(name.empty()) && !(description.empty()) ?
                        TEST{name, description, false} : TEST{false};
                    }
                }
                return !(name.empty()) && !(description.empty()) ? 
                TEST{name, description, true} : TEST{true};
            }

            /**
             * @brief Test function for comparing 2D vectors.
             * @tparam T The type of elements in the vectors
             * @param real_2dv The actual 2D vector from code execution
             * @param expected_2dv The expected 2D vector
             * @return True if 2D vectors are equal, false otherwise
             * @note Increments the vector test counter
             */
            template <typename T>
            bool vector_2d(const ocf::vec<ocf::vec<T>>& real_2dv,
                        const ocf::vec<ocf::vec<T>>& expected_2dv) noexcept
            {
                index.vector++;
                if (real_2dv.size() != expected_2dv.size()) {
                    return false;
                }
                for (size_t i = 0; i < real_2dv.size(); i++) {
                    if(real_2dv[i].size() != expected_2dv[i].size()) {
                        return false;
                    }
                    for(size_t j = 0; j < real_2dv[i].size(); j++) {
                        if(real_2dv[i][j] != expected_2dv[i][j]) {
                            return false;
                        }
                    }
                }
                return true;
            }

            /**
             * @brief Test function for comparing 2D vectors with metadata.
             * @tparam T The type of elements in the vectors
             * @param real_2dv The actual 2D vector from code execution
             * @param expected_2dv The expected 2D vector
             * @param name The test name
             * @param description The test description
             * @return TEST class containing result and metadata
             * @note Increments the vector test counter
             */
            template <typename T>
            TEST vector_2d(const ocf::vec<ocf::vec<T>>& real_2dv,
                        const ocf::vec<ocf::vec<T>>& expected_2dv,
                        const ocf::str& name,
                        const ocf::str& description) noexcept
            {
                index.vector++;
                if (real_2dv.size() != expected_2dv.size()) {
                    return !(name.empty()) && !(description.empty()) ? 
                    TEST{name, description, false} : TEST{false};
                }
                for (size_t i = 0; i < real_2dv.size(); i++) {
                    if(real_2dv[i].size() != expected_2dv.size()) {
                        return !(name.empty()) && !(description.empty()) ? 
                        TEST{name, description, false} : TEST{false};
                    }
                    for(size_t j = 0; j < real_2dv[i].size(); j++) {
                        if(real_2dv[i] != expected_2dv[i]) {
                            return !(name.empty()) && !(description.empty()) ?
                            TEST{name, description, false} : TEST{false};
                        }
                    }
                }
                return !(name.empty()) && !(description.empty()) ?
                TEST{name, description, false} : TEST{false};
            }

            /**
             * @brief Test function for comparing 3D vectors.
             * @tparam T The type of elements in the vectors
             * @param real_3dv The actual 3D vector from code execution
             * @param expected_3dv The expected 3D vector
             * @return True if 3D vectors are equal, false otherwise
             * @note Increments the vector test counter
             */
            template <typename T>
            bool vector_3d(const ocf::vec<ocf::vec<ocf::vec<T>>>& real_3dv,
                        const ocf::vec<ocf::vec<ocf::vec<T>>>& expected_3dv) noexcept
            {
                index.vector++;
                if (real_3dv.size() != expected_3dv.size()) {
                    return false;
                }
                for (size_t i = 0; i < real_3dv.size(); i++) {
                    if(real_3dv[i].size() != expected_3dv[i].size()) {
                        return false;
                    }
                    for(size_t j = 0; j < real_3dv[i].size(); j++) {
                        if(real_3dv[i][j].size() != expected_3dv[i][j].size()) {
                            return false;
                        }
                        for(size_t z = 0; z < real_3dv[i][j].size(); z++) {
                            if(real_3dv[i][j][z] != expected_3dv[i][j][z]) {
                                return false;
                            }
                        }
                    }
                }
                return true;
            }

            /**
             * @brief Test function for comparing 3D vectors with metadata.
             * @tparam T The type of elements in the vectors
             * @param real_3dv The actual 3D vector from code execution
             * @param expected_3dv The expected 3D vector
             * @param name The test name
             * @param description The test description
             * @return TEST class containing result and metadata
             * @note Increments the vector test counter
             */
            template <typename T>
            TEST vector_3d(const ocf::vec<ocf::vec<ocf::vec<T>>>& real_3dv,
                        const ocf::vec<ocf::vec<ocf::vec<T>>>& expected_3dv,
                        const ocf::str& name, const ocf::str& description) noexcept
            {
                if (real_3dv.size() != expected_3dv.size()) {
                    return !(name.empty()) && !(description.empty()) ? 
                    TEST{name, description, false} : TEST{false};
                }
                for (size_t i = 0; i < real_3dv.size(); i++) {
                    if(real_3dv[i].size() != expected_3dv[i].size()) {
                        return !(name.empty()) && !(description.empty()) ? 
                        TEST{name, description, false} : TEST{false};
                    }
                    for(size_t j = 0; j < real_3dv[i].size(); j++) {
                        if(real_3dv[i][j].size() != expected_3dv[i][j].size()) {
                            return !(name.empty()) && !(description.empty()) ? 
                            TEST{name, description, false} : TEST{false};
                        }
                        for(size_t z = 0; z < real_3dv[i][j].size(); z++) {
                            if(real_3dv[i][j][z] != expected_3dv[i][j][z]) {
                                return !(name.empty()) && !(description.empty()) ? 
                                TEST{name, description, false} : TEST{false};
                            }
                        }
                    }
                }
                return !(name.empty()) && !(description.empty()) ? 
                TEST{name, description, false} : TEST{false};
            }

            /**
             * @brief Test function without parameters.
             * @tparam T The return type of the function
             * @param fx The parameterless function to test
             * @param expected The expected return value
             * @return True if function result equals expected, false otherwise
             * @note Increments the function test counter
             */
            template <typename T>
            bool function(std::function<T()> fx, T expected) noexcept
            {
                index.function++;
                return fx() == expected;
            }

            /**
             * @brief Test function without parameters with metadata.
             * @tparam T The return type of the function
             * @param fx The parameterless function to test
             * @param expected The expected return value
             * @param name The test name
             * @param description The test description
             * @return TEST class containing result and metadata
             * @note Increments the function test counter
             */
            template <typename T>
            TEST function(std::function<T()> fx, T expected,
                        const ocf::str& name,
                        const ocf::str& description) noexcept
            {
                index.function++;
                return !(name.empty()) && !(description.empty()) ? 
                TEST{name, description, fx() == expected} :
                TEST{fx() == expected};
            }

            /**
             * @brief Test function with single parameter (same type).
             * @tparam T The parameter and return type of the function
             * @param fx The function to test
             * @param value The input value
             * @param expected The expected return value
             * @return True if function result equals expected, false otherwise
             * @note Increments the function test counter
             */
            template <typename T>
            bool function(std::function<T(T)> fx, T value, T expected) noexcept
            {
                index.function++;
                return fx(value) == expected;
            }

            /**
             * @brief Test function with single parameter with metadata.
             * @tparam T The parameter and return type of the function
             * @param fx The function to test
             * @param value The input value
             * @param expected The expected return value
             * @param name The test name
             * @param description The test description
             * @return TEST class containing result and metadata
             * @note Increments the function test counter
             */
            template <typename T>
            TEST function(std::function<T(T)> fx, T value, T expected,
                        const ocf::str& name,
                        const ocf::str& description) noexcept
            {
                index.function++;
                return !(name.empty()) && !(description.empty()) ? 
                TEST{name, description, fx(value) == expected} :
                TEST{fx(value) == expected};
            }

            /**
             * @brief Test function with type conversion.
             * @tparam T1 The return type of the function
             * @tparam T2 The parameter type of the function
             * @param fx The function to test
             * @param value The input value
             * @param expected The expected return value
             * @return True if function result equals expected, false otherwise
             * @note Increments the function test counter
             */
            template <typename T1, typename T2>
            bool function(std::function<T1(T2)> fx, T2 value, T1 expected) noexcept
            {
                index.function++;
                return fx(value) == expected;
            }

            /**
             * @brief Test function with type conversion with metadata.
             * @tparam T1 The return type of the function
             * @tparam T2 The parameter type of the function
             * @param fx The function to test
             * @param value The input value
             * @param expected The expected return value
             * @param name The test name
             * @param description The test description
             * @return TEST class containing result and metadata
             * @note Increments the function test counter
             */
            template <typename T1, typename T2>
            TEST function(std::function<T1(T2)> fx, T2 value, T1 expected,
                        const ocf::str& name, const ocf::str& description) noexcept
            {
                index.function++;
                return !(name.empty()) && !(description.empty()) ? 
                TEST{name, description, fx(value) == expected} :
                TEST{fx(value) == expected};
            }

            /**
             * @brief Test function with two parameters.
             * @tparam T1 The return type of the function
             * @tparam T2 The first parameter type
             * @tparam T3 The second parameter type
             * @param fx The function to test
             * @param expected The expected return value
             * @param value1 The first input value
             * @param value2 The second input value
             * @return Result of function call
             * @note Increments the function test counter
             */
            template <typename T1, typename T2, typename T3>
            bool function(std::function<T1(T2, T3)> fx, T1 expected, T2 value1, T3 value2) noexcept
            {
                index.function++;
                return fx(value1, value2) == expected;
            }

            /**
             * @brief Test function with two parameters with metadata.
             * @tparam T1 The return type of the function
             * @tparam T2 The first parameter type
             * @tparam T3 The second parameter type
             * @param fx The function to test
             * @param expected The expected return value
             * @param value1 The first input value
             * @param value2 The second input value
             * @param name The test name
             * @param description The test description
             * @return TEST class containing result and metadata
             * @note Increments the function test counter
             */
            template <typename T1, typename T2, typename T3>
            TEST function(std::function<T1(T2, T3)> fx, T1 expected,
                        T2 value1, T3 value2, const ocf::str& name,
                        const ocf::str& description) noexcept
            {
                index.function++;
                return !(name.empty()) && !(description.empty()) ? 
                TEST{name, description, fx(value1, value2) == expected} :
                TEST{fx(value1, value2) == expected};
            }

            /**
             * @brief Resets the basic test counter to its initial value.
             * Sets index.basic = 1. This function is constexpr and noexcept.
             */
            constexpr inline void reset_count() noexcept { index.basic = 1; }

            /**
             * @brief Resets the vector test counter to its initial value.
             * Sets index.vector = 1. This function is constexpr and noexcept.
             */
            constexpr inline void reset_vector_count() noexcept { index.vector = 1; }

            /**
             * @brief Resets the function test counter to its initial value.
             * Sets index.function = 1. This function is constexpr and noexcept.
             */
            constexpr inline void reset_function_count() noexcept { index.function = 1; }

            /**
             * @brief Resets all internal test counters to their initial state.
             * Calls reset_count(), reset_vector_count(), and reset_function_count()
             * to reset all respective counters. This function is constexpr and noexcept.
             */
            constexpr inline void reset_all_counts() noexcept
            {
                reset_count();
                reset_vector_count();
                reset_function_count();
            }

            /**
             * @brief A class that aggregates boolean test results with exception handling.
             */
            class stream
            {
            private:
                ocf::vec<TEST> container;
                bool result_ts = true;
                size_t total_tests = 0;
                size_t passed_tests = 0;
                size_t failed_tests = 0;
                ocf::vec<ocf::str> error_log;

            public:
                stream() = default;

                /**
                 * @brief Overloaded operator<< to handle boolean function execution with exception handling
                 *
                 * This operator takes a function object that returns a boolean value and executes it.
                 * The result is combined with the existing result_ts using logical AND operation.
                 * If the function is not marked noexcept, it wraps the execution in a try-catch block
                 * to handle various types of exceptions.
                 *
                 * @param fx A func object that returns bool and takes no parameters
                 * @noexcept This operator itself is marked noexcept, though the contained function may throw
                 *
                 * Exception handling includes:
                 * - std::invalid_argument
                 * - std::length_error
                 * - std::exception
                 * - const char* messages
                 * - Any other unhandled exceptions
                 *
                 * On any exception, result_ts is set to false and an error message is output to std::cerr
                 */
                void operator<<(ocf::func<bool()> fx) noexcept
                {
                    total_tests++;
                    bool test_result = false;
                    if (std::is_nothrow_invocable_r_v<bool, ocf::func<bool()>, bool>)
                    {
                        test_result = fx();
                        result_ts &= test_result;
                    }
                    else
                    {
                        try
                        {
                            test_result = fx();
                            result_ts &= test_result;
                        }
                        catch (const std::invalid_argument &e)
                        {
                            ocf::str err_msg = "invalid argument: " + ocf::str(e.what());
                            std::cerr << err_msg << std::endl;
                            error_log.push_back(err_msg);
                            test_result = false;
                            result_ts = false;
                        }
                        catch (const std::length_error &e)
                        {
                            ocf::str err_msg = "length error: " + ocf::str(e.what());
                            std::cerr << err_msg << std::endl;
                            error_log.push_back(err_msg);
                            test_result = false;
                            result_ts = false;
                        }
                        catch (const std::exception &e)
                        {
                            ocf::str err_msg = "Exception: " + ocf::str(e.what());
                            std::cerr << err_msg << "\n";
                            error_log.push_back(err_msg);
                            test_result = false;
                            result_ts = false;
                        }
                        catch (const char *msg)
                        {
                            ocf::str err_msg = "Error: " + ocf::str(msg);
                            std::cerr << err_msg << "\n";
                            error_log.push_back(err_msg);
                            test_result = false;
                            result_ts = false;
                        }
                        catch (...)
                        {
                            ocf::str err_msg = "Unknown error occurred";
                            std::cerr << err_msg << "\n";
                            error_log.push_back(err_msg);
                            test_result = false;
                            result_ts = false;
                        }
                    }
                    if (test_result)
                        passed_tests++;
                    else
                        failed_tests++;
                    container.push_back(TEST{fx()});
                }

                void operator<<(ocf::func<TEST()> fx) noexcept
                {
                    total_tests++;
                    bool test_result = false;
                    if (std::is_nothrow_invocable_r_v<bool, ocf::func<bool()>, bool>)
                    {
                        test_result = fx().get();
                        result_ts &= test_result;
                    }
                    else
                    {
                        try
                        {
                            test_result = fx().get();
                            result_ts &= test_result;
                        }
                        catch (const std::invalid_argument &e)
                        {
                            ocf::str err_msg = "invalid argument: " + ocf::str(e.what());
                            std::cerr << err_msg << std::endl;
                            error_log.push_back(err_msg);
                            test_result = false;
                            result_ts = false;
                        }
                        catch (const std::length_error &e)
                        {
                            ocf::str err_msg = "length error: " + ocf::str(e.what());
                            std::cerr << err_msg << std::endl;
                            error_log.push_back(err_msg);
                            test_result = false;
                            result_ts = false;
                        }
                        catch (const std::exception &e)
                        {
                            ocf::str err_msg = "Exception: " + ocf::str(e.what());
                            std::cerr << err_msg << "\n";
                            error_log.push_back(err_msg);
                            test_result = false;
                            result_ts = false;
                        }
                        catch (const char *msg)
                        {
                            ocf::str err_msg = "Error: " + ocf::str(msg);
                            std::cerr << err_msg << "\n";
                            error_log.push_back(err_msg);
                            test_result = false;
                            result_ts = false;
                        }
                        catch (...)
                        {
                            ocf::str err_msg = "Unknown error occurred";
                            std::cerr << err_msg << "\n";
                            error_log.push_back(err_msg);
                            test_result = false;
                            result_ts = false;
                        }
                    }
                    if (test_result)
                        passed_tests++;
                    else
                        failed_tests++;
                    container.push_back(fx());
                }

                void operator<<(bool testResult) noexcept {
                    total_tests++;
                    if(testResult) {
                        passed_tests++;
                    } else {
                        failed_tests++;
                    }
                    result_ts &= testResult;
                    container.push_back(TEST{testResult});
                }

                void operator<<(TEST& testResult) noexcept {
                    total_tests++;
                    if(testResult.get()) {
                        passed_tests++;
                    } else {
                        failed_tests++;
                    }
                    result_ts &= testResult.get();
                    container.push_back(testResult);
                }

                /// @brief Overloaded operator>> to retrieve the aggregated test result
                /// @param value Reference to a boolean variable to store the aggregated result
                void operator>>(bool &value) noexcept { value = result_ts; }

                void operator>>(TEST& value) noexcept {
                    value = TEST{"stream",
                            "the result of all tests in test stream",
                            result_ts};
                }

                TEST operator[](size_t index) noexcept {
                    return container[index];
                }

                /**
                 * @brief Retrieves the total number of tests executed
                 * @return Total count of tests
                 */
                size_t get_total_tests() const noexcept { return total_tests; }

                /**
                 * @brief Retrieves the number of passed tests
                 * @return Count of tests that passed
                 */
                size_t get_passed_tests() const noexcept { return passed_tests; }

                /**
                 * @brief Retrieves the number of failed tests
                 * @return Count of tests that failed
                 */
                size_t get_failed_tests() const noexcept { return failed_tests; }

                /**
                 * @brief Retrieves the success rate percentage
                 * @return Success rate (0.0 to 100.0)
                 */
                float get_success_rate() const noexcept
                {
                    if (total_tests == 0)
                        return 0.0f;
                    return (passed_tests * 100.0f) / total_tests;
                }

                /**
                 * @brief Retrieves the error log
                 * @return Vector containing all error messages
                 */
                const ocf::vec<ocf::str> &get_error_log() const noexcept { return error_log; }

                /**
                 * @brief Clears all test statistics and error log
                 */
                void reset_statistics() noexcept
                {
                    total_tests = 0;
                    passed_tests = 0;
                    failed_tests = 0;
                    error_log.clear();
                    container.clear();
                    result_ts = true;
                }

                ocf::vec<size_t> findIndex(bool isFailed) noexcept {
                    ocf::vec<size_t> result;
                    for(size_t i = 0; i < container.size(); i++) {
                        if(!isFailed && container[i].get()) {
                            result.push_back(i);
                        } else if(isFailed && !container[i].get()) {
                            result.push_back(i);
                        }
                        return result;
                    }
                }

                void find(bool isFailed) noexcept {
                    for(size_t i = 0; i < container.size(); i++) {
                        if(!isFailed && container[i].get()) {
                            io::print_test(container[i].get(true), 
                            container[i].get(false), i, container[i].get());
                        } else if(isFailed && !container[i].get()) {
                            io::print_test(container[i].get(true),
                            container[i].get(false), i, container[i].get());
                        }
                    }
                }

                /**
                 * @brief Prints a complete test summary with statistics
                 */
                void print_summary() const noexcept
                {
                    io::println("=== Test Summary ===");
                    io::println("Total tests: " + std::to_string(total_tests));
                    io::println("Passed: " + std::to_string(passed_tests));
                    io::println("Failed: " + std::to_string(failed_tests));
                    io::println("Success rate: " + std::to_string(get_success_rate()) + "%");
                    if (!error_log.empty())
                    {
                        io::println("=== Error Log ===");
                        for (size_t i = 0; i < error_log.size(); ++i)
                            io::println("[" + std::to_string(i + 1) + "] " + error_log[i]);
                    }
                }
            };
        }
}
#endif // ETL___TEST_HPP