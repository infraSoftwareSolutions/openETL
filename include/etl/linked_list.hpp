#include <iostream>
#include <initializer_list>
#include <vector>
#include "cformat/structure.h"

#pragma once
#ifndef ETL___LINKED_LIST_HPP
#define ETL___LINKED_LIST_HPP

namespace etl
{

    /// @brief Represents a singly linked list of values.
    ///
    /// The list supports insertion, removal, lookup, replacement, and traversal
    /// operations while preserving the existing implementation semantics.
    template <typename T>
    class linked_list
    {
    private:
        struct node
        {
            T item;
            node *next;
        };

        node *first;

        node *last;

        size_t length;

    public:
        /// @brief Constructs an empty linked list.
        linked_list() noexcept
        {
            first = nullptr;
            last = nullptr;
            length = 0;
        }

        /// @brief Constructs a linked list from an initializer list.
        ///
        /// @param list The values to insert in order.
        linked_list(std::initializer_list<T> list) noexcept
        {
            first = nullptr;
            last = nullptr;
            length = 0;
            for (const T &value : list)
            {
                insertLast(value);
            }
        }

        /// @brief Constructs a linked list from a vector.
        ///
        /// @param list The values to insert in order.
        linked_list(const std::vector<T> &list) noexcept
        {
            first = nullptr;
            last = nullptr;
            length = 0;
            for (const T &value : list)
            {
                insertLast(value);
            }
        }

        /// @brief Copies the contents of another linked list.
        ///
        /// @param list The linked list to copy.
        linked_list(const linked_list<T> &list) noexcept
        {
            first = nullptr;
            last = nullptr;
            length = 0;
            const node *current = list.first;
            while (current != nullptr)
            {
                insertLast(current->item);
                current = current->next;
            }
        }

        /// @brief Copies the contents of another linked list into this one.
        ///
        /// @param list The linked list to copy.
        /// @return A reference to this linked list.
        linked_list<T> &operator=(const linked_list<T> &list) noexcept
        {
            if (this != &list)
            {
                clear();
                const node *current = list.first;
                while (current != nullptr)
                {
                    insertLast(current->item);
                    current = current->next;
                }
            }
            return *this;
        }

        /// @brief Returns the element at the specified index.
        ///
        /// @param index The zero-based position to access.
        /// @return The value at the given index, or a default value if out of range.
        T at(size_t index) noexcept
        {
            if (index >= length)
            {
                std::cerr << "Out Of Range: index exceed the length of the list.\n";
                return T();
            }
            else if (index == 0)
            {
                return first->item;
            }
            else if (index == length - 1)
            {
                return last->item;
            }
            else
            {
                const node *curr = first;
                for (size_t i = 0; i < index; i++)
                {
                    curr = curr->next;
                }
                return curr->item;
            }
        }

        /// @brief Returns the last element in the list.
        constexpr T last_item() noexcept { return last->item; }

        /// @brief Returns the first element in the list.
        constexpr T first_item() noexcept { return first->item; }

        /// @brief Checks whether the list is empty.
        constexpr bool empty() noexcept { return length == 0; }

        /// @brief Returns the current number of elements in the list.
        constexpr size_t size() noexcept { return length; }

        /// @brief Inserts an element at the front of the list.
        ///
        /// @param element The value to insert.
        void insertFirst(T element) noexcept
        {
            node *newNode = new node;
            newNode->item = element;
            if (length == 0)
            {
                first = newNode;
                last = newNode;
                newNode->next = nullptr;
            }
            else
            {
                newNode->next = first;
                first = newNode;
            }
            length++;
        }

        /// @brief Inserts an element at the end of the list.
        ///
        /// @param element The value to insert.
        void insertLast(T element) noexcept
        {
            node *newNode = new node;
            newNode->item = element;
            if (length == 0)
            {
                first = newNode;
                last = newNode;
                newNode->next = nullptr;
            }
            else
            {
                newNode->next = nullptr;
                last->next = newNode;
                last = newNode;
            }
            length++;
        }

        /// @brief Inserts an element at the specified position.
        ///
        /// @param pos The zero-based insertion position.
        /// @param element The value to insert.
        void insert(size_t pos, T element) noexcept
        {
            if (pos > length)
                std::cerr << "out of range error: The position of the element exceeds the length of the list.\n";
            else if (pos == 0)
                insertFirst(element);
            else if (pos == length)
                insertLast(element);
            else
            {
                node *cur = first;
                for (iter_less(i, pos - 1))
                {
                    cur = cur->next;
                }
                node *newNode = new node;
                newNode->item = element;
                newNode->next = cur->next;
                cur->next = newNode;
                length++;
            }
        }

        /// @brief Removes the first element from the list.
        procedure(remove_first) noexcept
        {
            if (length == 0)
            {
                std::cerr << "Empty Error: no element in the list to remove.\n";
            }
            else if (length == 1)
            {
                delete first;
                last = first = nullptr;
                length = 0;
            }
            else
            {
                node *curr = first;
                first = first->next;
                delete curr;
                length--;
            }
        }

        /// @brief Removes the last element from the list.
        procedure(remove_last) noexcept
        {
            if (length == 0)
            {
                std::cerr << "Empty Error: no element in the list to remove.\n";
            }
            else if (length == 1)
            {
                delete first;
                last = first = nullptr;
                length = 0;
            }
            else if (length == 2)
            {
                delete last;
                last = first;
                first->next = nullptr;
                length = 1;
            }
            else
            {
                node *curr = first->next;
                node *prev = first;
                while (curr != last)
                {
                    prev = curr;
                    curr = curr->next;
                }
                delete curr;
                prev->next = nullptr;
                last = prev;
                length--;
            }
        }

        /// @brief Removes the first occurrence of the specified element.
        ///
        /// @param element The value to remove.
        void remove(T element) noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: no element in the list to remove.\n";
                return;
            }
            if (first->item == element)
            {
                removeFirst();
                return;
            }
            else if (last->item == element)
            {
                removeLast();
                return;
            }
            else
            {
                node *curr = first->next;
                node *prev = first;
                while (curr != nullptr)
                {
                    if (curr->item == element)
                    {
                        prev->next = curr->next;
                        delete curr;
                        length--;
                        return;
                    }
                    prev = curr;
                    curr = curr->next;
                }
            }
            std::cerr << "Error: The element doesn't exist in the list.\n";
        }

        /// @brief Checks whether the specified value exists in the list.
        ///
        /// @param element The value to search for.
        /// @return true if the value is found, false otherwise.
        bool exist(T element) noexcept
        {
            const node *temp = first;
            while (temp != nullptr)
            {
                if (temp->item == element)
                    return true;
                temp = temp->next;
            }
            return false;
        }

        /// @brief Finds the index of the specified element.
        ///
        /// @param element The value to locate.
        /// @return The zero-based index of the element, or 0 if it was not found.
        size_t where(T element) noexcept
        {
            const node *temp = first;
            size_t index = 0;
            while (temp != nullptr)
            {
                if (temp->item == element)
                    return index;
                temp = temp->next;
                index++;
            }
            std::cerr << "Error: this element don't exist.\n";
            return 0;
        }

        /// @brief Clears the stored values while keeping the nodes intact.
        procedure(clear_items) noexcept
        {
            node *temp = first;
            while (temp != nullptr)
            {
                temp->item = T();
                temp = temp->next;
            }
        }

        /// @brief Removes all nodes from the list and resets its state.
        procedure(clear) noexcept
        {
            node *temp = first;
            while (temp != nullptr)
            {
                first = first->next;
                delete temp;
                temp = first;
            }
            last = nullptr;
            length = 0;
        }

        /// @brief Replaces the value stored at the first node.
        ///
        /// @param newElement The replacement value.
        void replaceFirst(T newElement) noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: empty list cann't replace any item.\n";
                return;
            }
            first->item = newElement;
        }

        /// @brief Replaces the value stored at the last node.
        ///
        /// @param newElement The replacement value.
        void replaceLast(T newElement) noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: empty list cann't replace any item.\n";
                return;
            }
            last->item = newElement;
        }

        /// @brief Replaces the first occurrence of an old value with a new value.
        ///
        /// @param oldElement The value to replace.
        /// @param newElement The replacement value.
        void replace(T oldElement, T newElement) noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: empty list cann't replace any item.\n";
                return;
            }
            node *temp = first;
            while (temp != nullptr)
            {
                if (temp->item == oldElement)
                {
                    temp->item = newElement;
                    return;
                }
                temp = temp->next;
            }
            std::cerr << "No element found to replace.\n";
        }

        /// @brief Replaces all occurrences of an old value with a new value.
        ///
        /// @param oldElement The value to replace.
        /// @param newElement The replacement value.
        void replace_all(T oldElement, T newElement) noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: empty list cann't replace any item.\n";
                return;
            }
            node *temp = first;
            while (temp != nullptr)
            {
                if (temp->item == oldElement)
                    temp->item = newElement;
                temp = temp->next;
            }
        }

        /// @brief Reverses the order of the list.
        ///
        /// The operation runs in linear time.
        procedure(reverse) noexcept
        {
            if (empty())
            {
                std::cerr << "Empty Error: cann't reverse empty list.\n";
            }
            else if (length == 1)
            {
                std::cerr << "Error: cann't reverse list with one element.\n";
            }
            else if (length == 2)
            {
                last->next = first;
                first->next = nullptr;
                node *temp = first;
                first = last;
                last = temp;
            }
            else
            {
                node *prev = nullptr;
                node *curr = first;
                node *next = nullptr;
                while (curr != nullptr)
                {
                    next = curr->next;
                    curr->next = prev;
                    prev = curr;
                    curr = next;
                }
                last = first;
                first = prev;
            }
        }

        template <typename U>
        friend std::ostream &operator<<(std::ostream &os, const linked_list<U> &value) noexcept
        {
            os << "list: {";
            const node *curr = value.first;
            for (size_t i = 0; i < value.length; ++i)
            {
                os << curr->item;
                if (i != value.length - 1)
                    os << ", ";
                curr = curr->next;
            }
            os << "}\n";
            return os;
        }

        /// @brief Prints the list contents to the standard output stream.
        procedure(print) noexcept
        {
            const node *cur = first;
            while (cur != nullptr)
            {
                std::cout << cur->item << ' ';
                cur = cur->next;
            }
            std::cout << char(10);
        }

        /// @brief Returns the element at the given index using array-style access.
        ///
        /// @param index The zero-based position to access.
        /// @return The value stored at the given index, or a default value if out of range.
        T operator[](size_t index) noexcept
        {
            if (index >= length)
            {
                std::cerr << "Out Of Range: index exceed the length of the list.\n";
                return T();
            }
            else if (index == 0)
            {
                return first->item;
            }
            else if (index == length - 1)
            {
                return last->item;
            }
            else
            {
                const node *curr = first;
                for (iter_less(i, index))
                {
                    curr = curr->next;
                }
                return curr->item;
            }
        }

        ~linked_list()
        {
            node *current = first;
            while (current != nullptr)
            {
                node *next = current->next;
                delete current;
                current = next;
            }
        }
    };

    /// @brief Represents a doubly linked list container.
    /// The class provides insertion, removal, lookup, and replacement operations
    /// while keeping the underlying node-based implementation intact.
    template <typename T>
    class linkedList
    {
    private:
        struct node
        {
            node *next;
            node *prev;
            T item;
        };

        node *first = nullptr;
        node *last = nullptr;
        size_t length = 0;

    public:
        /// @brief Constructs an empty linked list.
        linked_list() = default;

        /// @brief Constructs a linked list from an initializer list.
        ///
        /// @param list The values to insert in order.
        linked_list(std::initializer_list<T> list)
        {
            for (const T &value : list)
                insert_last(value);
        }

        /// @brief Constructs a linked list from a vector.
        ///
        /// @param v The values to insert in order.
        linked_list(const std::vector<T> &v)
        {
            for (const T &value : v)
                insert_last(value);
        }

        linked_list(const linked_list<T> &list)
        {
            const node *temp = list->first;
            while (temp != nullptr)
            {
                insert_last(temp->item);
                temp = temp->next;
            }
        }

        /// @brief Checks whether the list contains any elements.
        constexpr bool empty() const noexcept
        {
            return length == 0;
        }

        /// @brief Returns the number of elements stored in the list.
        constexpr size_t size() const noexcept
        {
            return length;
        }

        constexpr T last_item() noexcept
        {
            return last->item;
        }

        constexpr T first_item() noexcept
        {
            return first->item;
        }

        /// @brief Inserts an element at the front of the list.
        ///
        /// @param element The value to insert.
        void insert_first(const T &element)
        {
            node *newNode = new node{nullptr, nullptr, element};
            if (empty())
            {
                first = last = newNode;
            }
            else
            {
                newNode->next = first;
                first->prev = newNode;
                first = newNode;
            }
            length++;
        }

        /// @brief Inserts an element at the end of the list.
        ///
        /// @param element The value to insert.
        void insert_last(const T &element)
        {
            node *newNode = new node{nullptr, nullptr, element};
            if (empty())
            {
                first = last = newNode;
            }
            else
            {
                newNode->prev = last;
                last->next = newNode;
                last = newNode;
            }
            length++;
        }

        void insert_before(T element, T befEle)
        {
            if (empty())
            {
                std::cerr << "Empty Error: no elements exist in this list.\n";
                return;
            }
            if (first->item == element)
            {
                insert_first(befEle);
                return;
            }
            node *temp = first->next;
            while (temp != nullptr)
            {
                if (temp->item == element)
                {
                    node *bef = temp->prev;
                    node *newNode = new node{temp, bef, befEle};
                    bef->next = newNode;
                    temp->prev = newNode;
                    length++;
                    return;
                }
                temp = temp->next;
            }
            std::cerr << "no element exist like this element: " << element;
        }

        void insert_after(T element, T aftEle)
        {
            if (empty())
            {
                std::cerr << "Empty Error: no elements exist in the list.\n";
                return;
            }
            if (last->item == element)
            {
                insert_last(aftEle);
                return;
            }
            node *temp = last->prev;
            while (temp != nullptr)
            {
                if (temp->item == element)
                {
                    node *aft = temp->next;
                    node *newNode = new node{aft, temp, aftEle};
                    aft->prev = newNode;
                    temp->next = newNode;
                    length++;
                    return;
                }
                temp = temp->prev;
            }
            std::cerr << "no element exist like this element: " << element;
        }

        /// @brief Removes the first element from the list.
        procedure(pop_first)
        {
            if (empty())
            {
                std::cerr << "Empty Error: The list is empty on pop.\n";
                return;
            }
            if (length == 1)
            {
                node *temp = first;
                last = nullptr;
                first = nullptr;
                delete temp;
                length = 0;
                return;
            }
            node *temp = first;
            first = first->next;
            first->prev = nullptr;
            delete temp;
            length--;
        }

        /// @brief Removes the last element from the list.
        procedure(pop_last)
        {
            if (empty())
            {
                std::cerr << "Empty Error: The list is empty on pop.\n";
                return;
            }
            if (length == 1)
            {
                node *temp = first;
                last = nullptr;
                first = nullptr;
                delete temp;
                length = 0;
                return;
            }
            node *temp = last;
            last = last->prev;
            last->next = nullptr;
            delete temp;
            length--;
        }

        /// @brief Replaces the first matching element in the list.
        ///
        /// @param oldEle The value to replace.
        /// @param newEle The replacement value.
        void replace(T oldEle, T newEle)
        {
            if (empty())
            {
                std::cerr << "Empty Error: can't replace item in empty list.\n";
                return;
            }
            else if (first->item == oldEle)
            {
                first->item = newEle;
                return;
            }
            node *temp = first->next;
            while (temp != nullptr)
            {
                if (temp->item == oldEle)
                {
                    temp->item = newEle;
                    return;
                }
                temp = temp->next;
            }
            std::cerr << "Error: no element found to replace.\n";
        }

        void replace_all(T oldEle, T newEle)
        {
            if (empty())
            {
                std::cerr << "Empty Error: can't replace item in empty list.\n";
                return;
            }
            const node *temp1 = first;
            const node *temp2 = last;
            while (temp1 != temp2 && temp1->prev != temp2)
            {
                if (temp1->item == oldEle)
                    temp1->item = newEle;
                if (temp2->item == oldEle)
                    temp2->item = newEle;
                temp1 = temp1->next;
                temp2 = temp2->prev;
            }
        }

        void remove(T element)
        {
            if (empty())
            {
                std::cerr << "Empty Error: can't remove elements form empty list.\n";
            }
            else if (length == 1 && element == first->item)
            {
                node *temp = first;
                last = nullptr;
                first = nullptr;
                delete temp;
                length--;
            }
            else if (first->item == element)
            {
                pop_first();
            }
            else if (last->item == element)
            {
                pop_last();
            }
            else
            {
                node *temp1 = first;
                node *temp2 = last;
                while (temp1 != temp2 && temp1->prev != temp2)
                {
                    if (temp1->item == element)
                    {
                        node *prev = temp1->prev;
                        node *next = temp1->next;
                        prev->next = next;
                        next->prev = prev;
                        delete temp1;
                        length--;
                        return;
                    }
                    if (temp2->item == element)
                    {
                        node *prev = temp2->prev;
                        node *next = temp2->next;
                        prev->next = next;
                        next->prev = prev;
                        delete temp2;
                        length--;
                        return;
                    }
                    temp1 = temp1->next;
                    temp2 = temp2->prev;
                }
                std::cerr << "Element not found\n";
            }
        }

        procedure(clear)
        {
            node *curr = first;
            while (curr != nullptr)
            {
                node *nextNode = curr->next;
                delete curr;
                curr = nextNode;
            }
            first = nullptr;
            last = nullptr;
            length = 0;
        }

        /// @brief Checks whether the specified element exists in the list.
        ///
        /// @param element The value to search for.
        bool exist(T element)
        {
            if (empty())
            {
                std::cerr << "Empty Error: no element exist in the list.\n";
                return false;
            }
            const node *temp1 = first;
            const node *temp2 = last;
            while (temp1 != temp2 && temp1->prev != temp2)
            {
                if (temp1->item == element || temp2->item == element)
                    return true;
                temp2 = temp2->prev;
                temp1 = temp1->next;
            }
            return false;
        }

        /// @brief Returns the index of the specified element if it exists.
        ///
        /// @param element The value to locate.
        size_t where(T element)
        {
            if (empty())
            {
                std::cerr << "Empty Error: no element exist in the list.\n";
                return 0;
            }
            const node *temp1 = first;
            const node *temp2 = last;
            size_t ind1 = 0;
            size_t ind2 = length - 1;
            while (temp1 != temp2 && temp1->prev != temp2)
            {
                if (temp1->item == element)
                    return ind1;
                if (temp2->item == element)
                    return ind2;
                temp2 = temp2->prev;
                temp1 = temp1->next;
                ind1++;
                ind2--;
            }
            std::cerr << "Error: no element found.\n";
            return 0;
        }

        /// @brief Prints the list contents to the standard output stream.
        procedure(print)
        {
            if (empty())
            {
                std::cout << "linked_list: {}\n";
            }
            else if (length == 1)
            {
                std::cout << "linked_list: {" << first->item << "}\n";
            }
            else if (length == 2)
            {
                std::cout << "linked_list: {" << first->item << ", " << last->item << "}\n";
            }
            else
            {
                std::cout << "linked_list: {";
                const node *temp = first;
                while (temp != nullptr)
                {
                    if (temp == last)
                    {
                        std::cout << temp->item << "}\n";
                        return;
                    }
                    std::cout << temp->item << ", ";
                    temp = temp->next;
                }
            }
        }

        ~linked_list()
        {
            if (length >= 0 && length <= 2)
            {
                delete last;
                delete first;
            }
            else if (length == 3)
            {
                delete last->prev;
                delete last;
                delete first;
            }
            else if (length == 4)
            {
                delete last->prev;
                delete first->next;
                delete first;
                delete last;
            }
            while (length != 0)
            {
                last = last->prev;
                delete last->next;
                if (last == first)
                {
                    delete last;
                    delete first;
                }
                length--;
            }
        }
    };
}

#endif // ETL___LINKED_LIST_HPP
