#ifndef STACK_H
#define STACK_H

#include <stdexcept>

template<typename T>
class Stack
{
public:
  Stack(size_t size)
  {
    m_data = new T[size];
    m_capacity = size;
    m_top = -1;
  }

  ~Stack()
  {
    delete[] m_data;
  }

  void push(T data)
  {
    if (isFull()) {
      throw std::out_of_range("stack overflow");
    }
    m_data[++m_top] = data;
  }

  T pop()
  {
    if (isEmpty()) {
      throw std::out_of_range("stack underflow");
    }
    return m_data[m_top--];
  }

  bool isFull()
  {
    return m_top == m_capacity - 1;
  }

  bool isEmpty()
  {
    return m_top == -1;
  }

private:
  T *m_data;
  int m_top;
  size_t m_capacity;
};

#endif /* #ifndef STACK_H */
