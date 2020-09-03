#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(const int& data, Node* next = nullptr) : data{data}, next{next} {}
};

Node* make_list(int v);
Node* make_list(const initializer_list<int>& list);
void print_list(Node* head);
void clear_list(Node** head);

// 2.1 remove duplicates from an unsorted linked list.
void remove_duplicates(Node* head);

// 2.2 implement an algorithm to find the nth to last element of a singly linked
// list.
Node* reverse_find_index(Node* head, const unsigned int& index);

// 2.3 delete a single node.
void delete_node(Node** head, Node* p);

// 2.4 adds the two numbers and returns the sum as a linked list.
Node* add(int x, int y);

int main() {
    auto l = add(513, 595);
    print_list(l);

    clear_list(&l);
    return 0;
}

Node* make_list(int v) {
    Node* head = new Node{v % 10};
    v = v / 10;

    auto tail = head;
    while (v) {
        tail->next = new Node{v % 10};
        tail = tail->next;
        v = v / 10;
    }

    return head;
}

Node* make_list(const initializer_list<int>& list) {
    Node* head = nullptr;
    Node* p = nullptr;
    for (auto& i : list) {
        if (head) {
            auto q = new Node{i};
            p->next = q;
            p = q;
        } else {
            head = new Node{i};
            p = head;
        }
    }
    return head;
}

Node* reverse_find_index(Node* head, const unsigned int& index) {
    auto length = 0u;
    auto p = head;
    while (p) {
        ++length;
        p = p->next;
    }

    if (index >= length) return nullptr;

    auto n = length - index - 1;
    p = head;
    while (n) {
        --n;
        p = p->next;
    }

    return p;
}

void print_list(Node* head) {
    if (!head) {
        cout << "empty list";
        return;
    }

    while (head->next != nullptr) {
        cout << head->data << ", ";
        head = head->next;
    }

    cout << head->data << "\n";
}

void clear_list(Node** head) {
    while (*head) {
        auto p = *head;
        *head = (*head)->next;
        delete p;
    }
}

void remove_duplicates(Node* head) {
    if (!head) return;

    auto current = head;
    while (current->next) {
        auto previous_p = current;
        auto p = previous_p->next;
        while (p) {
            if (p->data == current->data) {
                previous_p->next = p->next;
                delete p;
                p = previous_p->next;
            } else {
                previous_p = p;
                p = p->next;
            }
        }
        current = current->next;
    }
}

void delete_node(Node** head, Node* p) {
    if (!*head) return;

    if (*head == p) {
        *head = p->next;
        delete p;

        return;
    }

    auto previous_p = *head;
    while (previous_p->next != p) previous_p = previous_p->next;

    previous_p->next = p->next;
    delete p;
}

Node* add(int x, int y) {
    auto number_x = make_list(x);
    auto number_y = make_list(y);

    auto sum = number_x->data + number_y->data;
    auto remain = sum / 10;
    Node* head = new Node{sum % 10};
    auto tail = head;
    auto p = number_x->next;
    auto q = number_y->next;
    while (p && q) {
        sum = p->data + q->data + remain;
        tail->next = new Node{sum % 10};
        tail = tail->next;
        remain = sum / 10;
        p = p->next;
        q = q->next;
    }

    while (p) {
        sum = p->data + remain;
        tail->next = new Node{sum % 10};
        tail = tail->next;
        remain = sum / 10;
        p = p->next;
    }

    while (q) {
        sum = q->data + remain;
        tail->next = new Node{sum % 10};
        tail = tail->next;
        remain = sum / 10;
        q = q->next;
    }

    if (remain) {
        tail->next = new Node{remain};
        tail = tail->next;
    }

    clear_list(&number_x);
    clear_list(&number_y);

    return head;
}