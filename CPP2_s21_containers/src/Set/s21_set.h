#ifndef CPP2_S21_CONTAINERS_S21_SET_H_
#include "../Tree_rb/tree_rb.h"
#define CPP2_S21_CONTAINERS_S21_SET_H_
#include <cmath>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
namespace s21 {
template <typename T>
class set {
 public:
  using tree_type = Tree<T, T>;
  using key_type = T;
  using value_type = T;
  using key_reference = T &;
  using key_const_reference = const T &;
  using size_type = size_t;
  using iterator = typename tree_type::template IteratorTree<false>;
  using const_iterator = typename tree_type::template IteratorTree<true>;

 private:
  tree_type *tree_;

 public:
  set() : tree_(new tree_type()){};
  set(const set &other) : tree_(new tree_type(*other.tree_)){};
  set(set &&other) : tree_(std::move(other.tree_)) { other.tree_ = nullptr; };
  ~set() { delete tree_; };
  set operator=(const set &other) {
    if (this != &other) {
      *tree_ = *(other.tree_);
    }
    return *this;
  };
  std::pair<iterator, bool> insert(const value_type &value) {
    bool result = 0;
    iterator iter = tree_->getnil();
    if (tree_->find(value) == tree_->getnil()) {
      iter = tree_->insert(value);
      result = 1;
    }
    return {iter, result};
  }
  size_type max_size() const noexcept {
    return (pow(2, 64)) / sizeof(value_type) - 1;
  };
  set(std::initializer_list<key_type> const &items) : tree_(new tree_type()) {
    for (auto &&item : items) insert(item);
  };
  void print() { tree_->PrintTree(); }
  size_type size() { return tree_ != nullptr ? tree_->size() : 0; }
  bool empty() { return size() == 0 ? 1 : 0; }
  iterator begin() { return tree_->begin(); }
  iterator end() { return tree_->end(); }
  iterator find(const value_type &key) { return iterator{tree_->find(key)}; };
  bool contains(const value_type &key) {
    return (tree_->find(key) != tree_->getnil());
  };
  void clear() {
    delete tree_;
    tree_ = new tree_type();
  }
  void erase(iterator pos) { tree_->erase(pos); };
  void swap(set &other) { std::swap(this->tree_, other.tree_); }
  void merge(set &other) {
    for (auto i = other.begin(); i != other.end(); i++) {
      std::pair res = this->insert(*i);
      if (res.second) other.erase(i);
    }
  };
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> res;
    (..., res.push_back(this->insert(std::forward<Args>(args))));
    return res;
  }
};

};      // namespace s21
#endif  // CPP2_S21_CONTAINERS_S21_SET_H_