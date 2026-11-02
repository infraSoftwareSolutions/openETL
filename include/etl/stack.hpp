#include <algorithm>
#include "cfrost/structure.h"
#include "cfrost/types.h"

#pragma once
#ifndef ETL___STACK_HPP
#define ETL___STACK_HPP

namespace etl
{
    /// @brief Represents a stack implemented with a linked-list-based node structure.
    ///
    /// This container supports pushing, popping, and inspecting the current top element.
    template <class T>
    class stack
    {
    private:
        struct node
        {
            T item;
            node *prev;

            node() : item(T()), prev(nullptr) {}
            node(const T& value) : item(value), prev(nullptr) {}
            node(const T& value, node*& NODE) : item(value), prev(NODE) {}
        };
        node *current;
        size_t size;

    public:
        /// @brief Constructs an empty stack.
        inline constexpr stack() : current(nullptr), size(0) {}

        /// @brief Pushes a new item onto the stack.
        /// @param element The value to push.
        void push(const T& element) noexcept
        {
            if(current == nullptr) {
                current = new node(element);
            } else {
                node* newHead = new node(element, current);
                current = newHead;
            }
            size++;
        }

        /// @brief Checks whether the stack is empty.
        inline constexpr bool empty() const noexcept { return current == nullptr; }

        /// @brief Removes the top item from the stack.
        procedure(pop) noexcept
        {
            if(empty()) {
                return;
            } else {
                node* tempHead = current;
                current = current->prev;
                delete tempHead;
                size--;
            }
        }

        /// @brief Removes the top item and stores it in the provided reference.
        /// @param stackTop Receives the removed value.
        void pop(T &stackTop) noexcept
        {
            if (empty()) {
                return;
            } else {
                stackTop = current->item;
                node* tempHead = current;
                current = current->prev;
                delete tempHead;
                size--;
            }
        }

        /// @brief Copies the current top element to the provided reference.
        /// @param stackTop Receives the top value.
        inline T top(T &stackTop) noexcept
        {
            return empty() ? T() : current->item;
        }

        inline procedure(clear) noexcept {
            if(empty()) return;
            node* temp = current;
            while(!empty()) {
                current = current->prev;
                delete temp;
                temp = current;
            }
            size = 0;
        }

        void sort(const bool& decreasing_order) {
            ocf::vec<T> temp;
            while(!empty()) {
                T stackTop;
                this.pop(stackTop);
                temp.push_back(stackTop);
            }
            std::sort(temp.begin(), temp.end());
            if(decreasing_order) {
                for(size_t i = temp.size() - 1; i > 0; i--) {
                    this.push(temp[i]);
                }
            } else {
                for(T element : temp) {
                    this.push(element);
                }
            }
        }

        ocf::vec<T> to_vec() {
            ocf::vec<T> result;
            node* temp = current;
            while(temp != nullptr) {
                result.push_back(temp->item);
                temp = temp->prev;
            }
            return result;
        }
    };

    /// @brief Represents a fixed-capacity stack implemented on a static array.
    /// This container supports push, pop, and top access operations within a predefined size.
    template <typename T, size_t maxSize>
    class Stack
    {
    private:
        size_t top;
        T item[maxSize]; // T can be int, double, string, etc.

    public:
        /// @brief Constructs an empty fixed-capacity stack.
        Stack() : top(-1) {}

        /// @brief Pushes an element onto the stack.
        /// @param element The value to push.
        void push(T element)
        {
            if (top == maxSize - 1)
            {
                return;
            }
            item[++top] = element;
        }

        /// @brief Checks whether the stack is empty.
        bool empty()
        {
            return top < 0;
        }

        /// @brief Removes the top element from the stack.
        procedure(pop)
        {
            if (empty())
            {
                std::cerr << "Stack empty on pop" << endl;
                return;
            }
            top--;
        }

        /// @brief Removes the top element and stores it in the provided reference.
        ///
        /// @param element Receives the removed value.
        void pop(T &element)
        {
            if (empty())
                std::cerr << "Stack empty on pop" << endl;
            else
                element = item[top--];
        }

        /// @brief Copies the top element to the provided reference.
        ///
        /// @param StackTop Receives the top value.
        void top(T &StackTop)
        {
            if (empty())
                std::cerr << "Stack empty on get top" << endl;
            else
                StackTop = item[top];
        }

        /// @brief Prints the stack contents to the standard output stream.
        procedure(print)
        {
            for (int i = top; i >= 0; --i)
            {
                if (i == top)
                    std::cout << " [" << item[i] << ", ";
                else if (i == 0)
                    std::cout << item[i] << "] " << endl;
                else
                    std::cout << item[i] << ", ";
            }
        }
    };
}
#endif // ETL___STACK_HPP