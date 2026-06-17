#include "cgen/micros/structure.h"

#pragma once
#ifndef METACORE___ADVA___SORT_HPP
#define METACORE___ADVA___SORT_HPP

#ifdef METACORE___META_HPP
namespace meta {
#endif // METACORE___META_HPP
#ifdef METACORE___ADVA___HPP
namespace adva {
#endif // METACORE___ADVA___HPP

bool is_sorted(const str& value) noexcept {
    if(value.empty()) return true;
    for(size_t i = 1; i < value.length(); i++) {
        if(value[i] < value[i - 1]) return false;
    }
    return true;
}

template<typename T>
bool is_sorted(const vec<T>& value) noexcept {
    if(value.empty()) return true;
    for(size_t i = 1; i < value.size(); i++) {
        if(value[i] < value[i - 1]) return false;
    }
    return true;
}

str bubble_sort(const str& value) noexcept;
template<typename T>
vec<T> bubble_sort(const vec<T>& value) noexcept;

str selection_sort(const str& value) noexcept;
template<typename T>
vec<T> selection_sort(const vec<T>& value) noexcept;

str comb_sort(const str& value) noexcept;
template<typename T>
vec<T> comb_sort(const vec<T>& value) noexcept;

str heap_sort(const str& value) noexcept;
template<typename T>
vec<T> heap_sort(const vec<T>& value) noexcept;

str insertion_sort(const str& value) noexcept;
template<typename T>
vec<T> insertion_sort(const vec<T>& value) noexcept;

str merge_sort(const str& value) noexcept;
template<typename T>
vec<T> merge_sort(const vec<T>& value) noexcept;

str quick_sort(const str& value) noexcept;
template<typename T>
vec<T> quick_sort(const vec<T>& value) noexcept;

#ifdef METACORE___ADVA___HPP
}
#endif // METACORE___ADVA___HPP
#ifdef METACORE___META_HPP
}
#endif // METACORE___META_HPP

#endif // METACORE___ADVA___SORT_HPP