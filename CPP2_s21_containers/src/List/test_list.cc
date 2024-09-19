
#include <gtest/gtest.h>

#include "s21_list.h"

TEST(list_test, DefaultConstructor_1) {
  s21::list<int> l;
  EXPECT_EQ(l.empty(), 1);
};
TEST(list_test, size) {
  s21::list<int> l({1, 2, 3, 4, 5});
  EXPECT_EQ(l.size(), 5);
};
TEST(list_test, CopyConst) {
  s21::list<int> l({1, 2, 3, 4, 5}), k(l);
  EXPECT_EQ(k.size(), 5);
};
TEST(list_test, move) {
  s21::list<int> l({1, 2, 3, 4, 5}), k;
  k = std::move(l);
  EXPECT_EQ(k.size(), 5);
  EXPECT_EQ(l.size(), 0);
};
TEST(list_test, swap) {
  s21::list<int> l({1, 2, 3, 4, 5}), k({0, 0, 0});
  k.swap(l);
  EXPECT_EQ(k.size(), 5);
  EXPECT_EQ(l.size(), 3);
};
TEST(list_test, clear) {
  s21::list<int> l({1, 1, 1, 1, 1});
  for (auto i : l) EXPECT_EQ(i, 1);
  l.clear();
  for (auto i : l) EXPECT_EQ(i, 0);
};
TEST(list_test, list_n) {
  s21::list<int> l(5);
  for (auto i : l) EXPECT_EQ(i, 0);
};
TEST(list_test, insert) {
  s21::list<int> l({1, 1, 1, 1, 1}), ll({1, 2, 1, 1, 1, 1});
  auto i = l.begin();
  l.insert(i, 2);
  for (auto i = l.begin(), j = ll.begin(); i != l.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
};
TEST(list_test, sort) {
  s21::list<int> l({-1, 2, 4, 0, 10, 2}), ll({-1, 0, 2, 2, 4, 10});
  l.sort();
  for (auto i = l.begin(), j = ll.begin(); i != l.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
};
TEST(list_test, splice) {
  s21::list<int> l({1, 2, 6, 7, 8, 9}), lll({3, 4, 5});
  auto i = l.begin();
  i++;
  l.splice(i, lll);
  EXPECT_EQ(l.size(), 9);
  int j = 0;
  for (auto i : lll) {
    EXPECT_EQ(i, j++);
  }
};
TEST(list_test, merge) {
  s21::list<int> l({1, 3, 5, 7, 9}), ll({0, 2, 4, 6, 8, 9, 10, 11}),
      lll({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10, 11});
  l.merge(ll);
  for (auto i = lll.begin(), j = l.begin(); i != l.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
};

TEST(list_test, front_back) {
  s21::list<int> l({1, 3, 5, 7, 9});
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 9);
};

TEST(list_test, pops) {
  s21::list<int> l({1, 3, 5, 7, 9});
  l.pop_back();
  l.pop_front();
  EXPECT_EQ(l.front(), 3);
  EXPECT_EQ(l.back(), 7);
};
TEST(list_test, pushs) {
  s21::list<int> l({1, 3, 5, 7, 9});
  EXPECT_EQ(l.front(), 1);
  l.push_front(4);
  EXPECT_EQ(l.front(), 4);
};

TEST(list_test, reverse) {
  s21::list<int> l({1, 2, 3, 4, 5}), ll({5, 4, 3, 2, 1});
  l.reverse();
  for (auto i = l.begin(), j = ll.begin(); i != l.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
};
TEST(list_test, unique) {
  s21::list<int> l(
      {1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 5, 6, 7, 7, 7, 8, 8, 8}),
      ll({1, 2, 3, 4, 5, 6, 7, 8});
  l.unique();
  for (auto i = l.begin(), j = ll.begin(); i != l.end(); i++, j++) {
    EXPECT_EQ(*i, *j);
  }
};

TEST(list_test, insert_many) {
  s21::list<int> l({0, 0, 0, 0, 0, 0}), ll({5, 4, 3, 2, 1});
  auto k = l.insert_many(l.begin()++, 1, 2, 3, 4, 5, 6, 7, 8, 9);
  EXPECT_EQ(*k, 9);
  l.insert_many_back(0, 0, 0, 0, 0, 0, 0);
  l.insert_many_front(1, 1, 1, 1, 1);
  int res[27] = {1, 1, 1, 1, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8,
                 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int j = 0;
  for (auto i : l) EXPECT_EQ(i, res[j++]);
};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};
