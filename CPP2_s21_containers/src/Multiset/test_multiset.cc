#include <gtest/gtest.h>

#include "s21_multiset.h"

TEST(multiset_test, EmptyConstructor_1) {
  s21::multiset<int> multisets;
  EXPECT_EQ(multisets.empty(), 1);
  EXPECT_EQ(multisets.size(), 0);
};

TEST(multiset_test, Constructor_1) {
  s21::multiset<int> multisets({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -1}),
      multisets_clone(multisets);
  EXPECT_EQ(multisets.empty(), multisets_clone.empty());
  EXPECT_EQ(multisets.size(), multisets_clone.size());
  for (int i = -1; i < 10; i++) EXPECT_EQ(multisets.contains(i), 1);
  for (int i = -1; i < 10; i++) EXPECT_EQ(multisets_clone.contains(i), 1);
  auto j = multisets_clone.begin();
  for (auto i = multisets.begin(); i != multisets.end(); i++) {
    EXPECT_EQ(*i, *j);
    j++;
  }
};
TEST(multiset_test, Constructor_2) {
  s21::multiset<int> multisets({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -1}),
      multisets_clone(multisets), multisets_move(std::move(multisets));
  EXPECT_EQ(multisets.empty(), 1);
  EXPECT_EQ(multisets.size(), 0);
  EXPECT_EQ(multisets_move.empty(), multisets_clone.empty());
  EXPECT_EQ(multisets_move.size(), multisets_clone.size());
  for (int i = -1; i < 10; i++) EXPECT_EQ(multisets_move.contains(i), 1);
  for (int i = -1; i < 10; i++) EXPECT_EQ(multisets_clone.contains(i), 1);
  auto j = multisets_clone.begin();
  for (auto i = multisets_move.begin(); i != multisets_move.end(); i++) {
    EXPECT_EQ(*i, *j);
    j++;
  }
};
TEST(multiset_test, Constructor_3) {
  s21::multiset<int> multisets({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -1}),
      multisets_clone;
  multisets_clone = multisets;
  EXPECT_EQ(multisets.empty(), multisets_clone.empty());
  EXPECT_EQ(multisets.size(), multisets_clone.size());
  for (int i = -1; i < 10; i++) EXPECT_EQ(multisets.contains(i), 1);
  for (int i = -1; i < 10; i++) EXPECT_EQ(multisets_clone.contains(i), 1);
  auto j = multisets_clone.begin();
  for (auto i = multisets.begin(); i != multisets.end(); i++) {
    EXPECT_EQ(*i, *j);
    j++;
  }
};
TEST(multiset_test, Constructor_4) {
  s21::multiset<int> multisets({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -1}),
      multisets_clone;
  multisets_clone = multisets;
  EXPECT_EQ(multisets.empty(), multisets_clone.empty());
  EXPECT_EQ(multisets.size(), multisets_clone.size());
  for (int i = -1; i < 10; i++) EXPECT_EQ(multisets.contains(i), 1);
  for (int i = -1; i < 10; i++) EXPECT_EQ(multisets_clone.contains(i), 1);
  auto j = multisets_clone.begin();
  for (auto i = multisets.begin(); i != multisets.end(); i++) {
    EXPECT_EQ(*i, *j);
    j++;
  }
};
TEST(multiset_test, clear) {
  s21::multiset<int> multisets({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -1}),
      multisets_clone;
  multisets_clone = multisets;
  EXPECT_EQ(multisets.empty(), multisets_clone.empty());
  EXPECT_EQ(multisets.size(), multisets_clone.size());
  multisets.clear();
  multisets_clone.clear();
  EXPECT_EQ(multisets.empty(), multisets_clone.empty());
  EXPECT_EQ(multisets.size(), multisets_clone.size());
};

TEST(multiset_test, swap) {
  s21::multiset<int> multisets({1, 2, 3, 4, 5, 6, 7, 8, 9, 0}),
      multisets_clone({-1, -2, -3, -4, -5, -6, -7, -8, -9, 0});
  EXPECT_EQ(multisets.empty(), multisets_clone.empty());
  EXPECT_EQ(multisets.size(), multisets_clone.size());
  for (int i = 0; i < 10; i++) EXPECT_EQ(multisets.contains(i), 1);
  for (int i = 0; i > -10; i--) EXPECT_EQ(multisets_clone.contains(i), 1);
  multisets.swap(multisets_clone);
  for (int i = 0; i < 10; i++) EXPECT_EQ(multisets_clone.contains(i), 1);
  for (int i = 0; i > -10; i--) EXPECT_EQ(multisets.contains(i), 1);
};

TEST(multiset_test, merge) {
  s21::multiset<int> multisets({1, 3, 4, 5, 7, 10, 11, 12, 13}),
      multisets_m({1, 2, 3, 4, 5, 6, 7, 9, 10, 14});
  EXPECT_EQ(multisets.empty(), 0);
  EXPECT_EQ(multisets_m.empty(), 0);
  EXPECT_EQ(multisets.size(), 9);
  EXPECT_EQ(multisets_m.size(), 10);
  multisets.merge(multisets_m);
  EXPECT_EQ(multisets.size(), 19);
  EXPECT_EQ(multisets_m.size(), 0);
};

TEST(multiset_test, insert_many) {
  s21::multiset<int> multisets({1, 2, 6, 7, 8, 9});
  multisets.insert_many(3, 4, 5);
  for (int i = 1; i < 10; i++) EXPECT_EQ(multisets.contains(i), 1);
};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};