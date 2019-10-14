#include <iostream>

struct Node {
    int value = 110;
    Node* next = nullptr;
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

    if (list.head_ == list.tail_) {
        os << list.head_->value;
        return os;
    }

    auto p = list.head_;
    while (p != list.tail_) {
        os << p->value << ", ";
        p = p->next;
    }

    return os << p->value;
}

int main() {
    List l;
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
    auto node = new Node{value, nullptr};
    if (!tail_) {
        tail_ = node;
        head_ = node;
    } else {
        tail_->next = node;
        tail_ = node;
    }
}

void List::PushFront(const int& value) {
    auto node = new Node{value, head_};
    if (!tail_) {
        tail_ = node;
        head_ = node;
    } else {
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

    auto p = head_;
    auto q = head_->next;
    while (p->next != nullptr) {
        if (q->value == value) {
            p->next = q->next;
            delete q;
            q = p->next;
        } else {
            p = q;
            q = q->next;
        }
    }

    tail_ = p;
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

    if (head_ == tail_) {
        delete tail_;
        head_ = nullptr;
        tail_ = nullptr;
        return;
    }

    auto p = head_;
    while (p->next != tail_) {
        p = p->next;
    }

    p->next = nullptr;
    delete tail_;
    tail_ = p;
}

void List::PopFront() {
    if (!head_) return;

    auto p = head_->next;
    delete head_;
    head_ = p;
    if (!head_) {
        tail_ = nullptr;
    }
}