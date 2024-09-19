
#include <gtest/gtest.h>

#include <vector>

#include "s21_vector.h"

TEST(vector_test, AllTests) {
  s21::vector<int> v;
  EXPECT_EQ(v.size(), 0);
  s21::vector<int> v1{1, 2, 3, 4, 5};
  s21::vector<int> v2(v1);
  EXPECT_EQ(v1.size(), v2.size());
  for (size_t i = 0; i < v1.size(); ++i) EXPECT_EQ(v1[i], v2[i]);

  {
    s21::vector<int> v1(3);

    v1[0] = 1;
    v1[1] = 2;
    v1[2] = 3;

    s21::vector<int> v2(std::move(v1));

    EXPECT_EQ(v1.size(), 0);

    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
  }
}

TEST(IteratorTest, IteratorOperations) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  auto it = v.begin();
  EXPECT_EQ(it == v.begin(), true);
  EXPECT_EQ(it != v.end(), true);
  EXPECT_EQ(it < v.end(), true);
  EXPECT_EQ(it > v.begin(), false);
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*it, v[0]);

  auto tmp = it++;
  EXPECT_EQ(*tmp, 1);
  EXPECT_EQ(*it, 2);

  --it;
  EXPECT_EQ(*it, 1);

  it = it + 2;
  EXPECT_EQ(*it, 3);

  it = it - 1;
  EXPECT_EQ(*it, 2);
}

TEST(IteratorTest, PlusMinusOperators) {
  s21::vector<int> v{1, 2, 3, 4, 5};

  auto it = v.begin();

  it = it + 3;
  EXPECT_EQ(*it, 4);

  it = it - 2;
  EXPECT_EQ(*it, 2);
}

TEST(vector_test, MoveAssignmentOperator) {
  s21::vector<int> v1{1, 2, 3, 4, 5};
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ(v1.size(), 0);
  EXPECT_EQ(v2.size(), 5);
  for (size_t i = 0; i < v2.size(); ++i) EXPECT_EQ(v2[i], i + 1);
}

TEST(vector_test, AtMethod) {
  s21::vector<int> v{1, 2, 3, 4, 5};

  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_EQ(v.at(4), 5);

  EXPECT_THROW(v.at(5), std::out_of_range);
}

TEST(vector_test, OperatorSquareBrackets) {
  s21::vector<int> v{1, 2, 3, 4, 5};

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

TEST(vector_test, FrontMethod) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(v.front(), 1);
}

TEST(vector_test, BackMethod) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(v.back(), 5);
}

TEST(vector_test, DataMethod) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  auto it = v.data();
  EXPECT_EQ(*it, 1);
}

TEST(vector_test, BeginAndEndMethods) {
  s21::vector<int> v{1, 2, 3, 4, 5};

  auto begin_it = v.begin();
  auto end_it = v.end();

  EXPECT_EQ(*begin_it, 1);

  EXPECT_EQ(*(--end_it), 5);
}

TEST(vector_test, EmptyMethod) {
  s21::vector<int> v_empty;

  EXPECT_TRUE(v_empty.empty());

  s21::vector<int> v_not_empty{1, 2, 3};

  EXPECT_FALSE(v_not_empty.empty());
}

TEST(vector_test, SizeMethod) {
  s21::vector<int> v{1, 2, 3};

  EXPECT_EQ(v.size(), 3);
}

TEST(vector_Constructor, vectorInitializerListConstructor_ObjectEmpty) {
  std::vector<int> vector{};
  s21::vector<int> s21_vector{};

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.max_size(), s21_vector.max_size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());
}

TEST(vector_Constructor, vectorInitializerListConstructor_ObjectWithOneArg) {
  std::vector<int> vector{1};
  s21::vector<int> s21_vector{1};

  EXPECT_EQ(*vector.data(), *s21_vector.data());
  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.max_size(), s21_vector.max_size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());
}

TEST(vector_Constructor, vectorInitializerListConstructor_ObjectWithTwoArg) {
  std::vector<int> vector{1, 2, 3, 4};
  s21::vector<int> s21_vector{1, 2, 3, 4};

  EXPECT_EQ(*vector.data(), *s21_vector.data());
  EXPECT_EQ(*(vector.data() + 1), *(s21_vector.data() + 1));
  EXPECT_EQ(*(vector.data() + 2), *(s21_vector.data() + 2));
  EXPECT_EQ(*(vector.data() + 3), *(s21_vector.data() + 3));

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.max_size(), s21_vector.max_size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());
}

TEST(vector_Constructor, vectorCopyConstructor_CopyObjectWithNullhArg) {
  std::vector<int> vector_00;
  s21::vector<int> s21_vector_00;

  std::vector<int> vector_01 = vector_00;
  s21::vector<int> s21_vector_01(s21_vector_00);

  EXPECT_EQ(vector_01.empty(), s21_vector_01.empty());
  EXPECT_EQ(vector_01.size(), s21_vector_01.size());
  EXPECT_EQ(vector_01.max_size(), s21_vector_01.max_size());
  EXPECT_EQ(vector_01.capacity(), s21_vector_01.capacity());
}

TEST(vector_Constructor, vectorCopyConstructor_CopyObjectOnehTwoArg) {
  std::vector<int> vector_00 = {1};
  s21::vector<int> s21_vector_00 = {1};

  std::vector<int> vector_01 = vector_00;
  s21::vector<int> s21_vector_01(s21_vector_00);

  EXPECT_EQ(vector_01.empty(), s21_vector_01.empty());
  EXPECT_EQ(vector_01.size(), s21_vector_01.size());
  EXPECT_EQ(vector_01.max_size(), s21_vector_01.max_size());
  EXPECT_EQ(vector_01.capacity(), s21_vector_01.capacity());

  EXPECT_EQ(*vector_01.data(), *s21_vector_01.data());
  EXPECT_EQ(*vector_01.data(), *s21_vector_01.data());
}

TEST(vector_Constructor, vectorCopyConstructor_CopyObjectTwoTwoArg) {
  std::vector<int> vector_00 = {1, 2};
  s21::vector<int> s21_vector_00 = {1, 2};

  std::vector<int> vector_01 = vector_00;
  s21::vector<int> s21_vector_01(s21_vector_00);

  EXPECT_EQ(vector_01.empty(), s21_vector_01.empty());
  EXPECT_EQ(vector_01.size(), s21_vector_01.size());
  EXPECT_EQ(vector_01.max_size(), s21_vector_01.max_size());
  EXPECT_EQ(vector_01.capacity(), s21_vector_01.capacity());

  EXPECT_EQ(*vector_01.data(), *s21_vector_01.data());
  EXPECT_EQ(*(vector_01.data() + 1), *(s21_vector_01.data() + 1));
}

TEST(vector_Constructor, vectorMoveConstructor_MoveObjectWithTwoArg) {
  s21::vector<int> original;
  for (int i = 0; i < 10; ++i) {
    original.push_back(i);
  }

  auto original_data = original.data();
  auto original_size = original.size();

  s21::vector<int> moved(std::move(original));

  EXPECT_EQ(original.size(), 0);

  EXPECT_EQ(moved.data(), original_data);
  EXPECT_EQ(moved.size(), original_size);
}

TEST(vector_Capacity, AllVariantCombinations_Part_1) {
  std::vector<int> vector;
  s21::vector<int> s21_vector;

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.max_size(), s21_vector.max_size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());

  vector.reserve(10);
  s21_vector.reserve(10);

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());

  vector.shrink_to_fit();
  s21_vector.shrink_to_fit();

  EXPECT_EQ(vector.empty(), s21_vector.empty());
  EXPECT_EQ(vector.size(), s21_vector.size());
  EXPECT_EQ(vector.capacity(), s21_vector.capacity());
}

TEST(vector_Modifiers, ClearMethod) {
  s21::vector<int> s21_vector;

  for (int i = 0; i < 5; ++i) s21_vector.push_back(i);

  EXPECT_FALSE(s21_vector.empty());
  EXPECT_EQ(s21_vector.size(), 5);
  s21_vector.clear();
  EXPECT_TRUE(s21_vector.empty());
  EXPECT_EQ(s21_vector.size(), 0);
}

TEST(vector_Insert, InsertValueAtPosition) {
  s21::vector<int> vec({11, 2, 3});
  auto i = vec.insert(vec.begin() + 1, 10);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(*i, 10);
}

TEST(vector_Capacity, vectorErase) {
  std::vector<int> vector{1, 2, 3, 4, 5};
  s21::vector<int> s21_vector{1, 2, 3, 4, 5};

  vector.erase(vector.begin());
  s21_vector.erase(s21_vector.begin());

  EXPECT_EQ(*vector.data(), 2);
  EXPECT_EQ(*s21_vector.data(), 2);

  vector.erase(vector.end() - 1);
  s21_vector.erase(s21_vector.end() - 1);
  EXPECT_EQ(*(vector.data() + 2), 4);
  EXPECT_EQ(*(s21_vector.data() + 2), 4);

  vector.erase(vector.begin());
  s21_vector.erase(s21_vector.begin());
  EXPECT_EQ(*(vector.data()), 3);
  EXPECT_EQ(*(s21_vector.data()), 3);

  vector.erase(vector.begin());
  s21_vector.erase(s21_vector.begin());
  EXPECT_EQ(*(vector.data()), 4);
  EXPECT_EQ(*(s21_vector.data()), 4);

  EXPECT_EQ(s21_vector.empty(), vector.empty());
}

TEST(vector_Modifiers, PushBackAndPopBack) {
  s21::vector<int> s21_vector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  int j = 1;

  for (auto i : s21_vector) {
    EXPECT_EQ(i, j);
    j++;
  }
}

TEST(vector_Modifiers, Swap) {
  s21::vector<int> first_vector{1, 2, 3};
  s21::vector<int> second_vector{4, 5};

  first_vector.swap(second_vector);

  EXPECT_EQ(first_vector.size(), 2);
  EXPECT_EQ(first_vector[0], 4);
  EXPECT_EQ(first_vector[1], 5);

  EXPECT_EQ(second_vector.size(), 3);
  EXPECT_EQ(second_vector[0], 1);
  EXPECT_EQ(second_vector[1], 2);
  EXPECT_EQ(second_vector[2], 3);
}

TEST(vector, insert_many) {
  s21::vector<int> v({7, 8, 9, 10});
  auto i = v.begin();
  v.insert_many(i, 1, 2, 3, 4, 5, 6);
  v.insert_many_back(11, 12, 13, 14);  //
  int j = 0;
  for (auto i : v) EXPECT_EQ(i, ++j);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};
