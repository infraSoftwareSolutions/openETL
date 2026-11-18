/**
 * @file benchmark.hpp
 * @brief A lightweight code execution timer and memory usage measurement utility.
 * @brief this library provides a lightweight code execution timer utility.
 * It includes the `code_timer` class, which can be used in two modes:
 * RAII mode (in_structure = true): Automatically starts timing upon construction and stops timing upon destruction, printing the duration in milliseconds.
 * Manual mode (in_structure = false): Requires explicit calls to start_time() and stop_time(), with get_duration() to retrieve the result.
 * Additionally, it provides several overloaded execution_time functions to measure the execution time of parameterless functions, single-argument functions, and two-argument functions with different types.
 * The library also includes functions to simulate various time complexities (O(1), O(log n), O(n), O(n log n), O(n^2), O(n^3)) and a function to estimate the time complexity of an algorithm based on measured execution time.
 * Finally, it offers functions to calculate the size of an object in bytes and to measure additional memory usage caused by executing functions.
 * Overall, this library is designed to help developers easily measure and analyze the performance of their code in terms of execution time and memory usage.
 * @author developed by: Ali Lafi.
 * @date 2025 / 9 / 25
 * @details This library is designed to help developers easily measure and analyze the performance of their code in terms of execution time and memory usage.
 * It provides a simple interface for timing code execution and estimating time complexity, making it a useful tool for benchmarking and optimizing C++ code.
 * The `code_timer` class can be used in both RAII and manual modes, allowing for flexible timing of code blocks or specific function calls.
 * The additional functions for simulating time complexities and measuring memory usage further enhance its utility for performance analysis. Overall,
 * - code_timer: A class for timing code execution, with both RAII and manual modes.
 * - execution_time: Overloaded functions to measure execution time of various types of callables.
 * - big_O1, logn, big_On, logn_n, big_On2, big_On3: functions to simulate different time complexities.
 * - execution_type: A function to estimate the time complexity of an algorithm based on measured execution time.
 * - mata_data: A function to return the size of an object in bytes.
 * - heap_data: Overloaded functions to calculate the heap memory used by vectors and strings.
 * - function_data and function__data: functions to measure additional memory usage caused by executing callables.
 * @note This library is designed for benchmarking code performance in C++23 and is part of
 * it's a part of the lite library, specifically within the lite module, and is intended for benchmarking code performance in C++23.
 */

#include <chrono>
#include <thread>
#include <vector>
#include <functional>
#include <string>
#include <stdexcept>
#include <exception>
#include <windows.h>
#include <psapi.h>
#include <memory>
#include <algorithm>

#include "cformat/structure.h"
#include "cformat/types.h"

#pragma once
#ifndef ETL___BENCHMARK_HPP
#define ETL___BENCHMARK_HPP

namespace etl {
    namespace benchmark
    {
        /**
         * @brief A lightweight code execution timer utility.
         *
         * The `code_timer` class can be used to measure execution time in two modes:
         *
         * 1. **RAII mode (`in_structure = true`)**:
         *    - Starts timing automatically upon construction.
         *    - Stops timing and prints duration (in milliseconds) automatically
         *      upon destruction.
         *    - No need to call `start_time()` or `stop_time()`.
         *
         * 2. **Manual mode (`in_structure = false`)**:
         *    - Requires explicit calls to `start_time()` and `stop_time()`.
         *    - `get_duration()` can be used after `stop_time()` to retrieve the result.
         *
         * @tparam in_structure A compile-time boolean flag:
         *         - `true`: RAII automatic mode.
         *         - `false`: manual start/stop mode.
         *
         * Example usage:
         * @code
         * {
         *     // RAII mode: automatically times this scope
         *     code_timer<true> t;
         *     // some heavy code...
         * }
         * // Prints: time code duration: X ms
         *
         * {
         *     // Manual mode
         *     code_timer<false> t;
         *     t.start_time();
         *     // some heavy code...
         *     t.stop_time();
         *     std::cout << "manual duration: " << t.get_duration() * 1000.0f << " ms\n";
         * }
         * @endcode
         */
        template <bool in_structure>
        class code_timer
        {
        private:
            bool started = false;
            std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
            std::chrono::duration<float> mycodetime;

        public:
            /// @brief Constructor.
            /// Starts timing if RAII mode is enabled.
            code_timer()
            {
                if constexpr (in_structure)
                    start = std::chrono::high_resolution_clock::now();
            }
            
            /// @brief Returns the last measured duration in seconds.
            inline constexpr float get_duration() const noexcept { return mycodetime.count(); }
            
            /// @brief Start timing (only valid in manual mode).
            inline void start_time()
            {
                if constexpr (in_structure)
                    throw std::logic_error("RAII mode: timer is running by default");
                start = std::chrono::high_resolution_clock::now();
                started = true;
            }

            /// @brief Stop timing (only valid in manual mode).
            inline void stop_time()
            {
                if constexpr (in_structure)
                    throw std::logic_error("RAII mode: timer is running by default");
                if (!started)
                    throw std::logic_error("Timer is not running");
                end = std::chrono::high_resolution_clock::now();
                mycodetime = end - start;
                started = false;
            }

            /// @brief Destructor.
            /// In RAII mode, prints the measured duration.
            ~code_timer()
            {
                if constexpr (in_structure)
                {
                    end = std::chrono::high_resolution_clock::now();
                    mycodetime = end - start;
                }
            }
        };

        /**
         * @brief Measure the execution time of a parameterless function.
         *
         * This function takes a callable object (e.g., lambda, input_functor, function pointer)
         * with no parameters, executes it once, and measures the duration of its execution
         * using @ref code_timer in manual mode.
         *
         * @tparam T Return type of the function.
         * @param input_func A ocf::func<T()> representing the callable to measure.
         * @return Execution time in seconds as a floating-point value.
         *
         * @note The measured duration is in seconds. Multiply by 1000.0f if milliseconds
         *       are desired.
         *
         * Example usage:
         * @code
         * auto duration = execution_time<void>([]() {
         *     heavy_computation();
         * });
         * std::cout << "Duration: " << duration * 1000.0f << " ms\n";
         * @endcode
         */
        template <typename T>
        float execution_time(ocf::func<T()> input_func)
        {
            code_timer<false> timer;
            timer.start_time();
            input_func();
            timer.stop_time();
            return timer.get_duration();
        }

        /**
         * @brief Measure the execution time of a single-argument function.
         *
         * This overload takes a callable object that accepts a single argument,
         * executes it once with the provided value, and measures the duration
         * of its execution using @ref code_timer in manual mode.
         *
         * @tparam T The type of both the argument and return value of the function.
         * @param input_func A ocf::func<T(T)> representing the callable to measure.
         * @param arg The argument to pass to the function.
         * @return Execution time in seconds as a floating-point value.
         *
         * @note The measured duration is in seconds. Multiply by 1000.0f if milliseconds
         *       are desired.
         *
         * Example usage:
         * @code
         * auto duration = execution_time<int>([](int x) {
         *     return fibonacci(x);
         * }, 30);
         *
         * std::cout << "Duration: " << duration * 1000.0f << " ms\n";
         * @endcode
         */
        template <typename T>
        float execution_time(ocf::func<T(T)> input_func, T arg)
        {
            code_timer<false> timer;
            timer.start_time();
            input_func(arg);
            timer.stop_time();
            return timer.get_duration();
        }

        /**
         * @brief Measure the execution time of a function taking two arguments of the same type.
         *
         * Executes the provided callable with two arguments of type @p T2 and
         * measures its execution duration using @ref code_timer in manual mode.
         *
         * @tparam T1 Return type of the function.
         * @tparam T2 Argument type of the function (both arguments are the same type).
         * @param input_func A ocf::func<T1(T2, T2)> representing the callable to measure.
         * @param arg1 First argument to pass to the function.
         * @param arg2 Second argument to pass to the function.
         * @return Execution time in seconds as a floating-point value.
         *
         * @example
         * @code
         * auto duration = execution_time<int, int>([](int a, int b) {
         *     return a + b;
         * }, 10, 20);
         *
         * std::cout << "Duration: " << duration * 1000.0f << " ms\n";
         * @endcode
         */
        template <typename T1, typename T2>
        float execution_time(ocf::func<T1(T2, T2)> input_func, T2 arg1, T2 arg2)
        {
            code_timer<false> timer;
            timer.start_time();
            input_func(arg1, arg2);
            timer.stop_time();
            return timer.get_duration();
        }

        /**
         * @brief Measure the execution time of a single-argument function.
         *
         * Executes the provided callable with one argument of type @p T2 and
         * measures its execution duration using @ref code_timer in manual mode.
         *
         * @tparam T1 Return type of the function.
         * @tparam T2 Argument type of the function.
         * @param input_func A ocf::func<T1(T2)> representing the callable to measure.
         * @param arg Argument to pass to the function.
         * @return Execution time in seconds as a floating-point value.
         *
         * @example
         * @code
         * auto duration = execution__time<int, int>([](int x) {
         *     return x * x;
         * }, 42);
         *
         * std::cout << "Duration: " << duration * 1000.0f << " ms\n";
         * @endcode
         */
        template <typename T1, typename T2>
        float execution__time(ocf::func<T1(T2)> input_func, T2 arg)
        {
            code_timer<false> timer;
            timer.start_time();
            input_func(arg);
            timer.stop_time();
            return timer.get_duration();
        }

        /**
         * @brief Measure the execution time of a two-argument function with different types.
         *
         * Executes the provided callable with arguments of types @p T2 and @p T3,
         * and measures its execution duration using @ref code_timer in manual mode.
         *
         * @tparam T1 Return type of the function.
         * @tparam T2 Type of the first argument.
         * @tparam T3 Type of the second argument.
         * @param input_func A ocf::func<T1(T2, T3)> representing the callable to measure.
         * @param arg1 First argument to pass to the function.
         * @param arg2 Second argument to pass to the function.
         * @return Execution time in seconds as a floating-point value.
         *
         * @example
         * @code
         * auto duration = execution__time<str, int, double>(
         *     [](int a, double b) {
         *         return std::to_string(a + static_cast<int>(b));
         *     },
         *     5, 3.7
         * );
         *
         * std::cout << "Duration: " << duration * 1000.0f << " ms\n";
         * @endcode
         */
        template <typename T1, typename T2, typename T3>
        float execution__time(ocf::func<T1(T2, T3)> input_func, T2 arg1, T3 arg2)
        {
            code_timer<false> timer;
            timer.start_time();
            input_func(arg1, arg2);
            timer.stop_time();
            return timer.get_duration();
        }

        /**
         * @brief A collection of simple functions to simulate various time complexities.
         *
         * These functions are used internally to compare execution durations and
         * determine the likely time complexity of an algorithm.
         */
        /** Constant time complexity O(1). */
        void big_O1() noexcept { return; }

        /** Logarithmic time complexity O(log n).
         *  Sleeps for duration proportional to log(num). */
        void logn(size_t num, int n) noexcept
        {
            int iterations = 0;
            size_t temp = num;
            while (temp > 0) {
                temp /= n;
                iterations++;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(iterations));
        }

        /** Linear time complexity O(n).
         *  Sleeps for duration proportional to num. */
        void big_On(size_t num) noexcept
        {
            std::this_thread::sleep_for(std::chrono::microseconds(num));
        }

        /** Linearithmic time complexity O(n log n).
         *  Sleeps for duration proportional to n * log(n). */
        void logn_n(size_t num, int n) noexcept
        {
            int log_iterations = 0;
            int temp = num;
            while (temp > 0) {
                temp /= n;
                log_iterations++;
            }
            size_t sleep_duration = num * log_iterations;
            std::this_thread::sleep_for(std::chrono::microseconds(sleep_duration));
        }

        /** Quadratic time complexity O(n^2). */
        void big_On2(size_t num) noexcept
        {
            size_t sleep_duration = num * num;
            std::this_thread::sleep_for(std::chrono::microseconds(sleep_duration));
        }

        /** Cubic time complexity O(n^3). */
        void big_On3(size_t num) noexcept
        {
            size_t sleep_duration = num * num * num;
            std::this_thread::sleep_for(std::chrono::microseconds(sleep_duration));
        }

        /**
         * @brief Estimate the time complexity of an algorithm based on measured execution time.
         *
         * This function compares the provided execution time against predefined
         * time benchmarks for standard complexities: O(1), O(log n), O(n), O(n log n),
         * O(n^2), O(n^3), and higher exponential or factorial complexities.
         *
         * @param time Measured execution time in seconds.
         * @param num Input size used in the benchmark functions.
         * @param logbase Base for logarithmic calculations (default: 10).
         * @return A string representing the estimated time complexity.
         *
         * @example
         * @code
         * float t = 0.0023f;  // measured execution time
         * int n = 1000;       // input size
         * ocf::str complexity = execution_type(t, n);
         * std::cout << "Estimated complexity: " << complexity << "\n";
         * @endcode
         */
        ocf::str execution_type(float time, int num, int logbase = 10) noexcept
        {
            ocf::func<void()> O1 = big_O1;
            ocf::func<void(size_t, int)> log_n = logn;
            ocf::func<void(size_t)> On = big_On;
            ocf::func<void(size_t, int)> log_n_n = logn_n;
            ocf::func<void(size_t)> On2 = big_On2;
            ocf::func<void(size_t)> On3 = big_On3;
            if (time < execution_time<void>(O1))
                return "O(1)";
            else if (time < execution__time<void, size_t, int>(log_n, static_cast<size_t>(num), logbase))
                return "O(log n)";
            else if (time < execution__time<void, size_t>(On, static_cast<size_t>(num)))
                return "O(n)";
            else if (time < execution__time<void, size_t, int>(log_n_n, static_cast<size_t>(num), logbase))
                return "O(n log n)";
            else if (time < execution__time<void, size_t>(On2, static_cast<size_t>(num)))
                return "O(n^2)";
            else if (time < execution__time<void, size_t>(On3, static_cast<size_t>(num)))
                return "O(n^3)";
            else
                return "O(2^n) or O(n!)";
        }

        /**
         * @brief Returns the size of an object in bytes.
         *
         * This function calculates the compile-time size of any object
         * using sizeof.
         *
         * @tparam T Type of the object.
         * @param object Reference to the object.
         * @return Size of the object in bytes.
         *
         * @note This only accounts for the object's immediate size in memory,
         *       not dynamically allocated data (heap).
         */
        template <typename T>
        constexpr size_t mata_data(T & _object) noexcept { return sizeof(_object); }

        /**
         * @brief Returns the heap memory used by a vector.
         *
         * Calculates the memory allocated on the heap for a ocf::vec
         * based on its capacity and element size.
         *
         * @tparam T Type of elements in the vector.
         * @param v Reference to the vector.
         * @return Heap memory in bytes.
         */
        template <typename T>
        constexpr size_t heap_data(const ocf::vec<T> &v) noexcept { return sizeof(T) * v.capacity(); }

        /**
         * @brief Returns the heap memory used by a 2D vector.
         *
         * Calculates the memory allocated on the heap for a ocf::vec of ocf::vec
         * based on its capacity and element size.
         *
         * @tparam T Type of elements in the inner vectors.
         * @param v2d Reference to the 2D vector.
         * @return Heap memory in bytes.
         */
        template <typename T>
        constexpr size_t heap_data(const ocf::vec<ocf::vec<T>> &v2d) noexcept
        {
            size_t result = 0;
            for (const ocf::vec<T> &v : v2d)
                result += heap_data(v);
            return result;
        }

        /**
         * @brief Returns the heap memory used by a 3D vector.
         *
         * Calculates the memory allocated on the heap for a ocf::vec of ocf::vec of ocf::vec
         * based on its capacity and element size.
         *
         * @tparam T Type of elements in the innermost vectors.
         * @param v3d Reference to the 3D vector.
         * @return Heap memory in bytes.
         */
        template <typename T>
        constexpr size_t heap_data(const ocf::vec<ocf::vec<ocf::vec<T>>> &v3d) noexcept
        {
            size_t result = 0;
            for (const ocf::vec<ocf::vec<T>> &v2d : v3d)
                for (const ocf::vec<T> &v : v2d)
                    result += heap_data(v);
            return result;
        }

        /**
         * @brief Returns the heap memory used by a str.
         *
         * Calculates the memory allocated on the heap based on the string's capacity.
         *
         * @param s Reference to the string.
         * @return Heap memory in bytes.
         */
        size_t heap_data(const ocf::str &s) noexcept { return sizeof(char) * s.capacity(); }

        /**
         * @brief Measures additional memory usage caused by executing a parameterless function.
         *
         * The function checks the process's working set before and after execution
         * and returns the difference in memory usage.
         *
         * @tparam T Return type of the function.
         * @param f function to execute.
         * @return Additional memory used in bytes (0 if no increase).
         */
        template <typename T>
        size_t function_data(ocf::func<T()> f)
        {
            PROCESS_MEMORY_COUNTERS info1, info2;
            GetProcessMemoryInfo(GetCurrentProcess(), &info1, sizeof(info1));
            f();
            GetProcessMemoryInfo(GetCurrentProcess(), &info2, sizeof(info2));
            if (info2.WorkingSetSize > info1.WorkingSetSize)
                return info2.WorkingSetSize - info1.WorkingSetSize;
            else
                return 0;
        }

        /**
         * @brief Measures additional memory usage caused by executing a single-argument function.
         *
         * The function checks the process's working set before and after execution
         * and returns the difference in memory usage.
         *
         * @tparam T Return type and argument type of the function.
         * @param f function to execute.
         * @param input Argument to pass to the function.
         * @return Additional memory used in bytes (0 if no increase).
         */
        template <typename T>
        size_t function_data(ocf::func<T(T)> f, T input)
        {
            PROCESS_MEMORY_COUNTERS info1, info2;
            GetProcessMemoryInfo(GetCurrentProcess(), &info1, sizeof(info1));
            f(input);
            GetProcessMemoryInfo(GetCurrentProcess(), &info2, sizeof(info2));
            if (info2.WorkingSetSize > info1.WorkingSetSize)
                return info2.WorkingSetSize - info1.WorkingSetSize;
            else
                return 0;
        }

        /**
         * @brief Measures additional memory usage caused by executing a single-argument function.
         *
         * Overload with template parameters T1 and T2.
         *
         * @tparam T1 Return type of the function.
         * @tparam T2 Argument type of the function.
         * @param f function to execute.
         * @param input Argument to pass to the function.
         * @return Additional memory used in bytes (0 if no increase).
         */
        template <typename T1, typename T2>
        size_t function__data(ocf::func<T1(T2)> f, T2 input)
        {
            PROCESS_MEMORY_COUNTERS info1, info2;
            GetProcessMemoryInfo(GetCurrentProcess(), &info1, sizeof(info1));
            f(input);
            GetProcessMemoryInfo(GetCurrentProcess(), &info2, sizeof(info2));
            if (info2.WorkingSetSize > info1.WorkingSetSize)
                return info2.WorkingSetSize - info1.WorkingSetSize;
            else
                return 0;
        }

        /**
         * @brief Measures additional memory usage caused by executing a two-argument function.
         *
         * The function checks the process's working set before and after execution
         * and returns the difference in memory usage.
         *
         * @tparam T1 Return type of the function.
         * @tparam T2 Type of the first argument.
         * @tparam T3 Type of the second argument.
         * @param f function to execute.
         * @param input1 First argument to pass to the function.
         * @param input2 Second argument to pass to the function.
         * @return Additional memory used in bytes (0 if no increase).
         */
        template <typename T1, typename T2, typename T3>
        size_t function__data(ocf::func<T1(T2, T3)> f, T2 input1, T3 input2)
        {
            PROCESS_MEMORY_COUNTERS info1, info2;
            GetProcessMemoryInfo(GetCurrentProcess(), &info1, sizeof(info1));
            f(input1, input2);
            GetProcessMemoryInfo(GetCurrentProcess(), &info2, sizeof(info2));
            if (info2.WorkingSetSize > info1.WorkingSetSize)
                return info2.WorkingSetSize - info1.WorkingSetSize;
            else
                return 0;
        }

        /**
         * @brief A template class for benchmarking function execution time.
         *       The stream class allows users to measure the execution time
         *      of functions and optionally print the results.
         * @tparam print_result A boolean flag indicating whether to print
         *      the execution time for each test case.
         */
        template <bool print_result>
        class stream
        {
        private:
            size_t count = 1;
            ocf::str s = "s";
            long long factor = 1;
            ocf::vec<float> time_v;
            ocf::vec<ocf::str> test_names;
            float min_time = std::numeric_limits<float>::max();
            float max_time = std::numeric_limits<float>::min();

        protected:
            /**
             * @brief Calculates the arithmetic mean of stored time values
             * @return Float value representing the average of all times in time_v
             *
             * Computes the average by summing all time values and dividing by the count of entries.
             * Returns 0.0f if the vector is empty.
             */
            float average()
            {
                float result = 0.0f;
                for (float time : time_v)
                    result += time;
                return result / time_v.size();
            }

        public:
            /**
             * @brief Constructor for benchmark_stream that sets time measurement units
             *
             * @param TFactor String representing the time unit to use. Valid values are:
             *                "s"  - seconds
             *                "ms" - milliseconds
             *                "us" - microseconds
             *                "ns" - nanoseconds
             *                "ps" - picoseconds
             *
             * @throws std::invalid_argument if TFactor is not one of the valid time units
             *
             * @details Sets the appropriate multiplication factor based on the time unit:
             *          s  = 10^0  = 1
             *          ms = 10^3  = 1,000
             *          us = 10^6  = 1,000,000
             *          ns = 10^9  = 1,000,000,000
             *          ps = 10^12 = 1,000,000,000,000
             */
            stream(ocf::str TFactor)
            {
                if (TFactor == "s")
                {
                    factor = 1;
                    s = "s";
                }
                else if (TFactor == "ms")
                {
                    factor = std::pow(10, 3);
                    s = TFactor;
                }
                else if (TFactor == "us")
                {
                    factor = std::pow(10, 6);
                    s = TFactor;
                }
                else if (TFactor == "ns")
                {
                    factor = std::pow(10, 9);
                    s = TFactor;
                }
                else if (TFactor == "ps")
                {
                    factor = std::pow(10, 12);
                    s = TFactor;
                }
                else
                    throw std::invalid_argument("The size of the time is not defind");
            }

            /**
             * @brief Constructor for benchmark_stream that sets time unit scaling and suffix
             * @param n Power of 10 to scale time measurements (default = 3)
             *
             * Sets the scaling factor as 10^n and corresponding time unit suffix:
             * - n=1: seconds (s)
             * - n=3: milliseconds (ms)
             * - n=6: microseconds (us)
             * - n=9: nanoseconds (ns)
             * - n=12: picoseconds (ps)
             * - other: custom (xs)
             */
            stream(short n = 3)
            {
                factor = std::pow(10, n);
                if (n == 1)
                    s = "s";
                else if (n == 3)
                    s = "ms";
                else if (n == 6)
                    s = "us";
                else if (n == 9)
                    s = "ns";
                else if (n == 12)
                    s = "ps";
                else
                    s = "xs";
            }

            /**
             * @brief Overloaded stream operator to benchmark and record execution time of a function
             * @param fx Function to benchmark, must be callable and return bool
             * @details
             * - Executes the given function and records its execution time
             * - If print_result is enabled, prints the execution time for the test
             * - Increments internal test counter
             * - Time values are stored in time_v vector
             * - Results are printed with test number and scaled time (factor * measured_time)
             * @throws noexcept This function does not throw exceptions
             */
            void operator<<(ocf::func<bool()> fx) noexcept
            {
                time_v.push_back(benchmark::execution_time<bool>(fx));
                float current_time = factor * time_v[count - 1];
                min_time = std::min(min_time, current_time);
                max_time = std::max(max_time, current_time);
                if (print_result)
                    io::println(
                        "execution time for unit test " +
                        std::to_string(count) + ": " +
                        std::to_string(current_time) + s);
                count++;
            }

            /// @brief Overloaded stream operator to retrieve average execution time
            /// @param value Reference to float variable to store average execution time
            void operator>>(float &value) noexcept { value = factor * average(); }

            /**
             * @brief Retrieves the minimum recorded execution time
             * @return Minimum time in the specified unit
             */
            float get_min_time() const noexcept { return min_time; }

            /**
             * @brief Retrieves the maximum recorded execution time
             * @return Maximum time in the specified unit
             */
            float get_max_time() const noexcept { return max_time; }

            /**
             * @brief Retrieves the average execution time
             * @return Average time in the specified unit
             */
            float get_average_time() const noexcept { return factor * average(); }

            /**
             * @brief Retrieves the total number of benchmarked tests
             * @return Number of test cases executed
             */
            size_t get_test_count() const noexcept { return count - 1; }

            /**
             * @brief Clears all benchmark records and resets statistics
             */
            void clear_statistics() noexcept
            {
                time_v.clear();
                test_names.clear();
                count = 1;
                min_time = std::numeric_limits<float>::max();
                max_time = std::numeric_limits<float>::min();
            }

            /**
             * @brief Prints a complete benchmark summary with statistics
             */
            void print_summary() const noexcept
            {
                if (time_v.empty())
                {
                    io::println("No benchmark data available");
                    return;
                }
                io::println("=== Benchmark Summary ===");
                io::println("Total tests: " + std::to_string(time_v.size()));
                io::println("Average time: " + std::to_string(get_average_time()) + s);
                io::println("Min time: " + std::to_string(min_time) + s);
                io::println("Max time: " + std::to_string(max_time) + s);
            }
        };
    }
}
#endif // ETL___BENCHMARK_HPP