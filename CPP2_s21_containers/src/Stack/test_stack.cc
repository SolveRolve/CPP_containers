
#include <gtest/gtest.h>

#include <stack>

#include "s21_stack.h"

TEST(stack_test, EmptyConstructor_1) {
  s21::stack<int> l;
  EXPECT_EQ(l.empty(), 1);
};
TEST(stack_test, EmptyConstructor_2) {
  s21::stack<long> l;
  EXPECT_EQ(l.empty(), 1);
};
TEST(stack_test, EmptyConstructor_3) {
  s21::stack<bool> l;
  EXPECT_EQ(l.empty(), 1);
};

TEST(stack_test, initializer_list) {
  s21::stack<int> l({1, 2, 3, 4, 5, 6, 7});
  std::stack<int> ll({1, 2, 3, 4, 5, 6, 7});
  EXPECT_EQ(l.size(), ll.size());
  while (!l.empty()) {
    EXPECT_EQ(l.top(), ll.top());
    l.pop();
    ll.pop();
  }
};

TEST(stack_test, swap) {
  s21::stack<int> l({1, 2, 3, 4, 5, 6, 7}), k({1, 1, 1, 1, 1});
  std::stack<int> ll({1, 2, 3, 4, 5, 6, 7}), kk({1, 1, 1, 1, 1});
  EXPECT_EQ(l.size(), ll.size());
  l.swap(k);
  ll.swap(kk);
  while (!l.empty()) {
    EXPECT_EQ(l.top(), ll.top());
    l.pop();
    ll.pop();
  }
};

TEST(stack_test, CopyConstructor) {
  s21::stack<int> l({1, 2, 3, 4, 5, 6, 7}), l_copy(l);

  EXPECT_EQ(l.size(), l_copy.size());
  while (!l.empty()) {
    EXPECT_EQ(l.top(), l_copy.top());
    l.pop();
    l_copy.pop();
  }
};

TEST(stack_test, MoveConstructor) {
  s21::stack<int> l({1, 2, 3, 4, 5, 6, 7}), l_copy(l), l_move;
  l_move = std::move(l);
  EXPECT_EQ(l_move.size(), l_copy.size());
  EXPECT_EQ(l.size(), 0);
  while (!l_move.empty()) {
    EXPECT_EQ(l_move.top(), l_copy.top());
    l_move.pop();
    l_copy.pop();
  }
};

TEST(stack_test, insert_many) {
  s21::stack<int> v({7, 8, 9, 10});
  v.insert_many_front(11, 12, 13, 14);  //
  int j = 14;
  while (!v.empty()) {
    EXPECT_EQ(v.top(), j--);
    v.pop();
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};