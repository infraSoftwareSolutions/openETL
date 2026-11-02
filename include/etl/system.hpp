#include "warning.hpp"
#include "error.hpp"
#include <iostream>

#pragma once
#ifndef ETL___SYSTEM_HPP
#define ETL___SYSTEM_HPP

namespace etl
{
    ocf::que<warning> ordered_warnings;

    void echo(const error& e) noexcept {
        std::cout << e;
        std::exit(EXIT_FAILURE);
    }

    void echo(const warning& w) noexcept {
        std::cout << w;
        ordered_warnings.push(w);
    }
}

#endif // ETL___SYSTEM_HPP