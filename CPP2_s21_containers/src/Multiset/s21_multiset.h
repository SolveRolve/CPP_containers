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
class multiset {
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
  multiset() : tree_(new tree_type()){};
  multiset(const multiset &other) : tree_(new tree_type(*other.tree_)){};
  multiset(multiset &&other) : tree_(std::move(other.tree_)) {
    other.tree_ = nullptr;
  };
  ~multiset() { delete tree_; };
  multiset operator=(const multiset &other) {
    if (this != &other) {
      *tree_ = *(other.tree_);
    }
    return *this;
  };
  std::pair<iterator, bool> insert_true(const value_type &value) {
    return {tree_->insert(value), 1};
  };
  iterator insert(const value_type &value) { return tree_->insert(value); };
  multiset(std::initializer_list<key_type> const &items)
      : tree_(new tree_type()) {
    for (auto &&item : items) insert(item);
  };
  size_type max_size() const noexcept {
    return (pow(2, 64)) / sizeof(value_type) - 1;
  };
  void print() { tree_->PrintTree(); }
  size_type size() { return tree_ != nullptr ? tree_->size() : 0; }
  bool empty() { return size() == 0 ? 1 : 0; }
  iterator begin() { return tree_->begin(); }
  iterator end() { return tree_->end(); }
  iterator rbegin() { return tree_->rbegin(); }
  iterator rend() { return tree_->rend(); }
  iterator find(const value_type &key) { return iterator{tree_->find(key)}; };
  bool contains(const value_type &key) {
    return (tree_->find(key) != tree_->getnil());
  };
  void clear() {
    delete tree_;
    tree_ = new tree_type();
  }
  void erase(iterator pos) { tree_->erase(pos); };
  void swap(multiset &other) { std::swap(this->tree_, other.tree_); }
  void merge(multiset &other) {
    for (auto i = other.begin(); i != other.end(); i++) {
      std::pair res = this->insert_true(*i);
      if (res.second) other.erase(i);
    }
  };
  std::pair<iterator, iterator> equal_range(key_const_reference key) {
    iterator last = this->find(key);
    iterator first = last;
    last++;
    for (auto i = this->rbegin(); i != this->rend(); --i)
      if (*i == key) {
        first = i;
      }

    return {first, last};
  }
  iterator lower_bound(key_const_reference key) {
    iterator lower = this->begin();
    for (auto i = lower; i != this->end(); i++) {
      if (key <= *i) {
        lower = i;
        break;
      }
    }
    return lower;
  }
  iterator upper_bound(key_const_reference key) {
    iterator upper = this->begin();
    for (auto i = upper; i != this->end(); i++) {
      if (key < *i) {
        upper = i;
        break;
      }
    }
    return upper;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> res;

    (..., res.push_back(this->insert_true(std::forward<Args>(args))));
    return res;
  }
};

};      // namespace s21
#endif  // CPP2_S21_CONTAINERS_S21_SET_H_