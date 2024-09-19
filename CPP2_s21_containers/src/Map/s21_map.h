#ifndef CPP2_S21_CONTAINERS_S21_map_H_
#include "../Tree_rb/tree_rb.h"
#define CPP2_S21_CONTAINERS_S21_map_H_
#include <cmath>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

namespace s21 {
template <typename key_, typename T>
class map {
 public:
  using tree_type = Tree<key_, T>;
  using key_type = key_;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using key_reference = key_ &;
  using key_const_reference = const key_ &;
  using size_type = size_t;
  using iterator = typename tree_type::template IteratorTree<false>;
  using const_iterator = typename tree_type::template IteratorTree<true>;

 private:
  tree_type *tree_;

 public:
  map() : tree_(new tree_type()){};
  map(const map &other) : tree_(new tree_type(*other.tree_)){};
  map(map &&other) : tree_(std::move(other.tree_)) { other.tree_ = nullptr; };
  ~map() { delete tree_; };
  map operator=(const map &other) {
    if (this != &other) {
      *tree_ = *(other.tree_);
    }
    return *this;
  };
  std::pair<iterator, bool> insert(const value_type &value) {
    bool result = 0;
    iterator iter = find(value.first);
    if (tree_->find(value.first) == tree_->getnil()) {
      iter = tree_->insert(value.first, value.second);
      result = 1;
    }
    return {iter, result};
  }
  size_type max_size() const noexcept {
    return (pow(2, 64)) / sizeof(value_type) - 1;
  };
  map(std::initializer_list<value_type> const &items) : tree_(new tree_type()) {
    for (auto &&item : items) insert(item);
  };
  std::pair<iterator, bool> insert(key_const_reference key,
                                   const mapped_type &obj) {
    auto pair_ = std::pair{key, obj};
    auto pair = insert(pair_);
    if (!pair.second) pair.first = this->tree_->getNil();
    return pair;
  };
  std::pair<iterator, bool> insert_or_assign(key_const_reference key,
                                             const mapped_type &obj) {
    auto pair = insert({key, obj});
    return pair;
  };
  mapped_type &operator[](key_const_reference key) {
    insert({key, mapped_type{}});
    return (this->tree_->getMap(find(key)));
  }
  mapped_type &at(key_const_reference key) {
    if (find(key).getPtr() == tree_->getNil()) {
      std::cout << key;
      throw std::out_of_range("map don't have this key");
    }
    return (this->tree_->getMap(find(key)));
  }
  void print() { tree_->PrintTreeMap(); };
  size_type size() { return tree_ != nullptr ? tree_->size() : 0; }
  bool empty() { return size() == 0 ? 1 : 0; }
  iterator begin() { return tree_->begin(); }
  iterator end() { return tree_->end(); }
  iterator find(const key_type &key) { return iterator{tree_->find(key)}; };
  bool contains(const key_type &key) {
    return (tree_->find(key) != tree_->getnil());
  };
  void clear() {
    delete tree_;
    tree_ = new tree_type();
  }
  void erase(iterator pos) { tree_->erase(pos); };
  void swap(map &other) { std::swap(this->tree_, other.tree_); }
  void merge(map &other) {
    for (auto i = other.begin(); i != other.end(); i++) {
      std::pair res = this->insert(*i, other.at(*i));
      if (res.second) other.erase(i);
    };
  };

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> res;
    (..., res.push_back(this->insert(std::forward<Args>(args))));
    return res;
  }
};
};  // namespace s21

// namespace s21
#endif  // CPP2_S21_CONTAINERS_S21_map_H_