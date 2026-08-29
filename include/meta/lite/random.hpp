/**
 * @file random.hpp
 * @brief A collection of functions for generating random numbers, characters, and vectors, as well
 * as performing simple shift encryption on strings. These functions utilize the Mersenne Twister
 * algorithm for random number generation and provide both simple and complex encryption methods.
 * @note All functions are designed to be noexcept, ensuring they do not throw exceptions.
 * @details
 * - GRN: Generates a random integer within a specified range.
 * - SES: Encrypts a string by shifting all characters by the same randomly generated key.
 * - SEC: Encrypts a string by shifting each character by a different randomly generated key.
 * - GRC: Generates a random printable ASCII character.
 * - GRV: Generates vectors of random integers, with support for 1D, 2D, and 3D vectors.
 * - GRCV: Generates a vector of random printable ASCII characters.
 * - GRC2DV: Generates a 2D vector of random printable ASCII characters.
 * - GRC3DV: Generates a 3D vector of random printable ASCII characters.
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 */

#include <vector>
#include <string>
#include <random>
#include "cfrost/structure.h"


#pragma once
#ifndef METACORE___LITE___RANDOM_HPP
#define METACORE___LITE___RANDOM_HPP

namespace meta {

    namespace lite {

        // GRN: generate random number
        /// @brief Generates a random integer within the specified range using Mersenne Twister algorithm.
        /// @param start The lower bound of the range (inclusive).
        /// @param end The upper bound of the range (inclusive).
        /// @return A random integer between start and end (inclusive).
        /// @note Uses a static random generator initialized once per program execution.
        /// @noexcept Does not throw exceptions.
        int GRN(int start, int end) noexcept
        {
            static std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<> dis(start, end);
            return dis(gen);
        }
        
        // GRC: generate random char
        /// @brief Generates a random printable ASCII character.
        /// @return A random character in the range of printable ASCII characters (32 to 126)
        char GRC() noexcept { return static_cast<char>(GRN(32, 126)); }

        // GRV: generate random vector
        /// @brief Generates a vector of random integers within the specified range.
        /// @param ele_num The number of elements in the vector.
        /// @param start The lower bound of the range (inclusive).
        /// @param end The upper bound of the range (inclusive).
        /// @return A vector containing ele_num random integers between start and end (inclusive).
        ocf::vec<int> GRV(size_t ele_num, int start, int end) noexcept
        {
            ocf::vec<int> result;
            for (size_t i = 0; i < ele_num; i++)
                result.push_back(GRN(start, end));
            return result;
        }

        /// @brief Generates a 2D vector of random integers within the specified range.
        /// @param vec_num The number of vectors in the 2D vector.
        /// @param ele_num The number of elements in each vector.
        /// @param start The lower bound of the range (inclusive).
        /// @param end The upper bound of the range (inclusive).
        /// @return A 2D vector containing vec_num vectors, each with ele_num random integers between start and end (inclusive).
        ocf::vec<ocf::vec<int>> GRV(size_t vec_num, size_t ele_num, int start, int end) noexcept
        {
            ocf::vec<ocf::vec<int>> result;
            for (size_t i = 0; i < vec_num; i++)
                result.push_back(GRV(ele_num, start, end));
            return result;
        }

        /// @brief Generates a 3D vector of random integers within the specified range.
        /// @param vv_num The number of 2D vectors in the 3D vector
        /// @param vec_num The number of vectors in each 2D vector.
        /// @param ele_num The number of elements in each vector.
        /// @param start The lower bound of the range (inclusive).
        /// @param end The upper bound of the range (inclusive).
        /// @return A 3D vector containing vv_num 2D vectors, each with
        ocf::vec<ocf::vec<ocf::vec<int>>> GRV(size_t vv_num, size_t vec_num, size_t ele_num, int start, int end) noexcept
        {
            ocf::vec<ocf::vec<ocf::vec<int>>> result;
            for (size_t i = 0; i < vv_num; i++)
                result.push_back(GRV(vec_num, ele_num, start, end));
            return result;
        }

        // vector_cast: cast vector type
        // GRCV: generaterandom char vector
        /// @brief Generates a vector of random printable ASCII characters.
        /// @return A vector containing random characters in the range of printable ASCII characters (32 to 126).
        ocf::vec<char> GRCV() noexcept {
            ocf::vec<int> temp = GRV(94, 32, 126);
            ocf::vec<char> result;
            for(size_t i = 0; i < 94; i++)
                result.push_back(static_cast<char>(temp[i]));
            return result;
        }

        // GRC2DV: generate random char 2d vector
        /// @brief Generates a 2D vector of random printable ASCII characters.
        /// @return A 2D vector containing random characters in the range of printable ASCII characters
        ocf::vec<ocf::vec<char>> GRC2DV() noexcept {
            ocf::vec<ocf::vec<char>> result;
            for(size_t i = 0; i < 94; i++)
                result.push_back(GRCV());
            return result;
        }

        // GRC3DV: generate random char 3d vector
        /// @brief Generates a 3D vector of random printable ASCII characters.
        /// @return A 3D vector containing random characters in the range of printable ASCII characters
        ocf::vec<ocf::vec<ocf::vec<char>>> GRC3DV() noexcept {
            ocf::vec<ocf::vec<ocf::vec<char>>> result;
            for(size_t i = 0; i < 94; i++)
                result.push_back(GRC2DV());
            return result;
        }

    }

}

#endif // METACORE___LITE___RANDOM_HPP