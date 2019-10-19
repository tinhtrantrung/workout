#include <cassert>           // for assert()
#include <initializer_list>  // for std::initializer_list
#include <iostream>

template <typename T>
struct Node;

template <typename T>
class List;

template <typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &L);

template <typename T>
struct Node {
  T value;
  Node *next = nullptr;
  Node *previous = nullptr;
};

template <typename T>
class List {
  friend std::ostream &operator<<<>(std::ostream &os, const List &L);

 public:
  List() = default;
  List(const std::initializer_list<T> &l);
  ~List();

  T &Front();
  T &Back();

  void PushBack(const T &value);
  void PushFront(const T &value);
  void Remove(const T &value);

  bool Empty() const;
  bool IsExisted(const T &value);

  void PopBack();
  void PopFront();

  // Merges other_list into the list by transferring all of its elements at
  // their respective ordered positions into the container (both containers
  // shall already be ordered).
  void Merge(List &other_list);

  // Delete an ith node from a linked list. Be sure that such a node exists.
  void DeleteByIndex(const int &i);

  // Delete from list L1 nodes whose positions are to be found in an ordered
  // list L2
  void DeleteByListIndex(const List<int> &l);

  // Delete from list L1 nodes occupying positions indicated in ordered lists L2
  // and L3.
  void DeleteByListIndex(const List<int> &l1, const List<int> &l2);

 private:
  int size_ = 0;
  Node<T> *head_ = nullptr;
  Node<T> *tail_ = nullptr;
};

int main() {
  List<int> k{'A', 'B', 'C', 'D', 'E'};
  List<int> l{2, 4, 8};
  List<int> m{2, 5};
  std::cout << "k: " << k << std::endl;
  std::cout << "l: " << l << std::endl;
  std::cout << "k: " << m << std::endl;

  k.DeleteByListIndex(l, m);
  std::cout << "k after deleted nodes: " << k << std::endl;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &list) {
  if (list.Empty()) return os << "empty list";

  os << "\nsize: " << list.size_ << "\ndata: ";
  auto p = list.head_;
  while (p != list.tail_) {
    os << p->value << ", ";
    p = p->next;
  }

  return os << p->value;
}

template <typename T>
List<T>::List(const std::initializer_list<T> &l)
    : size_{0}, head_{nullptr}, tail_{nullptr} {
  for (auto &i : l) {
    this->PushBack(i);
  }
}

template <typename T>
List<T>::~List() {
  while (head_) {
    auto p = head_->next;
    delete head_;
    head_ = p;
  }

  tail_ = nullptr;
  head_ = nullptr;
}

template <typename T>
T &List<T>::Front() {
  assert(this->Empty());
  return head_ ? head_->value : throw "List::Front on an empty list!";
}

template <typename T>
T &List<T>::Back() {
  assert(this->Empty());
  return tail_ ? tail_->value : throw "List::Back on an empty list!";
}

template <typename T>
void List<T>::PushBack(const T &value) {
  auto node = new Node<T>{value, nullptr, tail_};
  if (this->Empty()) {
    tail_ = node;
    head_ = node;
  } else {
    tail_->next = node;
    tail_ = node;
  }
  size_++;
}

template <typename T>
void List<T>::PushFront(const T &value) {
  auto node = new Node<T>{value, head_, nullptr};
  if (this->Empty()) {
    tail_ = node;
    head_ = node;
  } else {
    head_->previous = node;
    head_ = node;
  }
  size_++;
}

template <typename T>
void List<T>::Remove(const T &value) {
  while (head_ && head_->value == value) {
    auto p = head_->next;
    delete head_;
    head_ = p;
    size_--;
  }

  if (!head_) {
    tail_ = nullptr;
    return;
  }

  head_->previous = nullptr;

  auto p = head_->next;
  while (p != tail_) {
    if (p->value == value) {
      p->previous->next = p->next;
      p->next->previous = p->previous;
      auto q = p;
      p = p->next;
      delete q;
      size_--;
    } else {
      p = p->next;
    }
  }

  if (p->value == value) {
    tail_ = p->previous;
    tail_->next = nullptr;
    delete p;
    size_--;
  }
}

template <typename T>
bool List<T>::Empty() const {
  return !head_;
}

template <typename T>
bool List<T>::IsExisted(const T &value) {
  auto p = head_;
  while (p != nullptr && p->value != value) {
    p = p->next;
  }

  return p != nullptr;
}

template <typename T>
void List<T>::PopBack() {
  if (this->Empty()) return;

  auto p = tail_;
  tail_ = tail_->previous;
  delete p;
  size_--;

  if (!tail_) {
    head_ = nullptr;
  } else {
    tail_->next = nullptr;
  }
}

template <typename T>
void List<T>::PopFront() {
  if (this->Empty()) return;

  auto p = head_;
  head_ = head_->next;
  delete p;
  size_--;

  if (!head_) {
    tail_ = nullptr;
  } else {
    head_->previous = nullptr;
  }
}

template <typename T>
void List<T>::Merge(List<T> &other_list) {
  if (this == &other_list) return;

  if (this->Empty()) {
    head_ = other_list.head_;
    tail_ = other_list.tail_;

    other_list.head_ = nullptr;
    other_list.tail_ = nullptr;

    size_ = other_list.size_;

    return;
  }

  if (other_list.Empty()) return;

  decltype(head_) new_head{nullptr};
  if (head_->value <= other_list.head_->value) {
    new_head = head_;
    head_ = head_->next;
    size_--;
  } else {
    new_head = other_list.head_;
    other_list.head_ = other_list.head_->next;
    other_list.size_--;
  }

  auto new_size{1};
  auto p{new_head};
  while (head_ && other_list.head_) {
    new_size++;
    if (head_->value <= other_list.head_->value) {
      p->next = head_;
      head_->previous = p;

      p = head_;
      head_ = head_->next;
      size_--;
    } else {
      p->next = other_list.head_;
      other_list.head_->previous = p;

      p = other_list.head_;
      other_list.head_ = other_list.head_->next;
      other_list.size_--;
    }
  }

  if (head_) {
    p->next = head_;
    head_->previous = p;
    new_size += size_;
  } else {
    p->next = other_list.head_;
    other_list.head_->previous = p;
    new_size += other_list.size_;
    tail_ = other_list.tail_;
  }

  head_ = new_head;
  size_ = new_size;
  other_list.head_ = other_list.tail_ = nullptr;
}

template <typename T>
void List<T>::DeleteByIndex(const int &i) {
  if (i <= 0 || i > size_) return;

  if (i == 1) {
    this->PopFront();
    return;
  }

  if (i == size_) {
    this->PopBack();
    return;
  }

  auto p{head_};
  auto j{i - 1};
  while (j > 1) {
    p = p->next;
    j--;
  }

  auto q{p->next};
  p->next = q->next;
  q->next->previous = p;
  delete q;
  size_--;
}

template <typename T>
void List<T>::DeleteByListIndex(const List<int> &l) {
  auto p{l.tail_};
  auto index{0};
  while (p != nullptr) {
    if (index != p->value) {
      index = p->value;
      this->DeleteByIndex(index);
    }
    p = p->previous;
  }
}

template <typename T>
void List<T>::DeleteByListIndex(const List<int> &l1, const List<int> &l2) {
  auto tail_1{l1.tail_};
  auto tail_2{l2.tail_};
  auto index{0};
  while (tail_1 && tail_2) {
    if (tail_1->value >= tail_2->value) {
      if (index != tail_1->value) {
        index = tail_1->value;
        this->DeleteByIndex(index);
      }
      tail_1 = tail_1->previous;
    } else {
      if (index != tail_2->value) {
        index = tail_2->value;
        this->DeleteByIndex(index);
      }
      tail_2 = tail_2->previous;
    }
  }

  auto p{tail_1 ? tail_1 : tail_2};
  while (p != nullptr) {
    if (index != p->value) {
      index = p->value;
      this->DeleteByIndex(index);
    }
    p = p->previous;
  }
}