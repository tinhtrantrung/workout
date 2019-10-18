#include <iostream>

template <typename T>
struct Node;

template <typename T>
class List;

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& L);

template <typename T>
struct Node {
    T value;
    Node* next = nullptr;
    Node* previous = nullptr;
};

template <typename T>
class List {
    friend std::ostream& operator<<<>(std::ostream& os, const List& L);

   public:
    List() = default;
    ~List();

    T& Front();
    T& Back();

    void PushBack(const T& value);
    void PushFront(const T& value);
    void Remove(const T& value);

    bool Empty() const;
    bool IsExisted(const T& value);

    void PopBack();
    void PopFront();

    // Merges other_list into the list by transferring all of its elements at their respective ordered positions into
    // the container (both containers shall already be ordered).
    void Merge(List& other_list);

   private:
    Node<T>* head_ = nullptr;
    Node<T>* tail_ = nullptr;
};

int main() {
    List<int> l1;
    l1.PushBack(1);
    l1.PushBack(3);
    l1.PushBack(5);

    List<int> l2;
    l2.PushBack(2);
    l2.PushBack(4);
    l2.PushBack(6);

    std::cout << l1 << std::endl;
    std::cout << l2 << std::endl;

    l1.Merge(l2);

    std::cout << l1 << std::endl;
    std::cout << l2 << std::endl;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list) {
    if (list.Empty()) return os << "empty list";

    auto p = list.head_;
    while (p != list.tail_) {
        os << p->value << ", ";
        p = p->next;
    }

    os << p->value;

    os << " <-> ";

    p = list.tail_;
    while (p != list.head_) {
        os << p->value << ", ";
        p = p->previous;
    }

    os << p->value;

    return os;
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
T& List<T>::Front() { return head_ ? head_->value : throw "List::Front on an empty list!"; }

template <typename T>
T& List<T>::Back() { return tail_ ? tail_->value : throw "List::Back on an empty list!"; }

template <typename T>
void List<T>::PushBack(const T& value) {
    auto node = new Node<T>{value, nullptr, tail_};
    if (this->Empty()) {
        tail_ = node;
        head_ = node;
    } else {
        tail_->next = node;
        tail_ = node;
    }
}

template <typename T>
void List<T>::PushFront(const T& value) {
    auto node = new Node<T>{value, head_, nullptr};
    if (this->Empty()) {
        tail_ = node;
        head_ = node;
    } else {
        head_->previous = node;
        head_ = node;
    }
}

template <typename T>
void List<T>::Remove(const T& value) {
    while (head_ && head_->value == value) {
        auto p = head_->next;
        delete head_;
        head_ = p;
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
        } else {
            p = p->next;
        }
    }

    if (p->value == value) {
        tail_ = p->previous;
        tail_->next = nullptr;
        delete p;
    }
}

template <typename T>
bool List<T>::Empty() const { return !head_; }

template <typename T>
bool List<T>::IsExisted(const T& value) {
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

    if (!head_) {
        tail_ = nullptr;
    } else {
        head_->previous = nullptr;
    }
}

template <typename T>
void List<T>::Merge(List<T>& other_list) {
    if (this == &other_list)
        return;

    if (this->Empty()) {
        head_ = other_list.head_;
        tail_ = other_list.tail_;

        other_list.head_ = nullptr;
        other_list.tail_ = nullptr;

        return;
    }

    if (other_list.Empty())
        return;

    decltype(head_) new_head = nullptr;
    if (head_->value <= other_list.head_->value) {
        new_head = head_;
        head_ = head_->next;
    } else {
        new_head = other_list.head_;
        other_list.head_ = other_list.head_->next;
    }

    auto p = new_head;
    while (head_ && other_list.head_) {
        if (head_->value <= other_list.head_->value) {
            p->next = head_;
            head_->previous = p;

            p = head_;
            head_ = head_->next;
        } else {
            p->next = other_list.head_;
            other_list.head_->previous = p;

            p = other_list.head_;
            other_list.head_ = other_list.head_->next;
        }
    }

    if (head_) {
        p->next = head_;
        head_->previous = p;
    } else {
        p->next = other_list.head_;
        other_list.head_->previous = p;
        tail_ = other_list.tail_;
    }

    head_ = new_head;
    other_list.head_ = other_list.tail_ = nullptr;
}