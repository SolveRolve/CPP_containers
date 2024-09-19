

#include <gtest/gtest.h>

#include "s21_queue.h"

TEST(queue_test, DefaultConstructor_1) {
  s21::queue<int> l;
  EXPECT_EQ(l.empty(), 1);
};
TEST(queue_test, size) {
  s21::queue<int> l({1, 2, 3, 4, 5});
  EXPECT_EQ(l.size(), 5);
};
TEST(queue_test, CopyConst) {
  s21::queue<int> l({1, 2, 3, 4, 5}), k(l);
  EXPECT_EQ(k.size(), 5);
};
TEST(queue_test, move) {
  s21::queue<int> l({1, 2, 3, 4, 5}), k;
  k = std::move(l);
  EXPECT_EQ(k.size(), 5);
  EXPECT_EQ(l.size(), 0);
};
TEST(queue_test, move_2) {
  s21::queue<int> l({1, 2, 3, 4, 5}), k(std::move(l));
  EXPECT_EQ(k.size(), 5);
  EXPECT_EQ(l.size(), 0);
};
TEST(queue_test, swap) {
  s21::queue<int> l({1, 2, 3, 4, 5}), k({0, 0, 0});
  k.swap(l);
  EXPECT_EQ(k.size(), 5);
  EXPECT_EQ(l.size(), 3);
};
TEST(queue_test, frontback) {
  s21::queue<int> l({1, 2, 3, 4, 5});
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 5);
};
TEST(queue_test, pushpops) {
  s21::queue<int> l;
  l.push(1);
  l.push(2);
  l.push(3);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 3);
  l.pop();
  EXPECT_EQ(l.back(), 2);
};

TEST(Vector, insert_many) {
  s21::queue<int> v({7, 8, 9, 10});

  v.insert_many_back(11, 12, 13, 14);  //
  int j = 14;
  while (!v.empty()) {
    EXPECT_EQ(v.back(), j--);
    v.pop();
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};
