#include "etl/benchmark.hpp"
#include "etl/enum.hpp"
#include "etl/error.hpp"
#include "etl/exception.hpp"
#include "etl/file.hpp"
#include "etl/function.hpp"
#include "etl/hash.hpp"
#include "etl/index.hpp"
#include "etl/io.hpp"
#include "etl/iterator.hpp"
#include "etl/lexer.hpp"
#include "etl/linked_list.hpp"
#include "etl/list.hpp"
#include "etl/queue.hpp"
#include "etl/random.hpp"
#include "etl/sort.hpp"
#include "etl/stack.hpp"
#include "etl/stream.hpp"
#include "etl/ternary.hpp"
#include "etl/test.hpp"
#include "etl/token.hpp"
#include "etl/types.hpp"
#include "etl/warning.hpp"

#pragma once
#ifndef ETL_HPP
#define ETL_HPP
namespace etl
{
    template <bool enableTesting = false, bool enableBenchmarking = false>
    class system {
        private:
            ocf::que<warning> ordered_warnings;

    }
    void echo(const error& e) noexcept {
        std::cout << e;
        std::exit(EXIT_FAILURE);
    }

    void echo(const warning& w) noexcept {
        std::cout << w;
        ordered_warnings.push(w);
    }
}
#endif // ETL_HPP