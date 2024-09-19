#include "tree_rb.h"
int main() {
  s21::Tree<int, int> s;
  s.insert(345, 2);
  s.getMap(s.find(345)) = 3;
  std::cout << s.getMap(s.find(345));
  s.remove(345);
  return 0;
}