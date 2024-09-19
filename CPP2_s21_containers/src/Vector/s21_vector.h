
#ifndef CPP2_S21_CONTAINERS_1_S21_VECTOR_H
#define CPP2_S21_CONTAINERS_1_S21_VECTOR_H

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>

class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  vector() : data_(nullptr), size_(0), max_size_(0) {}

  explicit vector(size_type n) {
    if (n > max_size())
      throw std::length_error(
          "cannot create s21::vector larger than max_size()");
    data_ = new value_type[n];
    size_ = 0;
    max_size_ = n;
  }

  vector(const vector& v) noexcept
      : data_(new T[v.size_]), size_(v.size_), max_size_(v.max_size_) {
    std::copy(v.data_, v.data_ + v.size_, data_);
  }
  vector(vector&& v) noexcept {
    if (&v != this) {
      this->data_ = std::move(v.data_);
      this->size_ = v.size_;
      this->max_size_ = v.max_size_;
      v.data_ = nullptr;
      v.size_ = 0;
      v.max_size_ = 0;
    }
  }
  vector(const std::initializer_list<value_type>& items) {
    for (auto i : items) {
      push_back(i);
    }
  }
  ~vector() { delete[] data_; };

  template <bool Const>
  class Iterator {
   public:
    friend class vector;
    friend class Iterator<!Const>;

    using data_pointer =
        std::conditional_t<Const, const value_type*, value_type*>;

    explicit Iterator(data_pointer p) : iterator_pointer(p){};

    ~Iterator() = default;

    Iterator operator++(int) noexcept {
      Iterator tmp = *this;
      ++iterator_pointer;
      return tmp;
    }

    Iterator& operator++() noexcept {
      ++iterator_pointer;
      return *this;
    }

    Iterator operator--(int) noexcept {
      Iterator tmp = *this;
      --iterator_pointer;
      return tmp;
    }

    Iterator& operator--() noexcept {
      --iterator_pointer;
      return *this;
    }

    Iterator operator+(long unsigned int value) {
      this->iterator_pointer += value;
      return *this;
    }

    Iterator operator-(const size_type value) {
      iterator_pointer = iterator_pointer - value;
      return *this;
    }

    size_type operator-(const Iterator value) {
      size_type k = iterator_pointer - value.iterator_pointer;

      return k;
    }

    value_type& operator*() const { return *iterator_pointer; }
    value_type* operator->() const { return iterator_pointer; }

    template <bool R>
    bool operator==(const Iterator<R>& other) const {
      return this->iterator_pointer == other.iterator_pointer;
    }

    template <bool R>
    bool operator!=(const Iterator<R>& other) const {
      return !(this->iterator_pointer == other.iterator_pointer);
    }

    template <bool R>
    bool operator<(const Iterator<R>& other) const {
      return this->iterator_pointer < other.iterator_pointer;
    }

    template <bool R>
    bool operator>(const Iterator<R>& other) const {
      return this->iterator_pointer > other.iterator_pointer;
    }

    template <bool R>
    bool operator<=(const Iterator<R>& other) const {
      return this->iterator_pointer <= other.iterator_pointer;
    }

    template <bool R>
    bool operator>=(const Iterator<R>& other) const {
      return this->iterator_pointer >= other.iterator_pointer;
    }

    operator Iterator<true>() const { return Iterator<true>{iterator_pointer}; }

   private:
    friend class vector;
    data_pointer iterator_pointer;
  };

  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;

  vector& operator=(vector&& v) noexcept {
    if (this != &v) {
      delete[] data_;
      data_ = v.data_;
      size_ = v.size_;
      max_size_ = v.max_size_;
      v.data_ = nullptr;
      v.size_ = 0;
      v.max_size_ = 0;
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("Index out of range");
    }

    value_type& element_ptr = *(this->begin() + pos);
    return element_ptr;
  }

  value_type& operator[](size_type pos) {
    value_type& reference = *(this->begin() + pos);
    return reference;
  }

  const_reference front() const {
    if (empty()) {
      throw std::out_of_range("vector is empty");
    }
    return *data_;
  }
  const_reference back() const {
    if (empty()) {
      throw std::out_of_range("vector is empty");
    }
    return data_[size_ - 1];
  }

  iterator data() noexcept { return iterator{data_}; }

  iterator begin() { return iterator{data_}; }
  iterator end() { return iterator{data_ + size_}; }

  bool empty() const noexcept { return size_ == 0; }
  size_type size() const noexcept { return size_; }
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(data_);
  }
  void reserve(size_t new_capacity) {
    if (new_capacity > this->max_size()) new_capacity = this->max_size();

    if (new_capacity < size_) {
      throw std::length_error("Container size exceeds maximum capacity");
    }

    value_type* new_data = new value_type[new_capacity];

    if (data_ != nullptr) {
      std::copy(data_, data_ + size_, new_data);
    }

    delete[] data_;

    data_ = new_data;
    max_size_ = new_capacity;
  }
  size_type capacity() const noexcept { return max_size_; };
  void shrink_to_fit() {
    if (size_ == 0) {
      delete[] data_;
      data_ = nullptr;
      max_size_ = 0;
    } else if (size_ < max_size_) {
      value_type* new_data = new value_type[size_];
      std::copy(data_, data_ + size_, new_data);

      delete[] data_;
      data_ = new_data;
      max_size_ = size_;
    }
  }

  void clear() {
    delete[] data_;
    size_ = 0;
    max_size_ = 0;
    data_ = nullptr;
  }

  iterator insert(iterator pos, const_reference value) {
    int position = pos - this->begin();
    s21::vector<value_type> buffer(size_ + 2);

    for (auto i = this->begin(); i != this->end(); i++) {
      if (i != pos)
        buffer.push_back(*i);
      else {
        buffer.push_back(value);
        buffer.push_back(*i);
      }
    }

    *this = std::move(buffer);
    auto i = this->begin() + position;

    return i;
  }

  void erase(iterator pos) {
    while (pos < end() - 1) {
      *(pos.iterator_pointer) = *(pos.iterator_pointer + 1);
      pos++;
    }
    size_--;
  }

  void push_back(const_reference value) {
    if (max_size_ == 0) {
      data_ = new value_type;
      max_size_++;
    }
    if (size_ == max_size_) {
      reserve(max_size_ * 2);
    }

    *(data_ + size_++) = value;
  }
  void pop_back() {
    if (empty()) {
      throw std::out_of_range("vector is empty");
    }
    if constexpr (std::is_pointer_v<value_type>) {
      delete data_[size_];
    }
    --size_;
  }
  void swap(vector& other) {
    std::swap(data_, other.data_);
    std::swap(max_size_, other.max_size_);
    std::swap(size_, other.size_);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    vector<value_type> tmp{std::forward<Args>(args)...};
    int num = 0;
    for (auto i = this->begin(); i != pos; i++) {
      num++;
      if (i == this->end()) break;
    }
    for (auto i : tmp) {
      this->insert(this->begin() + num, i);
      num++;
    }
    return this->begin() + num + sizeof...(args);
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    vector<value_type> tmp{std::forward<Args>(args)...};
    for (auto i = tmp.begin(); i != tmp.end(); i++) {
      this->push_back(*i);
    }
  }

 private:
  value_type* data_;
  size_t size_{0};
  size_t max_size_{0};
};
}  // namespace s21
#endif
