#pragma once

#include "common_inc.h"

template <typename T>
class Stack
{
public:
    Stack(size_t size)
    {
        dataArray = new T[size];
        capacity = size;
        top = -1;
    }

    ~Stack()
    {
        delete[] dataArray;
    }

    void push(T data)
    {
        if (isFull())
        {
            throw std::out_of_range("stack overflow");
        }
        dataArray[++top] = data;
    }

    T pop()
    {
        if (isEmpty())
        {
            throw std::out_of_range("stack underflow");
        }
        return dataArray[top--];
    }

    T peek() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("stack underflow");
        }
        return dataArray[top];
    }

    size_t size() const
    {
        return top + 1;
    }

    T* data() const
    {
        return dataArray;
    }

    void flush()
    {
        top = -1;
    }

    bool isFull() const
    {
        return top == capacity - 1;
    }

    bool isEmpty() const
    {
        return top == -1;
    }

private:
    T* dataArray;
    int top;
    size_t capacity;
};
