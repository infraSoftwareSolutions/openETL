#include <initializer_list>
#pragma once
#if !defined(ETL_ITERATOR_HPP)
#define ETL_ITERATOR_HPP
namespace etl {
    /**
     * @brief A cursor over a doubly linked sequence of values.
     *
     * The cursor refers to the current node and can move in either direction.
     * An empty instance has no current node. Most navigation and element
     * operations require a non-empty instance, and the current destructor
     * also dereferences the current node.
     *
     * @tparam T Type stored in each node.
     *
     * @warning Instances manage linked nodes. Do not merge or copy instances
     * that share nodes and then destroy both instances. Empty instances are
     * not safe to destroy with the current implementation.
     */
    template <typename T>
    class iterator {
        private:
        struct node {
            T data;
            node* next;
            node* prev;
            node() : data(T()), next(nullptr), prev(nullptr) {}
            node(const T& element) : data(element), next(nullptr), prev(nullptr) {}
            node(const T& element, node* prev) : data(element), next(nullptr), prev(prev) {}
            node(const T& element, node* prev, node* next) : data(element), next(next), prev(prev) {}
        };
        node* start;
        node* current;
        node* end;
        size_t s;
        public:
        /**
         * @brief Constructs an empty iterator.
         *
         * @warning Operations that access the current or boundary node require
         * a non-empty iterator.
         */
        iterator() : current(nullptr), start(nullptr), end(nullptr), s(0) {}

        /**
         * @brief Constructs an iterator containing one value.
         * @param element Value to store in the new node.
         */
        iterator(const T& element) : current(new node(element)), start(current), end(current), s(1) {}

        /**
         * @brief Constructs an iterator node linked after a previous node.
         * @param element Value to store in the new node.
         * @param prev Previous node to link to, or nullptr if there is none.
         */
        iterator(const T& element, node* prev) : current(new node(element, prev)), start(prev), end(current), s(1) {}

        /**
         * @brief Constructs an iterator node between two existing nodes.
         * @param element Value to store in the new node.
         * @param prev Previous node, or nullptr if there is none.
         * @param next Following node, or nullptr if there is none.
         */
        iterator(const T& element, node* prev, node* next) : current(new node(element, prev, next)), start(prev), end(next), s(1) {
            if(prev != nullptr) prev->next = current;
            if(next != nullptr) next->prev = current;
        }

        /**
         * @brief Constructs an iterator from another iterator's current value.
         *
         * The new current node contains a copy of the source current value;
         * the boundary pointers and size are copied from the source.
         *
         * @param other Iterator to copy.
         * @warning Requires a non-empty source. The linked nodes may be
         * shared with the source; destroying both instances can therefore
         * invalidate or delete shared nodes.
         */
        iterator(const iterator& other) : current(new node(*other.current)), start(other.start), end(other.end), s(other.s) {}

        /**
         * @brief Constructs an iterator from an initializer list.
         * @param list Values to initialize the iterator with.
         * @warning The current implementation appends each value to an empty
         * iterator, but append requires an existing boundary node. A non-empty
         * list therefore cannot be constructed successfully; an empty
         * instance is also unsafe to destroy with the current implementation.
         */
        iterator(std::initializer_list<T> list) : current(nullptr), start(nullptr), end(nullptr), s(0) {
            for(const T& element : list) {
                append(element, true);
            }
        }

        /**
         * @brief Destroys this iterator and the nodes reachable from its current node.
         * @warning Do not destroy another iterator that shares these nodes.
         */
        ~iterator() {
            s = 0;
            node* temp = nullptr;
            if(has_next()) {
                temp = current->next;
                while(temp != nullptr) {
                    node* next = temp->next;
                    delete temp;
                    temp = next;
                }
            }
            
            if(has_prev()) {
                temp = current->prev;
                while(temp != nullptr) {
                    node* prev = temp->prev;
                    delete temp;
                    temp = prev;
                }
            }
            delete current;
        }

        /**
         * @brief Checks whether the current node has a following node.
         * @return true if a following node exists; otherwise false.
         * @warning Requires a non-empty iterator.
         */
        constexpr bool has_next() noexcept { return current->next != nullptr; }

        /**
         * @brief Checks whether the current node has a preceding node.
         * @return true if a preceding node exists; otherwise false.
         * @warning Requires a non-empty iterator.
         */
        constexpr bool has_prev() noexcept { return current->prev != nullptr; }

        /**
         * @brief Checks whether this iterator has a current node.
         * @return true if the iterator is empty; otherwise false.
         */
        constexpr bool is_empty() noexcept { return current == nullptr; }

        /**
         * @brief Moves the current position by one node when possible.
         * @param next true to move forward; false to move backward.
         * @warning Requires a non-empty iterator.
         */
        inline void move(bool next) {
            if(next && current->next != nullptr) current = current->next;
            if(!next && current->prev != nullptr) current = current->prev;
        }

        /**
         * @brief Gets the value at the current position.
         * @return A copy of the current value.
         * @warning Requires a non-empty iterator.
         */
        constexpr T get() noexcept { return current->data; }

        /**
         * @brief Gets the value in the adjacent node.
         * @param next true to inspect the following node; false to inspect the
         * preceding node.
         * @return A copy of the adjacent value, or a default-constructed T if
         * there is no adjacent node.
         * @warning Requires a non-empty iterator.
         */
        constexpr T get(bool next) {
            if(next && current->next != nullptr) return (current->next)->data;
            if(!next && current->prev != nullptr) return (current->prev)->data;
            return T();
        }

        /**
         * @brief Gets the address of the selected boundary node.
         * @param is_start true to select the first node; false to select the
         * last node.
         * @return A pointer to the selected boundary, or nullptr if the
         * selected boundary is unset.
         * @warning The implementation returns an internal node pointer,
         * although the declared return type is const T*.
         */
        const T* edge(bool is_start) noexcept {
            return is_start ? start : end;
        }

        /**
         * @brief Removes the current node and selects a neighboring node.
         *
         * When both neighbors exist, the preceding node becomes current.
         * Otherwise the existing neighbor becomes current.
         *
         * @warning Requires a non-empty iterator. Removing the last remaining
         * node leaves the current pointer dangling.
         */
        inline void del() {
            if(has_prev() && has_next()) {
                node* tempPrev = current->prev;
                node* tempNext = current->next;
                tempPrev->next = current->next;
                tempNext->prev = current->prev;
                delete current;
                current = tempPrev;
            } else if(has_prev()) {
                node* temp = current->prev;
                delete current;
                current = temp;
            } else if(has_next()) {
                node* temp = current->next;
                delete current;
                current = temp;
            } else if(current != nullptr) {
                delete current;
            }
            s--;
        }

        /**
         * @brief Adds a value at the beginning or end of the sequence.
         * @param element Value to append.
         * @param to_end true to add at the end; false to add at the beginning.
         * @warning Requires a non-empty iterator because a boundary node must
         * already exist.
         */
        inline void append(const T& element, bool to_end) noexcept {
            if(to_end) {
                end->next = new node(element, end);
                end = end->next;
            } else {
                start->prev = new node(element, nullptr, start);
                start = start->prev;
            }
            s++;
        }

        /**
         * @brief Removes the first or last node.
         * @param element Unused; retained in the current function signature.
         * @param to_end true to remove the last node; false to remove the first.
         * @warning Requires at least two nodes. The current implementation
         * dereferences the new boundary after removing a node.
         */
        inline void pop(const T& element, bool to_end) noexcept {
            if(to_end) {
                end = end->prev;
                delete end->next;
                end->next = nullptr;
            } else {
                start = start->next;
                delete start->prev;
                start->prev = nullptr;
            }
            s--;
        }

        /**
         * @brief Gets the number of nodes recorded by this iterator.
         * @return The stored sequence size.
         */
        inline size_t size() const {
            return s;
        }

        /**
         * @brief Swaps the current node with its next or previous neighbor.
         * @param is_next true to swap with the following node; false to swap
         * with the preceding node.
         * @warning Requires a non-empty iterator.
         */
        inline void swap(bool is_next) {
            if(is_next && has_next()) {
                node* temp = current->next;
                current->next = temp->next;
                temp->prev = current->prev;
                current->prev = temp;
                temp->next = current;
            } else if(!is_next && has_prev()) {
                node* temp = current->prev;
                current->prev = temp->prev;
                temp->next = current->next;
                current->next = temp;
                temp->prev = current;
            }
        }

        /**
         * @brief Joins another iterator's sequence at the selected boundary.
         * @param other Sequence to join.
         * @param to_end true to attach at the end; false to attach at the
         * beginning.
         * @warning The operation links the existing nodes without transferring
         * ownership or clearing the other iterator. Destroying both instances
         * may delete the same nodes.
         */
        inline void merge(const iterator<T>& other, bool to_end) {
            s += other.s;
            if(to_end) {
                end->next = other.start;
                other.start->prev = end;
                end = other.end;
            } else {
                start->prev = other.end;
                other.end->next = start;
                start = other.start;
            }
        }

        /**
         * @brief Advances the current position up to the requested number of nodes.
         * @param value Maximum number of forward steps.
         */
        void operator+=(size_t value) {
            for(size_t i = 0; i < value; ++i) {
                move(true);
            }
        }

        /**
         * @brief Moves the current position backward up to the requested number of nodes.
         * @param value Maximum number of backward steps.
         */
        void operator-=(size_t value) {
            for(size_t i = 0; i < value; ++i) {
                move(false);
            }
        }
    };
}
#endif // ETL_ITERATOR_HPP