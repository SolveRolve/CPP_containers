#include <gtest/gtest.h>

#include "s21_map.h"

TEST(map_test, EmptyConstructor_1) {
  s21::map<int, std::string> sets;
  EXPECT_EQ(sets.empty(), 1);
  EXPECT_EQ(sets.size(), 0);
};

TEST(map_test, Constructor_1) {
  s21::map<int, std::string> sets({{1, "ras"},
                                   {2, "dwa"},
                                   {3, "tri"},
                                   {4, "chetare"},
                                   {5, "pyat"},
                                   {6, "sest"},
                                   {7, "sem"},
                                   {8, "vosem"},
                                   {9, "devayt"},
                                   {0, "nol"},
                                   {-1, "min odin"}}),
      sets_clone(sets);
  EXPECT_EQ(sets.empty(), sets_clone.empty());
  EXPECT_EQ(sets.size(), sets_clone.size());
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets.contains(i), 1);
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets_clone.contains(i), 1);
  auto j = sets_clone.begin();
  for (auto i = sets.begin(); i != sets.end(); i++) {
    EXPECT_EQ(*i, *j);
    j++;
  }
  int i = -1;
  for (auto l : {"min odin", "nol", "ras", "dwa", "tri", "chetare", "pyat",
                 "sest", "sem", "vosem", "devayt"}) {
    EXPECT_EQ(l, sets.at(i));
    EXPECT_EQ(l, sets_clone.at(i));
    i++;
  }
}
TEST(map_test, Constructor_2) {
  s21::map<int, std::string> sets({{1, "ras"},
                                   {2, "dwa"},
                                   {3, "tri"},
                                   {4, "chetare"},
                                   {5, "pyat"},
                                   {6, "sest"},
                                   {7, "sem"},
                                   {8, "vosem"},
                                   {9, "devayt"},
                                   {0, "nol"},
                                   {-1, "min odin"}}),
      sets_clone(sets), sets_move(std::move(sets));
  EXPECT_EQ(sets_move.empty(), sets_clone.empty());
  EXPECT_EQ(sets_move.size(), sets_clone.size());
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets_move.contains(i), 1);
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets_clone.contains(i), 1);
  auto j = sets_clone.begin();
  for (auto i = sets_move.begin(); i != sets_move.end(); i++) {
    EXPECT_EQ(*i, *j);
    j++;
  }
  int i = -1;
  for (auto l : {"min odin", "nol", "ras", "dwa", "tri", "chetare", "pyat",
                 "sest", "sem", "vosem", "devayt"}) {
    EXPECT_EQ(l, sets_move.at(i));
    EXPECT_EQ(l, sets_clone.at(i));
    i++;
  }
};
TEST(map_test, Constructor_3) {
  s21::map<int, std::string> sets({{1, "ras"},
                                   {2, "dwa"},
                                   {3, "tri"},
                                   {4, "chetare"},
                                   {5, "pyat"},
                                   {6, "sest"},
                                   {7, "sem"},
                                   {8, "vosem"},
                                   {9, "devayt"},
                                   {0, "nol"},
                                   {-1, "min odin"}}),
      sets_clone;
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
  int i = -1;
  for (auto l : {"min odin", "nol", "ras", "dwa", "tri", "chetare", "pyat",
                 "sest", "sem", "vosem", "devayt"}) {
    EXPECT_EQ(l, sets.at(i));
    EXPECT_EQ(l, sets_clone.at(i));
    i++;
  }
};
TEST(map_test, Constructor_4) {
  s21::map<int, std::string> sets({{1, "ras"},
                                   {2, "dwa"},
                                   {3, "tri"},
                                   {4, "chetare"},
                                   {5, "pyat"},
                                   {6, "sest"},
                                   {7, "sem"},
                                   {8, "vosem"},
                                   {9, "devayt"},
                                   {0, "nol"},
                                   {-1, "min odin"}}),
      sets_clone(sets), sets_move;
  sets_move = std::move(sets);
  EXPECT_EQ(sets_move.empty(), sets_clone.empty());
  EXPECT_EQ(sets_move.size(), sets_clone.size());
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets_move.contains(i), 1);
  for (int i = -1; i < 10; i++) EXPECT_EQ(sets_clone.contains(i), 1);
  auto j = sets_clone.begin();
  for (auto i = sets_move.begin(); i != sets_move.end(); i++) {
    EXPECT_EQ(*i, *j);
    j++;
  }
  int i = -1;
  for (auto l : {"min odin", "nol", "ras", "dwa", "tri", "chetare", "pyat",
                 "sest", "sem", "vosem", "devayt"}) {
    EXPECT_EQ(l, sets_move.at(i));
    EXPECT_EQ(l, sets_clone.at(i));
    i++;
  }
};
TEST(map_test, clear) {
  s21::map<int, std::string> sets({{1, "ras"},
                                   {2, "dwa"},
                                   {3, "tri"},
                                   {4, "chetare"},
                                   {5, "pyat"},
                                   {6, "sest"},
                                   {7, "sem"},
                                   {8, "vosem"},
                                   {9, "devayt"},
                                   {0, "nol"},
                                   {-1, "min odin"}}),
      sets_clone(sets);
  EXPECT_EQ(sets.empty(), sets_clone.empty());
  EXPECT_EQ(sets.size(), sets_clone.size());
  EXPECT_EQ(sets.empty(), sets_clone.empty());
  EXPECT_EQ(sets.size(), sets_clone.size());
  sets.clear();
  sets_clone.clear();
  EXPECT_EQ(sets.empty(), sets_clone.empty());
  EXPECT_EQ(sets.size(), sets_clone.size());
};

TEST(map_test, swap) {
  s21::map<int, std::string> sets({{1, "ras"},
                                   {2, "dwa"},
                                   {3, "tri"},
                                   {4, "chetare"},
                                   {5, "pyat"},
                                   {6, "sest"},
                                   {0, "nol"},
                                   {-1, "min odin"}}),
      sets_clone({{7, "sem"}, {8, "vosem"}, {9, "devayt"}});
  EXPECT_EQ(sets.empty(), sets_clone.empty());
  for (int i = -1; i < 7; i++) EXPECT_EQ(sets.contains(i), 1);
  for (int i = 7; i < 10; i++) EXPECT_EQ(sets_clone.contains(i), 1);

  int i = -1;
  for (auto l :
       {"min odin", "nol", "ras", "dwa", "tri", "chetare", "pyat", "sest"}) {
    EXPECT_EQ(l, sets.at(i));
    i++;
  }
  int k = 7;
  for (auto l : {"sem", "vosem", "devayt"}) {
    EXPECT_EQ(l, sets_clone.at(k));
    k++;
  }
  sets.swap(sets_clone);

  i = -1;
  for (auto l :
       {"min odin", "nol", "ras", "dwa", "tri", "chetare", "pyat", "sest"}) {
    EXPECT_EQ(l, sets_clone.at(i));
    i++;
  }
  k = 7;
  for (auto l : {"sem", "vosem", "devayt"}) {
    EXPECT_EQ(l, sets.at(k));
    k++;
  }
};

TEST(map_test, merge) {
  s21::map<int, std::string> sets({{1, "ras"},
                                   {2, "dwa"},
                                   {3, "tri"},
                                   {4, "chetare"},
                                   {5, "pyat"},
                                   {6, "sest"},
                                   {0, "nol"},
                                   {-1, "min odin"}}),
      sets_clone(
          {{5, "pyat"}, {6, "sest"}, {7, "sem"}, {8, "vosem"}, {9, "devayt"}});
  EXPECT_EQ(sets.empty(), sets_clone.empty());
  for (int i = -1; i < 7; i++) EXPECT_EQ(sets.contains(i), 1);
  for (int i = 7; i < 10; i++) EXPECT_EQ(sets_clone.contains(i), 1);

  int i = -1;
  for (auto l :
       {"min odin", "nol", "ras", "dwa", "tri", "chetare", "pyat", "sest"}) {
    EXPECT_EQ(l, sets.at(i));

    i++;
  }
  int k = 5;
  for (auto l : {"pyat", "sest", "sem", "vosem", "devayt"}) {
    EXPECT_EQ(l, sets_clone.at(k));

    k++;
  }
  sets.merge(sets_clone);

  i = -1;
  for (auto l : {"min odin", "nol", "ras", "dwa", "tri", "chetare", "pyat",
                 "sest", "sem", "vosem", "devayt"}) {
    EXPECT_EQ(l, sets.at(i));
    i++;
  }
  k = 5;
  for (auto l : {"pyat", "sest"}) {
    EXPECT_EQ(l, sets_clone.at(k));
    k++;
  }
};

TEST(map_test, inserts) {
  s21::map<int, std::string> sets;
  EXPECT_EQ(sets.empty(), 1);
  auto pair_ = sets.insert(2, "dwa");
  sets[1] = "odin";
  EXPECT_EQ(pair_.second, 1);
  EXPECT_EQ(pair_.first, sets.find(2));
  EXPECT_EQ(sets.at(1), "odin");
  pair_ = sets.insert_or_assign(2, "dwa");
  EXPECT_EQ(pair_.second, 0);
  EXPECT_EQ(pair_.first, sets.find(2));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};