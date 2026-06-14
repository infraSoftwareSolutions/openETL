#include "micros.h"

#ifndef METACORE___CGEN___PAIR_H
#define METACORE___CGEN___PAIR_H

#ifdef __cplusplus
#ifdef METACORE___META_HPP
namespace meta {
namespace cgen {
#endif // METACORE___META_HPP
#endif

cobject {
    bool first;
    bool second;
} pair_bool;

cobject {
    char first;
    char second;
} pair_char;

cobject {
    short first;
    short second;
} pair_short;

cobject {
    int first;
    int second;
} pair_int;

cobject {
    float first;
    float second;
} pair_float;

cobject {
    double first;
    double second;
} pair_double;

cobject {
    long first;
    long second;
} pair_long;

cobject {
    size_t first;
    size_t second;
} pair_size_t;

#ifdef __cplusplus
#ifdef METACORE___META_HPP
}}
#endif // METACORE___META_HPP
#endif

#define pair(type) _Generic((type) \
    bool: pair_bool,               \
    char: pair_char,               \
    short: pair_short,             \
    int: pair_int,                 \
    long: pair_long,               \
    size_t: pair_size_t,           \
    float: pair_float,             \
    double: pair_double)

#endif // METACORE___CGEN___PAIR_H