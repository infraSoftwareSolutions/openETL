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
#include "cformat/structure.h"

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
        std::queue<std::vector<T>> vs;

    public:
        /** Default constructor */
        vstream() = default;
        
        /** Constructor from vec
         * @param vec The vector to initialize the stream with
         * @note This constructor copies the vector
         */
        vstream(const std::queue<std::vector<T>> &_vec) noexcept : vs(_vec) {}
        
        /** Constructor from rvalue vec
         * @param vec The vector to initialize the stream with
         * @note This constructor moves the vector
         */
        vstream(std::queue<std::vector<T>> &&_vec) noexcept : vs(std::move(_vec)) {}
        
        /**
         * Constructor from initializer list
         * @param il The initializer list to initialize the stream with
         * @note This constructor copies the elements from the initializer list
         */
        vstream(std::initializer_list<std::vector<T>> il) noexcept : vs(il) {}
        
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
        void operator=(const std::queue<std::vector<T>> &vec) noexcept { vs = vec; }

        /**
         * @brief Move assignment operator from a vec<T>.
         *
         * Replaces the contents of the internal vector 'vs' with those of the given rvalue reference 'vec',
         * transferring ownership of the data without copying.
         *
         * @param vec Rvalue reference to a vec<T> whose contents will be moved.
         * @note This operation is noexcept and leaves 'vec' in a valid but unspecified state.
         */
        void operator=(std::queue<std::vector<T>> &&vec) noexcept { vs = std::move(vec); }

        /**
         * @brief Assignment operator for assigning an initializer list to the container.
         *
         * Replaces the contents of the container with the elements from the given initializer list.
         * This operation is noexcept.
         *
         * @param il The initializer list whose elements will be assigned to the container.
         */
        void operator=(std::initializer_list<std::vector<T>> il) noexcept { vs = il; }

        /**
         * @brief Inserts a value into the vector stream.
         *
         * This operator overload allows vectors of type T to be enqueued to the internal queue (vs)
         * using the stream insertion syntax.
         *
         * @param value The vector to be inserted into the queue stream.
         * @note This operation does not support chaining as it returns void.
         */
        void operator<<(const std::vector<T> &value) noexcept { vs.push(value); }

        /**
         * @brief Inserts a value into the vector stream using move semantics.
         *
         * This operator overload allows an rvalue reference of type vec<T> to be moved
         * into the internal queue (vs), which improves performance by avoiding unnecessary copies.
         *
         * @param value The rvalue reference to the vector to be inserted.
         * @note This operation does not support chaining as it returns void.
         */
        void operator<<(std::vector<T> &&value) noexcept { vs.push(std::move(value)); }

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
        void operator>>(std::vector<T> &value)
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
        std::string split_str;
        std::queue<std::string> ss;
        public:

        sstream() noexcept : split(false), split_str(""), ss(std::queue<std::string>()) {};
        sstream(const std::queue<std::string> &strVal) noexcept : split(false), split_str(""), ss(strVal) {}
        sstream(const std::string &ssplit) noexcept : split(true), split_str(ssplit), ss(std::queue<std::string>()) {}
        sstream(bool isSplit) noexcept : split(isSplit), split_str(""), ss(std::queue<std::string>()) {}

        void set_split(bool isSplit) noexcept { split = isSplit; }
        void set_split_str(const std::string &ssplit) noexcept { split_str = ssplit; }
        
        void operator<<(const std::string &value) noexcept {
            if (split && !split_str.empty()) {
                size_t start = 0;
                size_t end = value.find(split_str);
                while (end != std::string::npos) {
                    ss.push(value.substr(start, end - start));
                    start = end + split_str.length();
                    end = value.find(split_str, start);
                }
                ss.push(value.substr(start));
            } else {
                ss.push(value);
            }
        }

        void operator>>(std::string &value) {
            if (!ss.empty()) {
                value = ss.front();
                ss.pop();
            } else {
                throw std::out_of_range("sstream is empty");
            }
        }
    };
}
#endif // ETL___STREAM_HPP