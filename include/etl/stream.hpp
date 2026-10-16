/**
 * @file stream.hpp
 * @brief This header file defines the vstream class, which provides stream-like operations for a vector of type T.
 * The vstream class allows for easy insertion and extraction of elements, as well as various utility functions to manage the underlying vector.
 * Additionally, it includes the benchmark_stream and test_stream classes for benchmarking function execution time and aggregating boolean test results with exception handling, respectively.
 * The stream_t, stream_tp, stream__tp, and stream__t_p classes provide safe execution of function objects with built-in error handling.
 * @note All operations are designed to be noexcept where applicable, ensuring that exceptions are handled gracefully without propagating.
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 * @details This file is part of the MetaCore library, which provides various utilities for C++ programming.
 * - vstream: A stream-like interface for managing a vector of type T, supporting insertion, extraction, and utility functions.
 * - benchmark_stream: A class for benchmarking function execution time with configurable time units and result printing.
 * - test_stream: A class for aggregating boolean test results with exception handling and statistics tracking.
 * - stream_t: A template class for safely executing function objects with built-in error handling.
 * - stream_tp: A template class for safely executing unary functions (T -> T) with built-in error handling.
 * - stream__tp: A template class for safely executing unary transformation functions (T2 -> T1) with built-in error handling.
 * - stream__t_p: A template class for safely executing binary functions (T2, T3 -> T1) with built-in error handling.
 * @note This file is intended to be included in C++ projects that require stream-like operations on vectors, benchmarking capabilities, and safe function execution with error handling.
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <stdexcept>
#include <queue>
#include <type_traits>
#include <string>
#include <cerrno>
#include <stack>

#include "io.hpp"
#include "cfrost/structure.h"
#include "cfrost/types.h"

#pragma once
#ifndef ETL___STREAM_HPP
#define ETL___STREAM_HPP

namespace etl {
        /**
         * @class vstream
         * @brief A class that provides stream-like operations for a vector of type T.
         * This class allows for easy insertion and extraction of elements,
         * as well as various utility functions to manage the underlying vector.
         */
        template <typename T>
        class vstream
        {
        private:
            ocf::que<ocf::vec<T>> vs;

        public:
            /** Default constructor */
            vstream() = default;
            
            /** Constructor from vec
             * @param vec The vector to initialize the stream with
             * @note This constructor copies the vector
             */
            vstream(const ocf::que<ocf::vec<T>> &_vec) noexcept : vs(_vec) {}
            
            /** Constructor from rvalue vec
             * @param vec The vector to initialize the stream with
             * @note This constructor moves the vector
             */
            vstream(ocf::que<ocf::vec<T>> &&_vec) noexcept : vs(std::move(_vec)) {}
            
            /**
             * Constructor from initializer list
             * @param il The initializer list to initialize the stream with
             * @note This constructor copies the elements from the initializer list
             */
            vstream(std::initializer_list<ocf::vec<T>> il) noexcept : vs(il) {}
            
            /**
             * Copy constructor
             * @param other The other vstream to copy from
             * @note This constructor copies the underlying vector
             */
            vstream(const vstream &other) noexcept : vs(other.vs) {}
            
            /**
             * Move constructor
             * @param other The other vstream to move from
             * @note This constructor moves the underlying vector
             */
            vstream(vstream &&other) noexcept : vs(std::move(other.vs)) {}
            
            /**
             * @brief Returns the number of elements in the vector.
             *
             * @return The current size of the vector.
             * @note This function does not throw exceptions.
             */
            size_t size() const noexcept { return vs.size(); }

            /**
             * @brief Checks whether the container is empty.
             *
             * @return true if the container contains no elements, false otherwise.
             * @note This function does not throw exceptions.
             */
            bool empty() const noexcept { return vs.empty(); }

            /**
             * @brief Removes all elements from the container.
             *
             * After calling this function, the container will be empty.
             * No exceptions are thrown.
             */
            void clear() noexcept { 
                while (!vs.empty())
                    vs.pop();
            }

            /**
             * @brief Copy assignment operator for vstream.
             *
             * Assigns the contents of another vstream object to this one.
             * Performs a self-assignment check before copying the internal state.
             *
             * @param other The vstream object to copy from.
             * @return Reference to this vstream object.
             * @note This operator is marked noexcept.
             */
            vstream &operator=(const vstream &other) noexcept
            {
                if (this != &other)
                    vs = other.vs;
                return *this;
            }

            /**
             * @brief Move assignment operator for the vstream class.
             *
             * Transfers ownership of resources from another vstream instance to this instance.
             * If the source and destination are not the same object, the internal stream (vs)
             * is moved from the source to this object, leaving the source in a valid but unspecified state.
             *
             * @param other The vstream instance to move from.
             * @return Reference to this vstream instance.
             */
            vstream &operator=(vstream &&other) noexcept
            {
                if (this != &other)
                    vs = std::move(other.vs);
                return *this;
            }

            /**
             * @brief Assignment operator from vec.
             *
             * Assigns the contents of the given vec<T> to the internal vector 'vs'.
             *
             * @param vec The vec<T> whose contents will be copied.
             * @note This operation is noexcept.
             */
            void operator=(const ocf::que<ocf::vec<T>> &vec) noexcept { vs = vec; }

            /**
             * @brief Move assignment operator from a vec<T>.
             *
             * Replaces the contents of the internal vector 'vs' with those of the given rvalue reference 'vec',
             * transferring ownership of the data without copying.
             *
             * @param vec Rvalue reference to a vec<T> whose contents will be moved.
             * @note This operation is noexcept and leaves 'vec' in a valid but unspecified state.
             */
            void operator=(ocf::que<ocf::vec<T>> &&vec) noexcept { vs = std::move(vec); }

            /**
             * @brief Assignment operator for assigning an initializer list to the container.
             *
             * Replaces the contents of the container with the elements from the given initializer list.
             * This operation is noexcept.
             *
             * @param il The initializer list whose elements will be assigned to the container.
             */
            void operator=(std::initializer_list<ocf::vec<T>> il) noexcept { vs = il; }

            /**
             * @brief Inserts a value into the vector stream.
             *
             * This operator overload allows vectors of type T to be enqueued to the internal queue (vs)
             * using the stream insertion syntax.
             *
             * @param value The vector to be inserted into the queue stream.
             * @note This operation does not support chaining as it returns void.
             */
            void operator<<(const ocf::vec<T> &value) noexcept { vs.push(value); }

            /**
             * @brief Inserts a value into the vector stream using move semantics.
             *
             * This operator overload allows an rvalue reference of type vec<T> to be moved
             * into the internal queue (vs), which improves performance by avoiding unnecessary copies.
             *
             * @param value The rvalue reference to the vector to be inserted.
             * @note This operation does not support chaining as it returns void.
             */
            void operator<<(ocf::vec<T> &&value) noexcept { vs.push(std::move(value)); }

            /**
             * @brief Extracts the front element from the internal queue and assigns it to the provided value.
             *
             * This operator overload removes the front element from the internal queue `vs` (FIFO order)
             * and assigns it to `value` via move semantics.
             * If the queue is empty, it throws a `std::out_of_range` exception.
             *
             * @tparam T The type of the elements stored in the queue.
             * @param value Reference to the variable where the extracted vector will be stored.
             * @throws std::out_of_range if the internal queue is empty.
             */
            void operator>>(ocf::vec<T> &value)
            {
                if (!vs.empty())
                {
                    value = std::move(vs.front());
                    vs.pop();
                }
                else
                    throw std::out_of_range("vstream is empty");
            }

            /** @brief Default destructor for vstream. */
            ~vstream() = default;
        };

        class sstream {
            private:
            bool split;
            ocf::str split_str;
            ocf::que<ocf::str> ss;
            public:

            sstream() noexcept : split(false), split_str(""), ss(ocf::que<ocf::str>()) {};
            sstream(const ocf::que<ocf::str> &strVal) noexcept : split(false), split_str(""), ss(strVal) {}
            sstream(const ocf::str &ssplit) noexcept : split(true), split_str(ssplit), ss(ocf::que<ocf::str>()) {}
            sstream(bool isSplit) noexcept : split(isSplit), split_str(""), ss(ocf::que<ocf::str>()) {}

            void set_split(bool isSplit) noexcept { split = isSplit; }
            void set_split_str(const ocf::str &ssplit) noexcept { split_str = ssplit; }
            
            void operator<<(const ocf::str &value) noexcept {
                if (split && !split_str.empty()) {
                    size_t start = 0;
                    size_t end = value.find(split_str);
                    while (end != ocf::str::npos) {
                        ss.push(value.substr(start, end - start));
                        start = end + split_str.length();
                        end = value.find(split_str, start);
                    }
                    ss.push(value.substr(start));
                } else {
                    ss.push(value);
                }
            }

            void operator>>(ocf::str &value) {
                if (!ss.empty()) {
                    value = ss.front();
                    ss.pop();
                } else {
                    throw std::out_of_range("sstream is empty");
                }
            }
        };

        namespace function
        {   
            /**
             * @brief A template class that wraps a function object and provides
             *        safe execution with built-in error handling.
             *
             * The stream_t class acts as a minimal stream-like container for
             * function objects (ocf::func<T()>). It allows storing a function,
             * retrieving it, and executing it with exception handling.
             *
             * @tparam T The return type of the function object.
             */
            template <typename T, bool immediate_run>
            class stream_t
            {
            private:
                /**
                 * @brief Internal function storage.
                 *
                 * This holds the function object that will be executed when
                 * handler() or run_test() is called.
                 */
                ocf::func<T()> f;

            protected:
                /**
                 * @brief Executes the stored function with exception handling.
                 *
                 * This function runs the stored function object `f()` and
                 * catches common exceptions:
                 * - std::invalid_argument
                 * - std::length_error
                 * - std::exception
                 * - const char* (C-style error messages)
                 *
                 * All errors are reported to std::cerr.
                 *
                 * @note This method is intended for internal use and is
                 *       exposed through run_test().
                 */
                void handler() const noexcept
                {
                    try
                    {
                        f();
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::cerr << "invalid argument: " << e.what() << std::endl;
                    }
                    catch (const std::length_error &e)
                    {
                        std::cerr << "length error: " << e.what() << std::endl;
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "Exception: " << e.what() << "\n";
                    }
                    catch (const char *msg)
                    {
                        std::cerr << "Error: " << msg << "\n";
                    }
                }

            public:
                stream_t() = default;

                /**
                 * @brief Assigns a new function to the stream.
                 *
                 * Example usage:
                 * @code
                 * stream_t<int> s;
                 * s << []() -> int { return 42; };
                 * @endcode
                 *
                 * @param fx The function object to be stored.
                 */
                void operator<<(ocf::func<T()> fx) noexcept
                {
                    f = fx;
                    if (immediate_run)
                        handler();
                }

                /**
                 * @brief Extracts the stored function into another func.
                 *
                 * Example usage:
                 * @code
                 * ocf::func<int()> func;
                 * s >> func; // func now holds the stored function
                 * @endcode
                 *
                 * @param fx Reference to a function object where the stored function will be copied.
                 */
                void operator>>(ocf::func<T()> &fx) noexcept { fx = f; }
                
                /**
                 * @brief Executes the stored function safely.
                 *
                 * This method runs the stored function using handler(),
                 * which ensures that common exceptions are caught and
                 * reported instead of propagating.
                 *
                 * Example usage:
                 * @code
                 * s.run_test();
                 * @endcode
                 */
                void run_test() const noexcept { handler(); }
            };

            /**
             * @brief A template class that wraps a unary function (T -> T)
             *        and provides safe execution with built-in error handling.
             *
             * The stream_tp class stores a function of type ocf::func<T(T)>,
             * allowing input transformation and safe execution with exception handling.
             *
             * @tparam T The input and output type of the function object.
             */
            template <typename T>
            class stream_tp
            {
            private:
                /**
                 * @brief Internal function storage.
                 *
                 * This holds the unary function (T -> T) that will be executed
                 * when handler() or run_test() is called.
                 */
                ocf::func<T(T)> f;

            protected:
                /**
                 * @brief Executes the stored function with the given input and
                 *        provides exception handling.
                 *
                 * This function runs the stored function `f(input)` and catches:
                 * - std::invalid_argument
                 * - std::length_error
                 * - std::exception
                 * - const char* (C-style error messages)
                 *
                 * All errors are reported to std::cerr.
                 *
                 * @param input The input value passed to the stored function.
                 */
                void handler(const T &input) const noexcept
                {
                    try
                    {
                        f(input);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::cerr << "invalid argument: " << e.what() << std::endl;
                    }
                    catch (const std::length_error &e)
                    {
                        std::cerr << "length error: " << e.what() << std::endl;
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "Exception: " << e.what() << "\n";
                    }
                    catch (const char *msg)
                    {
                        std::cerr << "Error: " << msg << "\n";
                    }
                }

            public:
                stream_tp() = default;

                /**
                 * @brief Assigns a new unary function to the stream.
                 *
                 * Example usage:
                 * @code
                 * stream_tp<int> s;
                 * s << [](int x) { return x * x; }; // stores a square function
                 * @endcode
                 *
                 * @param fx The function object to be stored.
                 */
                void operator<<(ocf::func<T(T)> fx) noexcept { f = fx; }
                
                /**
                 * @brief Extracts the stored function into another func.
                 *
                 * Example usage:
                 * @code
                 * ocf::func<int(int)> func;
                 * s >> func; // func now holds the stored function
                 * @endcode
                 *
                 * @param fx Reference to a function object where the stored function will be copied.
                 */
                void operator>>(ocf::func<T(T)> &fx) noexcept { fx = f; }
                
                /**
                 * @brief Executes the stored function with an lvalue reference input.
                 *
                 * Example usage:
                 * @code
                 * int value = 5;
                 * s.run_test(value); // safely runs f(value)
                 * @endcode
                 *
                 * @param value Reference to the input value.
                 */
                void run_test(T &value) const noexcept { handler(value); }
                
                /**
                 * @brief Executes the stored function with an rvalue input.
                 *
                 * Example usage:
                 * @code
                 * s.run_test(10); // safely runs f(10)
                 * @endcode
                 *
                 * @param value Rvalue reference to the input value.
                 */
                void run_test(T &&value) const noexcept { handler(value); }
            };

            /**
             * @brief A template class that wraps a unary transformation function (T2 -> T1)
             *        and provides safe execution with built-in error handling.
             *
             * The stream__tp class stores a function of type ocf::func<T1(T2)>,
             * allowing input of type T2 to be transformed into output of type T1.
             * It also provides exception handling for common errors.
             *
             * @tparam T1 The return type of the stored function.
             * @tparam T2 The input type of the stored function.
             */
            template <typename T1, typename T2>
            class stream__tp
            {
            private:
                /**
                 * @brief Internal function storage.
                 *
                 * Holds the unary function (T2 -> T1) that will be executed
                 * when handler() or run_test() is called.
                 */
                ocf::func<T1(T2)> f;

            protected:
                /**
                 * @brief Executes the stored function with the given input and
                 *        provides exception handling.
                 *
                 * This function runs the stored function `f(input2)` and catches:
                 * - std::invalid_argument
                 * - std::length_error
                 * - std::exception
                 * - const char* (C-style error messages)
                 *
                 * All errors are reported to std::cerr.
                 *
                 * @param input2 The input value passed to the stored function.
                 *
                 * @note The return value of the function is currently ignored.
                 *       Use run_test() or modify handler() to return the result if needed.
                 */
                void handler(const T2 &input2)
                {
                    try
                    {
                        f(input2);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::cerr << "invalid argument: " << e.what() << std::endl;
                    }
                    catch (const std::length_error &e)
                    {
                        std::cerr << "length error: " << e.what() << std::endl;
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "Exception: " << e.what() << "\n";
                    }
                    catch (const char *msg)
                    {
                        std::cerr << "Error: " << msg << "\n";
                    }
                }

            public:
                stream__tp() = default;

                /**
                 * @brief Assigns a new unary transformation function to the stream.
                 *
                 * Example usage:
                 * @code
                 * stream__tp<int, double> s;
                 * s << [](double x) { return static_cast<int>(x * 2); };
                 * @endcode
                 *
                 * @param fx The function object to be stored.
                 */
                void operator<<(ocf::func<T1(T2)> fx) noexcept { f = fx; }
            
                /**
                 * @brief Extracts the stored function into another func.
                 *
                 * Example usage:
                 * @code
                 * ocf::func<int(double)> func;
                 * s >> func; // func now holds the stored function
                 * @endcode
                 *
                 * @param fx Reference to a function object where the stored function will be copied.
                 */
                void operator>>(ocf::func<T1(T2)> &fx) noexcept { fx = f; }
                
                /**
                 * @brief Executes the stored function safely with a given input.
                 *
                 * Example usage:
                 * @code
                 * double d = 3.14;
                 * s.run_test(d); // safely runs f(d)
                 * @endcode
                 *
                 * @param value2 Input value of type T2 passed to the stored function.
                 *
                 * @note The return value of the stored function is ignored.
                 */
                void run_test(const T2 &value2) { handler(value2); }
            };

            /**
             * @brief A template class that wraps a binary function (T2, T3 -> T1)
             *        and provides safe execution with built-in error handling.
             *
             * The stream__t_p class stores a function of type ocf::func<T1(T2, T3)>,
             * allowing transformation of two inputs (T2 and T3) into one output (T1).
             * It also provides exception handling for common errors.
             *
             * @tparam T1 The return type of the stored function.
             * @tparam T2 The first input type of the stored function.
             * @tparam T3 The second input type of the stored function.
             */
            template <typename T1, typename T2, typename T3>
            class stream__t_p
            {
            private:
                /**
                 * @brief Internal function storage.
                 *
                 * Holds the binary function (T2, T3 -> T1) that will be executed
                 * when handler() or run_test() is called.
                 */
                ocf::func<T1(T2, T3)> f;

            protected:
                /**
                 * @brief Executes the stored function with the given inputs and
                 *        provides exception handling.
                 *
                 * This function runs the stored function `f(input2, input3)` and catches:
                 * - std::invalid_argument
                 * - std::length_error
                 * - std::exception
                 * - const char* (C-style error messages)
                 *
                 * All errors are reported to std::cerr.
                 *
                 * @param input2 The first input value.
                 * @param input3 The second input value.
                 *
                 * @note The return value of the function is currently ignored.
                 *       Use run_test() or modify handler() to return the result if needed.
                 */
                void handler(const T2 &input2, const T3 &input3)
                {
                    try
                    {
                        f(input2, input3);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::cerr << "invalid argument: " << e.what() << std::endl;
                    }
                    catch (const std::length_error &e)
                    {
                        std::cerr << "length error: " << e.what() << std::endl;
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "Exception: " << e.what() << "\n";
                    }
                    catch (const char *msg)
                    {
                        std::cerr << "Error: " << msg << "\n";
                    }
                }

            public:
                stream__t_p() = default;

                /**
                 * @brief Assigns a new binary function to the stream.
                 *
                 * Example usage:
                 * @code
                 * stream__t_p<int, int, int> s;
                 * s << [](int a, int b) { return a + b; }; // stores addition function
                 * @endcode
                 *
                 * @param fx The function object to be stored.
                 */
                void operator<<(ocf::func<T1(T2, T3)> fx) noexcept { f = fx; }
                
                /**
                 * @brief Extracts the stored function into another func.
                 *
                 * Example usage:
                 * @code
                 * ocf::func<int(int,int)> func;
                 * s >> func; // func now holds the stored function
                 * @endcode
                 *
                 * @param fx Reference to a function object where the stored function will be copied.
                 */
                void operator>>(ocf::func<T1(T2, T3)> &fx) noexcept { fx = f; }
                
                /**
                 * @brief Executes the stored function safely with two inputs.
                 *
                 * Example usage:
                 * @code
                 * s.run_test(3, 4); // safely runs f(3, 4)
                 * @endcode
                 *
                 * @param value2 First input argument.
                 * @param value3 Second input argument.
                 *
                 * @note The return value of the stored function is ignored.
                 */
                void run_test(const T2 &value2, const T3 &value3) { handler(value2, value3); }
            };
        }
}
#endif // ETL___STREAM_HPP