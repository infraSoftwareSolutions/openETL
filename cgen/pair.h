#include "micros.h"

#ifndef METACORE___CGEN___PAIR_H
#define METACORE___CGEN___PAIR_H

object {
    bool first;
    bool second;
} pair_bool;

object {
    char first;
    char second;
} pair_char;

object {
    short first;
    short second;
} pair_short;

object {
    int first;
    int second;
} pair_int;

object {
    float first;
    float second;
} pair_float;

object {
    double first;
    double second;
} pair_double;

object {
    long first;
    long second;
} pair_long;

object {
    size_t first;
    size_t second;
} pair_size_t;

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