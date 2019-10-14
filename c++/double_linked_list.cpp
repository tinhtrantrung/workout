#include <iostream>

struct Node {
    int value = 110;
    Node* next = nullptr;
    Node* previous = nullptr;
};

class List {
    friend std::ostream& operator<<(std::ostream& os, const List& list);

   public:
    List() = default;
    ~List();

    int Front();
    int Back();

    void PushBack(const int& value);
    void PushFront(const int& value);
    void Remove(const int& value);

    bool Empty();
    bool IsExisted(const int& value);

    void PopBack();
    void PopFront();

   private:
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
};

std::ostream& operator<<(std::ostream& os, const List& list) {
    if (list.head_ == nullptr) return os;

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

int main() {
    List l;
    l.PushBack(1);
    l.PushBack(2);
    l.PushFront(3);
    l.PushFront(4);
    l.PushFront(4);
    l.PushFront(4);
    std::cout << l << std::endl;
    l.Remove(1);
    std::cout << l << std::endl;
    l.Remove(2);
    std::cout << l << std::endl;
    l.Remove(3);
    std::cout << l << std::endl;
    l.Remove(4);
    std::cout << l << std::endl;

    l.PushBack(1);
    l.PushBack(2);
    l.PushFront(3);
    l.PushFront(4);
    std::cout << l << std::endl;

    auto sum{0};
    while (!l.Empty()) {
        sum += l.Back();
        l.PopBack();
    }

    std::cout << sum << std::endl;
    std::cout << l << std::endl;

    l.PushBack(1);
    l.PushBack(2);
    l.PushFront(3);
    l.PushFront(4);
    std::cout << l << std::endl;

    sum = 0;
    while (!l.Empty()) {
        sum += l.Front();
        l.PopFront();
    }

    std::cout << sum << std::endl;
    std::cout << l << std::endl;
}

List::~List() {
    while (head_) {
        auto p = head_->next;
        delete head_;
        head_ = p;
    }

    tail_ = nullptr;
}

int List::Front() { return head_ ? head_->value : 0; }

int List::Back() { return tail_ ? tail_->value : 0; }

void List::PushBack(const int& value) {
    auto node = new Node{value, nullptr, tail_};
    if (!tail_) {
        tail_ = node;
        head_ = node;
    } else {
        tail_->next = node;
        tail_ = node;
    }
}

void List::PushFront(const int& value) {
    auto node = new Node{value, head_, nullptr};
    if (!tail_) {
        tail_ = node;
        head_ = node;
    } else {
        head_->previous = node;
        head_ = node;
    }
}

void List::Remove(const int& value) {
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

bool List::Empty() { return !head_; }

bool List::IsExisted(const int& value) {
    auto p = head_;
    while (p != nullptr && p->value != value) {
        p = p->next;
    }

    return p != nullptr;
}

void List::PopBack() {
    if (!tail_) return;

    auto p = tail_;
    tail_ = tail_->previous;
    delete p;

    if (!tail_) {
        head_ = nullptr;
    } else {
        tail_->next = nullptr;
    }
}

void List::PopFront() {
    if (!head_) return;

    auto p = head_;
    head_ = head_->next;
    delete p;

    if (!head_) {
        tail_ = nullptr;
    } else {
        head_->previous = nullptr;
    }
}