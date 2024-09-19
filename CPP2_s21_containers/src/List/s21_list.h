#include <cmath>
#include <iostream>

namespace s21 {
template <typename T>
class list {
 public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  struct node {
    value_type data;
    node *next = nullptr;
    node *prev = nullptr;
  };

 private:
  node *m_tail = nullptr;
  node *m_head = nullptr;

 public:
  list() {
    m_tail = nullptr;
    m_head = nullptr;
  };

  node *GetTail() { return m_tail; }
  node *GetHead() { return m_head; }
  void SetTail(node *const ptr) { m_tail = ptr; }
  void SetTai(node *ptr) { m_tail = ptr; }
  void SetHead(node *const ptr) { m_head = ptr; }
  const_reference front() { return this->m_head->data; };
  const_reference back() { return this->m_tail->data; };

  size_type max_size() const noexcept {
    return (pow(2, 64)) / sizeof(value_type) - 1;
  };

  void clear() {
    for (node *p = m_head, *next = m_head; p != nullptr; p = next) {
      next = p->next;
      p->data = 0;
    };
  }

  list &swap(list &other) {
    auto buff(other);
    other = *this;
    *this = buff;
    return *this;
  };

 public:
  template <bool Const>

  class Iteratorlist {
    friend class list;
    friend class Iteratorlist<!Const>;

    using node_pointer = std::conditional_t<Const, const node *, node *>;

   private:
    node_pointer ptr;

    explicit Iteratorlist(node_pointer p) : ptr(p){};

   public:
    using value_type = list::value_type;
    using reference = list::reference;

    const_reference operator*() const noexcept { return ptr->data; }
    const node *getPtr() const { return ptr; }
    auto &operator++() noexcept {
      if (ptr) ptr = ptr->next;
      return *this;
    }

    auto operator++(int) noexcept {
      auto tmp = ptr;
      if (ptr) ptr = ptr->next;
      return Iteratorlist{tmp};
    }

    Iteratorlist &operator--() noexcept {
      if (ptr) ptr = ptr->prev;
      return *this;
    }
    Iteratorlist &operator+(const int b) {
      for (int i = 0; i < b; i++) {
        (*this)++;
      }
      return *this;
    }
    Iteratorlist &operator-(const int b) {
      for (int i = 0; i < b; i++) {
        (*this)--;
      }
      return *this;
    }
    Iteratorlist operator--(int) noexcept {
      auto tmp = ptr;
      if (ptr) ptr = ptr->prev;
      return Iteratorlist{tmp};
    }

    template <bool R>
    bool operator==(const Iteratorlist<R> &other) {
      return this->ptr == other.ptr;
    }

    template <bool R>
    bool operator!=(const Iteratorlist<R> &other) {
      return !(this->ptr == other.ptr);
    }

    operator Iteratorlist<true>() const { return Iteratorlist<true>{ptr}; }
  };

  using const_iterator = Iteratorlist<true>;
  using iterator = Iteratorlist<false>;
  iterator begin() { return iterator{m_head}; }
  iterator end() { return iterator{nullptr}; }
  iterator rbegin() { return iterator{m_tail}; }
  iterator rend() { return iterator{nullptr}; }
  const_iterator begin() const { return iterator{m_head}; }
  const_iterator end() const { return iterator{nullptr}; }

  iterator insert(iterator pos, const_reference value) {
    node *newnode = new node;
    newnode->data = value;
    newnode->prev = pos.ptr;
    newnode->next = pos.ptr->next;
    pos.ptr->next = newnode;
    if (!pos.ptr->next) this->SetTail(newnode);
    return iterator{newnode};
  };

  void erase(iterator pos) {
    auto node_next = pos.ptr->next;
    auto node_prev = pos.ptr->prev;
    if (node_prev)
      node_prev->next = node_next;
    else
      this->SetHead(node_next);
    if (node_next)
      node_next->prev = node_prev;
    else
      this->SetTail(node_prev);
    delete pos.ptr;
    pos.ptr = node_next;
  };

  void reverse() {
    if (this->size() > 1) {
      list<value_type> copy_list(*this);
      this->~list();
      for (auto i = copy_list.rbegin(); i != copy_list.rend(); i--) {
        this->push_back(*i);
      }
    }
  };

  iterator min() {
    auto remainder = this->begin();
    for (auto i = this->begin(); i != this->end(); i++) {
      if (*remainder > *i) remainder = i;
    }
    return remainder;
  };

  void sort() {
    list<value_type> temp;
    while (!this->empty()) {
      auto minimum = this->min();
      temp.push_back(*minimum);
      this->erase(minimum);
    }
    *this = std::move(temp);
  };

  void splice(const_iterator pos, list &other) {
    auto j = this->begin();
    for (; j != this->end(); j++) {
      if (pos == j) break;
    }
    for (auto i = other.begin(); i != other.end(); i++, j++) {
      this->insert(j, *i);
      other.erase(i);
    }
  };

  void merge(list &other) {
    list<value_type> temp;
    auto j = other.begin();
    auto i = this->begin();
    for (; i != this->end() && j != this->end();) {
      if (*i > *j) {
        temp.push_back(*j), j++;
      } else if (*i == *j) {
        temp.push_back(*j), j++;
        temp.push_back(*i), i++;
      } else {
        temp.push_back(*i), i++;
      }
    }
    while (j != this->end()) temp.push_back(*j), j++;
    while (i != this->end()) this->push_back(*i), i++;

    *this = std::move(temp);
  }

  void unique() {
    list<value_type> temp(*this);
    int count = 0;
    for (auto i = this->begin(); i != this->end(); i++) {
      count = 0;
      for (auto j = temp.begin(); j != temp.end(); j++) {
        if (*i == *j) count++;
        if (count == 2) {
          temp.erase(j);
          count = 0;
        }
      }
    }
    *this = std::move(temp);
  };

  ~list() {
    while (m_head) {
      node *move = m_head;
      m_head = m_head->next;
      delete move;
    }
    this->SetHead(nullptr);
    this->SetTail(nullptr);
  };

  bool empty() {
    return (this->GetTail() == nullptr) && (this->GetHead() == nullptr) ? 1 : 0;
  };

  list &operator=(list const &other) {
    this->~list();
    for (auto i = other.begin(); i != other.end(); i++) {
      this->push_back(*i);
    }
    return *this;
  };

  list &operator=(list &&other) {
    this->~list();
    this->SetHead(other.GetHead());
    this->SetTail(other.GetTail());
    other.SetHead(nullptr);
    other.SetTail(nullptr);
    return *this;
  };

  list(value_type n) {
    for (auto i = 0; i < n; i++) {
      this->push_back(0);
    }
  };

  void push_back(value_type value) {
    s21::list<T>::node *newnode = new node;
    newnode->data = value;
    if (m_tail) {
      m_tail->next = newnode;
      newnode->prev = m_tail;
      m_tail = newnode;
    } else {
      m_head = newnode;
      m_tail = newnode;
    }
  };

  void push_front(const_reference value) {
    node *newnode = new node{value, nullptr};
    newnode->data = value;
    if (m_tail) {
      m_head->prev = newnode;
      newnode->next = m_head;
      m_head = newnode;
    } else {
      m_head = m_tail = newnode;
    }
  };

  void pop_front() {
    if (m_head) {
      node *tmp = m_head;
      this->m_head = this->m_head->next;
      this->m_head->prev = nullptr;
      delete tmp;
    } else
      throw std::out_of_range("pop_front not have head");
  };

  void pop_back() {
    if (m_tail) {
      node *tmp = m_tail;
      this->m_tail = this->m_tail->prev;
      this->m_tail->next = nullptr;
      delete tmp;
    } else
      throw std::out_of_range("pop_back not have tail");
  };

  list(std::initializer_list<value_type> items) {
    for (auto &item : items) push_back(item);
  };

  list(list &&other) {
    this->SetHead(other.GetHead());
    this->SetTail(other.GetTail());
    other.SetHead(nullptr);
    other.SetTail(nullptr);
  };

  list(const list &l) {
    for (auto i = l.begin(); i != l.end(); i++) {
      this->push_back(*i);
    }
  };

  size_type size() const {
    size_type amount{0};
    for (auto i = this->begin(); i != this->end(); i++) amount++;
    return amount;
  };
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    list<value_type> tmp{std::forward<Args>(args)...};
    splice(pos, tmp);
    auto pos_copy = this->begin();
    for (; pos_copy != pos;) pos_copy++;
    return pos_copy + sizeof...(args);
  }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    this->insert_many(this->rbegin(), args...);
  }
  template <typename... Args>
  void insert_many_front(Args &&...args) {
    list<value_type> tmp{std::forward<Args>(args)...};
    for (auto i = tmp.begin(); i != tmp.end(); i++) this->push_front(*i);
  }
};
};  // namespace s21
