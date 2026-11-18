/**
 * @file type.hpp
 * @brief This header file defines functions for getting type names as strings and checking types.
 * The functions are implemented in the corresponding CXXType.tpp file.
 * The type() function returns the name of the type as a string, while the is_*() functions check if a type matches a specific type.
 * The boolean_msg() function converts a boolean value to its string representation.
 * @note The type() function has a default implementation that returns "***" for any type that is not specialized.
 * @note The is_*() functions have a default implementation that returns false for any type that is not specialized.
 * @author Ali Lafi
 * @date 2025 / 9 / 25
 * @details This file is part of the MetaCore library, which provides various utilities for C++ programming.
 * - MetaCore/Lite/type.hpp: This header file declares the functions for type name retrieval and type checking.
 * - MetaCore/Lite/imp/type.tpp: This implementation
 * file defines the actual logic for the functions declared in CXXType.hpp, including specializations for common types and the boolean_msg() function.
 */

#include "cformat/types.h"

#pragma once
#ifndef ETL___TYPE_HPP
#define ETL___TYPE_HPP

namespace etl {
    /// @brief Get the type name as a string.
    /// @tparam T The type to get the name of.
    /// @return The name of the type as a string.
    template <typename T>
    inline ocf::str type() noexcept { return "unkown"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    inline ocf::str type<bool>() noexcept { return "bool"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    inline ocf::str type<char>() noexcept { return "char"; }

    template <>
    inline ocf::str type<unsigned char>() noexcept { return "unsigned char"; }

    template <>
    inline ocf::str type<ocf::byte>() noexcept { return "byte"; }

    template <>
    inline ocf::str type<ocf::ubyte>() noexcept { return "ubyte"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    inline ocf::str type<short>() noexcept { return "short"; }

    template <>
    inline ocf::str type<unsigned short>() noexcept { return "unsigned short"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    inline ocf::str type<int>() noexcept { return "int"; }

    template <>
    inline ocf::str type<unsigned int>() noexcept { return "unsigned int"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    inline ocf::str type<long>() noexcept { return "long"; }

    template <>
    inline ocf::str type<unsigned long>() noexcept { return "unsigned long"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    inline ocf::str type<long long>() noexcept { return "long long"; }

    template <>
    inline ocf::str type<unsigned long long>() noexcept { return "unsigned long long"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    inline ocf::str type<float>() noexcept { return "float"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    inline ocf::str type<double>() noexcept { return "double"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    inline ocf::str type<long double>() noexcept { return "long double"; }

    /// @brief Specializations for common types.
    /// @return The name of the type as a string.
    template <>
    inline ocf::str type<ocf::str>() noexcept { return "str"; }

    /// @brief Type checking functions.
    /// @tparam T the type to check.
    /// @return true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_bool() noexcept { return false; }

    /// @brief Specialization for bool type.
    /// @return true since T is bool.
    template <>
    inline constexpr bool is_bool<bool>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T the type to check.
    /// @return true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_char() noexcept { return false; }

    /// @brief specialization for char type.
    /// @return true since T is char.
    template <>
    inline constexpr bool is_char<char>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T the type to check.
    /// @return true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_short() noexcept { return false; }

    /// @brief specialization for short type.
    /// @return true since T is short.
    template <>
    inline constexpr bool is_short<short>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_int() noexcept { return false; }

    /// @brief specialization for int type.
    /// @return true since T is int.
    template <>
    inline constexpr bool is_int<int>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_float() noexcept { return false; }

    /// @brief specialization for float type.
    /// @return true since T is float.
    template <>
    inline constexpr bool is_float<float>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_double() noexcept { return false; }

    /// @brief Specialization for double type.
    /// @return true since T is double.
    template <>
    inline constexpr bool is_double<double>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_string() noexcept { return false; }

    /// @brief Specialization for inline ocf::str type.
    /// @return true since T is str.
    template <>
    inline constexpr bool is_string<ocf::str>() noexcept { return true; }

    /// @brief Type checking functions.
    /// @tparam T type of to check.
    /// @return the true if T matches the checked type, false otherwise.
    template <typename T>
    constexpr bool is_numeric() noexcept { return false; }

    /// @brief Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    inline constexpr bool is_numeric<short>() noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    inline constexpr bool is_numeric<int>() noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    inline constexpr bool is_numeric<long>() noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    inline constexpr bool is_numeric<long long>() noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    inline constexpr bool is_numeric<float>() noexcept { return true; }

    /// @brief Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    inline constexpr bool is_numeric<double>() noexcept { return true; }

    /// @brief  Specializations for numeric types.
    /// @return true since T is a numeric type.
    template <>
    inline constexpr bool is_numeric<long double>() noexcept { return true; }

    template <typename T>
    inline constexpr bool is_unsigned() noexcept { return false; }

    template <>
    inline constexpr bool is_unsigned<unsigned char>() noexcept { return true; }

    template <>
    inline constexpr bool is_unsigned<unsigned short>() noexcept { return true; }

    template <>
    inline constexpr bool is_unsigned<unsigned int>() noexcept { return true; }

    template <>
    inline constexpr bool is_unsigned<unsigned long>() noexcept { return true; }

    template <>
    inline constexpr bool is_unsigned<unsigned long long>() noexcept { return true; }

    template <>
    inline constexpr bool is_unsigned<ocf::ubyte>() noexcept { return true; }

    /// @brief Converts a boolean value to its string representation.
    /// @param value The boolean value to convert.
    /// @return The string representation of the boolean value.
    inline ocf::str boolean_msg(bool value) noexcept { return value ? "true" : "false"; }
}

#endif // ETL___TYPE_HPP