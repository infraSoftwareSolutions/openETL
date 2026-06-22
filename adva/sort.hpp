#include <vector>
#include <string>

#pragma once
#ifndef METACORE___ADVA___SORT_HPP
#define METACORE___ADVA___SORT_HPP

namespace meta {
    namespace adva {
        
        bool is_sorted(const std::string& value) noexcept {
            if(value.empty()) return true;
            for(size_t i = 1; i < value.length(); i++) {
                if(value[i] < value[i - 1]) return false;
            }
            return true;
        }

        template<typename T>
        bool is_sorted(const std::vector<T>& value) noexcept {
            if(value.empty()) return true;
            for(size_t i = 1; i < value.size(); i++) {
                if(value[i] < value[i - 1]) return false;
            }
            return true;
        }

        std::string bubble_sort(const std::string& value) noexcept;
        template<typename T>
        std::vector<T> bubble_sort(const std::vector<T>& value) noexcept;

        std::string selection_sort(const std::string& value) noexcept;
        template<typename T>
        std::vector<T> selection_sort(const std::vector<T>& value) noexcept;

        std::string comb_sort(const std::string& value) noexcept;
        template<typename T>
        std::vector<T> comb_sort(const std::vector<T>& value) noexcept;

        std::string heap_sort(const std::string& value) noexcept;
        template<typename T>
        std::vector<T> heap_sort(const std::vector<T>& value) noexcept;

        std::string insertion_sort(const std::string& value) noexcept;
        template<typename T>
        std::vector<T> insertion_sort(const std::vector<T>& value) noexcept;

        std::string merge_sort(const std::string& value) noexcept;
        template<typename T>
        std::vector<T> merge_sort(const std::vector<T>& value) noexcept;

        std::string quick_sort(const std::string& value) noexcept;
        template<typename T>
        std::vector<T> quick_sort(const std::vector<T>& value) noexcept;
    }
}

#endif // METACORE___ADVA___SORT_HPP