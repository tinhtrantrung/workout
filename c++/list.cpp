#include <iostream>

struct IntNode {
  int value = 110;
  IntNode* next = nullptr;
};

class IntList {
 public:
  IntList() : head(nullptr) {}

 private:
  IntNode* head;
};

int main() {
  IntNode x;
  std::cout << x.value << std::endl;
  return;
}