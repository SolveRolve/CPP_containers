#include "../List/s21_list.h"

namespace s21 {
template <typename T>
class queue {
 public:
  // member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  //   using iterator = T*;

 private:
  value_type* data;
  value_type* head;
  value_type* rear;
  size_type capacity, sizeq;

 public:
  queue() {
    data = nullptr, head = nullptr, rear = nullptr;
    capacity = 0;
    sizeq = 0;
  };
  queue(std::initializer_list<value_type> const& items) {
    data = nullptr, head = nullptr, rear = nullptr;
    capacity = 0;
    sizeq = 0;
    for (auto i : items) {
      this->push(i);
    }
  };

  queue(queue&& other) {
    if (this != &other) {
      data = other.data;
      capacity = other.capacity;
      rear = other.rear;
      head = other.head;
      sizeq = other.size();

      other.data = nullptr;
      other.capacity = 0;
      other.rear = nullptr;
      other.head = nullptr;
      other.sizeq = 0;
    }
  };
  ~queue() {
    delete[] data;
    rear = nullptr;
    head = nullptr;
    capacity = 0;
    sizeq = 0;
  };
  queue& operator=(queue&& other) {
    if (this != &other) {
      delete[] data;

      data = other.data;
      capacity = other.capacity;
      rear = other.rear;
      head = other.head;
      sizeq = other.size();

      other.data = nullptr;
      other.capacity = 0;
      other.rear = nullptr;
      other.head = nullptr;
      other.sizeq = 0;
    }
    return *this;
  };

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(data);
  }

  const_reference front() { return *(head); };
  const_reference back() { return *(rear); };

  bool empty() { return sizeq == 0; };
  size_type size() { return sizeq; };

  void push(const_reference value){{

      if (capacity == 0){data = new value_type[1];
  head = rear = data;
  capacity++;
  *(rear) = value;
} else if (size() == capacity) {
  reserve(capacity * 2);
  rear++;
  *(rear) = value;
}
else {
  rear++;
  *(rear) = value;
}
sizeq++;

}  // namespace s21
}
;

void reserve(size_t new_capacity) {
  if (new_capacity < size())
    throw std::length_error("Container size exceeds maximum capacity");

  if (new_capacity > this->max_size()) new_capacity = this->max_size();

  value_type* new_data = new value_type[new_capacity];

  if (data != nullptr) {
    std::copy(data, data + size(), new_data);
  }

  delete[] data;

  head = data = new_data;
  rear = data + sizeq - 1;
  capacity = new_capacity;
}

void pop() {
  if (empty()) {
    throw std::out_of_range("queue is empty");
  }
  rear--;
  sizeq--;
};

void swap(queue& other) {
  std::swap(this->data, other.data);
  std::swap(this->head, other.head);
  std::swap(this->rear, other.rear);
  std::swap(this->sizeq, other.sizeq);
  std::swap(this->capacity, other.capacity);
};

queue(const queue& other) {
  capacity = 0;
  sizeq = 0;
  if (other.data != nullptr) {
    for (value_type* start = other.data; start != other.rear + 1;) {
      this->push(*start);
      start++;
    }
  }
};
template <typename... Args>
void insert_many_back(Args&&... args) {
  list<value_type> tmp{std::forward<Args>(args)...};
  for (auto i = tmp.begin(); i != tmp.end(); i++) this->push(*i);
};
}
;
}
;