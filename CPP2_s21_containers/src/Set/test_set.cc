#include <gtest/gtest.h>

#include "s21_set.h"

TEST(set_test, EmptyConstructor_1) {
  s21::set<int> sets;
  EXPECT_EQ(sets.empty(), 1);
  EXPECT_EQ(sets.size(), 0);
};

TEST(set_test, Constructor_1) {
  s21::set<int> sets({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -1}), sets_clone(sets);
  EXPECT_EQ(sets.empty(), sets_clone.empty());
  EXPECT_EQ(sets.size(), sets_clone.size());
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets.contains(i), 1);
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets_clone.contains(i), 1);
  auto j = sets_clone.begin();
  for (auto i = sets.begin(); i != sets.end(); i++) {
    EXPECT_EQ(*i, *j);
    j++;
  }
};
TEST(set_test, Constructor_2) {
  s21::set<int> sets({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -1}), sets_clone(sets),
      sets_move(std::move(sets));
  EXPECT_EQ(sets.empty(), 1);
  EXPECT_EQ(sets.size(), 0);
  EXPECT_EQ(sets_move.empty(), sets_clone.empty());
  EXPECT_EQ(sets_move.size(), sets_clone.size());
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets_move.contains(i), 1);
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets_clone.contains(i), 1);
  auto j = sets_clone.begin();
  for (auto i = sets_move.begin(); i != sets_move.end(); i++) {
    EXPECT_EQ(*i, *j);
    j++;
  }
};
TEST(set_test, Constructor_3) {
  s21::set<int> sets({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -1}), sets_clone;
  sets_clone = sets;
  EXPECT_EQ(sets.empty(), sets_clone.empty());
  EXPECT_EQ(sets.size(), sets_clone.size());
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets.contains(i), 1);
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets_clone.contains(i), 1);
  auto j = sets_clone.begin();
  for (auto i = sets.begin(); i != sets.end(); i++) {
    EXPECT_EQ(*i, *j);
    j++;
  }
};
TEST(set_test, Constructor_4) {
  s21::set<int> sets({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -1}), sets_clone;
  sets_clone = sets;
  EXPECT_EQ(sets.empty(), sets_clone.empty());
  EXPECT_EQ(sets.size(), sets_clone.size());
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets.contains(i), 1);
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets_clone.contains(i), 1);
  auto j = sets_clone.begin();
  for (auto i = sets.begin(); i != sets.end(); i++) {
    EXPECT_EQ(*i, *j);
    j++;
  }
};
TEST(set_test, clear) {
  s21::set<int> sets({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -1}), sets_clone;
  sets_clone = sets;
  EXPECT_EQ(sets.empty(), sets_clone.empty());
  EXPECT_EQ(sets.size(), sets_clone.size());
  sets.clear();
  sets_clone.clear();
  EXPECT_EQ(sets.empty(), sets_clone.empty());
  EXPECT_EQ(sets.size(), sets_clone.size());
};

TEST(set_test, swap) {
  s21::set<int> sets({1, 2, 3, 4, 5, 6, 7, 8, 9, 0}),
      sets_clone({-1, -2, -3, -4, -5, -6, -7, -8, -9, 0});
  EXPECT_EQ(sets.empty(), sets_clone.empty());
  EXPECT_EQ(sets.size(), sets_clone.size());
  for (int i = 0; i < 10; i++) EXPECT_EQ(sets.contains(i), 1);
  for (int i = 0; i > -10; i--) EXPECT_EQ(sets_clone.contains(i), 1);
  sets.swap(sets_clone);
  for (int i = 0; i < 10; i++) EXPECT_EQ(sets_clone.contains(i), 1);
  for (int i = 0; i > -10; i--) EXPECT_EQ(sets.contains(i), 1);
};

TEST(set_test, merge) {
  s21::set<int> sets({1, 3, 4, 5, 7, 10, 11, 12, 13}),
      sets_m({1, 2, 3, 4, 5, 6, 7, 9, 10, 14});
  EXPECT_EQ(sets.empty(), 0);
  EXPECT_EQ(sets_m.empty(), 0);
  EXPECT_EQ(sets.size(), 9);
  EXPECT_EQ(sets_m.size(), 10);
  sets.merge(sets_m);
  EXPECT_EQ(sets.size(), 13);
  EXPECT_EQ(sets_m.size(), 6);
};

TEST(set_test, insert_many) {
  s21::set<int> sets({1, 2, 6, 7, 8, 9});
  sets.insert_many(3, 4, 5);
  for (int i = 1; i < 10; i++) EXPECT_EQ(sets.contains(i), 1);
};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};