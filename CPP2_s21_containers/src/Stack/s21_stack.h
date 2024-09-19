#include <cmath>
#include <iostream>

#include "../List/s21_list.h"

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  struct node {
    value_type data;
    node *prev = nullptr;
  };

 private:
  node *m_tail = nullptr;
  size_type size_stack = 0;

 public:
  stack() {
    m_tail = nullptr;
    size_stack = 0;
  };
  stack(std::initializer_list<value_type> items) {
    for (auto &item : items) push(item);
  };
  node *GetTail() { return this->m_tail; }
  void SetTail(node *const ptr) { m_tail = ptr; }
  const_reference top() { return this->m_tail->data; };

  size_type max_size() const noexcept {
    return (pow(2, 64)) / sizeof(value_type) - 1;
  };

  stack &swap(stack &other) {
    auto buff(other);
    other = *this;
    *this = buff;
    return *this;
  };

  ~stack() {
    while (this->empty() != 1) {
      this->pop();
    }
    this->SetTail(nullptr);
    this->size_stack = 0;
  };

  bool empty() { return (this->GetTail() == nullptr) ? 1 : 0; };

  stack &operator=(stack const &other) {
    this->~stack();
    stack<value_type> buffer;
    for (node *i = other.m_tail; i != nullptr;) {
      buffer.push(i->data);
      i = i->prev;
    }
    for (node *i = buffer.m_tail; i != nullptr;) {
      this->push(i->data);
      i = i->prev;
    }
    return *this;
  };

  stack &operator=(stack &&other) {
    this->SetTail(other.GetTail());
    this->size_stack = other.size();
    other.size_stack = 0;
    other.SetTail(nullptr);
    return *this;
  };

  void push(value_type value) {
    s21::stack<T>::node *newnode = new node{value, nullptr};
    newnode->data = value;
    if (m_tail) {
      newnode->prev = m_tail;
      m_tail = newnode;
    } else {
      m_tail = newnode;
    }
    size_stack++;
  };

  void pop() {
    if (m_tail) {
      node *tmp = m_tail;
      this->m_tail = this->m_tail->prev;
      delete tmp;
    } else
      throw std::out_of_range("pop not have tail");
  };

  stack(stack &&other) {
    this->SetTail(other.GetTail());
    size_stack = other.size_stack;
    other.SetTail(nullptr);
    other.size_stack = 0;
  };

  stack(const stack &other) {
    stack<value_type> buffer;
    for (node *i = other.m_tail; i != nullptr;) {
      buffer.push(i->data);
      i = i->prev;
    }
    for (node *i = buffer.m_tail; i != nullptr;) {
      this->push(i->data);
      i = i->prev;
    }
  };

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    list<value_type> tmp{std::forward<Args>(args)...};
    for (auto i = tmp.begin(); i != tmp.end(); i++) this->push(*i);
  }
  size_type size() const { return size_stack; };
};
}  // namespace s21