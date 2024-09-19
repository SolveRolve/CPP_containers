

#include <gtest/gtest.h>

#include "tree_rb.h"

TEST(Tree_test, empty_constructor) {
  s21::Tree<int, int> tree;
  EXPECT_EQ(tree.getnil(), tree.getRoot());
  EXPECT_EQ(tree.empty(), 1);
  EXPECT_EQ(tree.size(), 0);
};
TEST(Tree_test, insert) {
  s21::Tree<int, int> tree;
  tree.insert(1);
  EXPECT_NE(tree.getnil(), tree.getRoot());
  EXPECT_EQ(tree.empty(), 0);
  EXPECT_EQ(tree.size(), 1);
  EXPECT_EQ(tree.getKey(tree.find(1)), 1);
};

TEST(Tree_test, insert_100000) {
  s21::Tree<int, int> tree;
  for (int i = 0; i < 100000; i++) {
    tree.insert(i);
  }
  EXPECT_NE(tree.getnil(), tree.getRoot());
  EXPECT_EQ(tree.empty(), 0);
  EXPECT_EQ(tree.size(), 100000);
  for (int i = 0; i < 100000; i++) EXPECT_EQ(tree.getKey(tree.find(i)), i);
};

TEST(Tree_test, insert_1000_rand1) {
  srand(123123121);
  s21::Tree<int, int> tree;
  int rand_numb[1000] = {0};
  for (int i = 0; i < 20; i++) {
    rand_numb[i] = rand() % 1000 + 1;
    tree.insert(rand_numb[i]);
  }
  for (int i = 0; i < 10000; i++) {
    int s = rand() % 1000 + 1;
    tree.remove(s);
  }
}

TEST(Tree_test, insert_1000_rand2) {
  s21::Tree<int, int> tree;
  int rand_numb[1000] = {0};
  for (int i = 0; i < 20; i++) {
    rand_numb[i] = rand() % -9990 + 1;
    tree.insert(rand_numb[i]);
  }
  for (int i = 0; i < 10000; i++) {
    int s = rand() % -9990 + 1;
    tree.remove(s);
  }
}
// TEST(Tree_test, insert_1000_rand3) {
//     s21::Tree<int, int> tree;
//     int rand_numb[10000]={0};
//     for (int i =0;i<10000;i++){
//         rand_numb[i]=rand() % -100000 +1;
//         tree.insert(rand_numb[i]);}
//         std::cout<< "inseert";
// int k =20;
//     for (auto i = tree.rbegin();i!=tree.rend();i--){
//         EXPECT_NE(tree.find(*i),tree.getnil());
//         k--;
//     }
//     for (int i =0;i<10000;i++){
//     int s = rand() % -1000 +1;
//     tree.remove(s);
//     }
//     }

TEST(Tree_test, insert_initialize_list) {
  s21::Tree<int, int> tree({1, 2, 3, 4, 5, 6, 7, 8, 9, 0});
  EXPECT_NE(tree.getnil(), tree.getRoot());
  EXPECT_EQ(tree.empty(), 0);
  EXPECT_EQ(tree.size(), 10);
  for (int i = 0; i < 10; i++) EXPECT_EQ(tree.getKey(tree.find(i)), i);
};

TEST(Tree_test, remove_all) {
  s21::Tree<int, int> tree({1, 2, 3, 4, 5, 6, 7, 8, 9, 0});
  EXPECT_NE(tree.getnil(), tree.getRoot());
  EXPECT_EQ(tree.empty(), 0);
  EXPECT_EQ(tree.size(), 10);
  for (int i = 0; i < 10; i++) EXPECT_EQ(tree.getKey(tree.find(i)), i);
  for (int i = 0; i < 11; i++) {
    tree.remove(i);
    EXPECT_EQ(tree.getKey(tree.find(i)), -1);
  }
};
TEST(Tree_test, iterator_1) {
  s21::Tree<int, int> tree({1, 2, 3, 4, 5, 6, 7, 8, 9, 0});
  int k = 0;
  for (auto i = tree.begin(); i != tree.end(); i++) {
    EXPECT_EQ(tree.getKey(tree.find(*i)), k);
    k++;
  }
}
TEST(Tree_test, Iterator_2) {
  s21::Tree<int, int> tree({1, 2, 3, 4, 5, 6, 7, 8, 9, 0});
  int k = 9;
  for (auto i = tree.rbegin(); i != tree.rend(); i--) {
    EXPECT_EQ(tree.getKey(tree.find(*i)), k);
    k--;
  }
}
TEST(Tree_test, swaps) {
  s21::Tree<int, int> tree({1, 2, 3, 4, 5, 6, 7, 8, 9, 0}),
      eert({-1, -2, -3, -4, -5, -6, -7, -8, -9, -0});
  EXPECT_NE(tree.getnil(), tree.getRoot());
  EXPECT_NE(eert.getnil(), tree.getRoot());
  EXPECT_EQ(tree.empty(), eert.empty());
  EXPECT_EQ(tree.size(), eert.size());
  for (int i = 0; i < 10; i++) EXPECT_EQ(tree.getKey(tree.find(i)), i);
  for (int i = -1; i > -10; i--) EXPECT_EQ(eert.getKey(eert.find(i)), i);
  tree.swap(eert);
  for (int i = 0; i < 10; i++) EXPECT_EQ(eert.getKey(eert.find(i)), i);
  for (int i = -1; i > -10; i--) EXPECT_EQ(tree.getKey(tree.find(i)), i);
};
TEST(Tree_test, move_copy_constructor) {
  s21::Tree<int, int> tree({1, 2, 3, 4, 5, 6, 7, 8, 9, 0}), trees(tree), trem;
  trem = std::move(tree);
  auto j = trees.begin();
  for (auto i = trem.begin(); i != trem.end(); i++) {
    EXPECT_EQ(trem.getKey(trem.find(*i)), trees.getKey(trees.find(*j)));
    j++;
  }
};
TEST(Tree_test, move_copy_constructor_1) {
  s21::Tree<int, int> tree({1, 2, 3, 4, 5, 6, 7, 8, 9, 0}),
      trees(std::move(tree)), trem;
  auto j = trees.begin();
  for (auto i = trem.begin(); i != trem.end(); i++) {
    EXPECT_EQ(trem.getKey(trem.find(*i)), trees.getKey(trees.find(*j)));
    j++;
  }
};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};
