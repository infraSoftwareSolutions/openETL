#include <iostream>
#include <initializer_list>
#include "cformat/types.h"
#include "cformat/structure.h"

#pragma once
#ifndef ETL___QUEUE_HPP
#define ETL___QUEUE_HPP

namespace etl
{

    /// @brief Represents a queue implemented with a singly linked list.
    ///
    /// The class supports enqueuing, dequeuing, and inspecting the front and rear items.
    template <typename T>
    class queue
    {
    private:
        struct node
        {
            T item;
            node *next;
        };
        node *front;
        node *rear;
        size_t size;

    public:
        /// @brief Constructs an empty queue.
        queue()
        {
            front = rear = nullptr;
            size = 0;
        }

        queue(T element)
        {
            front = new node;
            front->item = element;
            front->next = nullptr;
            rear = front;
            size++;
        }

        queue(std::initializer_list<T> list)
        {
            for (const T &element : list)
                enque(element);
        }

        /// @brief Checks whether the queue is empty.
        inline bool empty() const noexcept
        {
            if (rear == nullptr)
                return true;
            return false;
        }

        /// @brief Adds an element to the rear of the queue.
        ///
        /// @param element The value to enqueue.
        void enque(T element) noexcept
        {
            if (empty())
            {
                front = new node;
                front->item = element;
                front->next = nullptr;
                rear = front;
            }
            else
            {
                node *new_ptr = new node;
                new_ptr->item = element;
                new_ptr->next = nullptr;
                rear->next = new_ptr;
                rear = new_ptr;
            }
            size++;
        }

        /// @brief Removes the element at the front of the queue.
        procedure(deque)
        {
            if (empty())
            {
                throw std::invalid_argument("empty que can\'t deque");
            }
            else
            {
                node *temp_ptr = front;
                if (front == rear)
                {
                    rear = nullptr;
                    front = nullptr;
                    size--;
                }
                else
                {
                    front = front->next;
                    size--;
                }
                temp_ptr->next = nullptr;
                delete temp_ptr;
            }
        }

        /// @brief Returns the value stored at the front of the queue.
        inline T get_front() const
        {
            if (empty())
                throw std::invalid_argument("empty que");
            return front->item;
        }

        /// @brief Returns the value stored at the rear of the queue.
        inline T get_rear() const
        {
            if (empty())
                throw std::invalid_argument("empty que");
            return rear->item;
        }

        /// @brief Removes all elements from the queue.
        procedure(clear)
        {
            node *current;
            while (front != nullptr)
            {
                current = front;
                front = front->next;
                delete current;
            }
            rear = nullptr;
            size = 0;
        }

        void operator=(const std::vector<T> &elements)
        {
            clear();
            for (const T &element : elements)
                enque(element);
        }

        void operator=(const std::string &s)
        {
            clear();
            for (const char &c : s)
                enque(static_cast<T>(c));
        }

        inline void operator<<(T element) { enque(element); }

        inline void operator<<(std::vector<T> &elements)
        {
            enque(elements[elements.size() - 1]);
            elements.pop_back();
        }

        inline void operator<<(std::string &s)
        {
            enque(s[s.size() - 1]);
            s.pop_back();
        }

        inline void operator>>(T &element)
        {
            element = get_front();
            deque();
        }

        inline void operator>>(std::vector<T> &elements)
        {
            elements.push_back(get_front());
            deque();
        }

        inline void operator>>(std::string &s)
        {
            s += static_cast<char>(get_front());
            deque();
        }

        ~queue() { clear(); }
    };

    template <typename T, size_t maxSize>
    class Queue
    {
    private:
        T arr[maxSize];
        size_t rear;
        size_t front;
        size_t length;

    public:
        Queue(int ArrSize)
        {
            if (ArrSize < 0)
                throw invalid_argument("the size have to be bigger then zero");
            front = 0;
            maxSize = ArrSize;
            rear = maxSize - 1;
            length = 0;
        }

        Queue(std::initializer_list<T> list) noexcept : arr(list) {};

        inline constexpr bool empty() const noexcept { return length == 0; }

        inline constexpr bool full() const noexcept { return length == maxSize; }

        void eque(T element) noexcept
        {
            if (full())
                io::println_error("Queue Full Can't Enqueue");
            else
            {
                rear = (rear + 1) % maxSize;
                arr[rear] = element;
                length++;
            }
        }

        procedure(dque) noexcept
        {
            if (empty())
                io::println_error("Empty Queue Can't Dequeue");
            else
            {
                front = (front + 1) % maxSize;
                length--;
            }
        }

        T get_front() const
        {
            if (empty())
            {
                io::println_error("the queue is empty, no elements to get");
                throw std::invalid_argument("Queue is empty, no front element available.");
            }
            return arr[front];
        }

        void get_front(T &element) const noexcept
        {
            if (empty())
            {
                io::println_error("the queue is empty, no elements to get");
                return;
            }
            element = arr[front];
        }

        T get_rear() const
        {
            if (empty())
            {
                io::println_error("the queue is empty, no elements to get");
                throw std::invalid_argument("Queue is empty, no rear element available.");
            }
            return arr[rear];
        }

        procedure(print) const noexcept
        {
            if (empty())
            {
                io::println_error("the queue is empty, no elements to print");
                return;
            }
            std::cout << "Queue elements: ";
            for (size_t i = 0; i < length; i++)
                cout << arr[(front + i) % maxSize] << " ";
            std::cout << '\n';
        }

        T search(T element) const noexcept
        {
            if (!empty())
            {
                for (int i = front; i != rear; i = (i + 1) % maxSize)
                {
                    if (arr[i] == element)
                        return i;
                }
                if (arr[rear] == element)
                    return rear;
            }
            else
                io::println_error("Q is empty ! ");
            return -1;
        }

        void operator=(const std::vector<T> &vec)
        {
            if (!vec.empty())
            {
                for (int i = 0; i < vec.size(); i++)
                    addQueue(vec[i]);
            }
            else
                io::println_error("Empty Error");
        }

        void operator=(const queue &other) noexcept
        {
            if (this != &other)
            {
                front = other.front;
                rear = other.rear;
                length = other.length;
                for (size_t i = 0; i < maxSize; i++)
                    arr[i] = other.arr[i];
            }
        }

        T operator>>(T &element)
        {
            if (empty())
            {
                io::println_error("the queue is empty, no elements to read");
                throw std::invalid_argument("Queue is empty, no elements to read.");
            }
            element = get_front();
            deleteQueue();
            return element;
        }

        T operator<<(const T &element)
        {
            if (full())
            {
                io::println_error("Queue Full Can't Enqueue");
                throw std::out_of_range("Queue is full, cannot add more elements.");
            }
            addQueue(element);
            return element;
        }

        ~Queue() = default;
    };
}

#endif // ETL___QUEUE_HPP