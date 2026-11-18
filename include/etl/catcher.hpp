#include <cstddef>
#include <stack>
#include "error.hpp"
#include "warning.hpp"
#include "exception.hpp"

#pragma once

namespace etl {
    /**
     * @brief Stores errors, warnings, and exceptions in separate LIFO stacks.
     *
     * Each category is retrieved independently in last-in, first-out order.
     * Copy construction and copy assignment are disabled.
     */
    class catcher {
    private:
        std::stack<error> errors;
        std::stack<warning> warnings;
        std::stack<exception> exceptions;

    public:
        /** @brief Constructs an empty catcher. */
        catcher() = default;

        /** @brief Destroys the catcher and its stored diagnostic values. */
        ~catcher() = default;

        /** @brief Copy construction is disabled. */
        catcher(const catcher&) = delete;

        /** @brief Copy assignment is disabled. */
        catcher& operator=(const catcher&) = delete;

        /**
         * @brief Pushes an error onto the error stack.
         * @param value Error value to store.
         */
        void push(const error& value) { errors.push(value); }

        /**
         * @brief Pushes a warning onto the warning stack.
         * @param value Warning value to store.
         */
        void push(const warning& value) { warnings.push(value); }

        /**
         * @brief Pushes an exception onto the exception stack.
         * @param value Exception value to store.
         */
        void push(const exception& value) { exceptions.push(value); }

        /**
         * @brief Removes the most recently stored error.
         * @param value Receives the removed error when one is available.
         * @return true if an error was removed; otherwise false.
         */
        bool pop(error& value) {
            if (errors.empty()) return false;
            value = errors.top();
            errors.pop();
            return true;
        }

        /**
         * @brief Removes the most recently stored warning.
         * @param value Receives the removed warning when one is available.
         * @return true if a warning was removed; otherwise false.
         */
        bool pop(warning& value) {
            if (warnings.empty()) return false;
            value = warnings.top();
            warnings.pop();
            return true;
        }

        /**
         * @brief Removes the most recently stored exception.
         * @param value Receives the removed exception when one is available.
         * @return true if an exception was removed; otherwise false.
         */
        bool pop(exception& value) {
            if (exceptions.empty()) return false;
            value = exceptions.top();
            exceptions.pop();
            return true;
        }

        /**
         * @brief Checks whether all three diagnostic stacks are empty.
         * @return true if there are no stored errors, warnings, or exceptions.
         */
        bool empty() const noexcept {
            return errors.empty() && warnings.empty() && exceptions.empty();
        }

        /** @brief Gets the number of stored errors. */
        std::size_t error_count() const noexcept { return errors.size(); }

        /** @brief Gets the number of stored warnings. */
        std::size_t warning_count() const noexcept { return warnings.size(); }

        /** @brief Gets the number of stored exceptions. */
        std::size_t exception_count() const noexcept { return exceptions.size(); }

        /** @brief Removes all stored errors, warnings, and exceptions. */
        void clear() {
            while (!errors.empty()) errors.pop();
            while (!warnings.empty()) warnings.pop();
            while (!exceptions.empty()) exceptions.pop();
        }
    };
}