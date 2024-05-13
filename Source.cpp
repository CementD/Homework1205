#include <iostream>
#include <initializer_list>
using namespace std;

template<class T>
struct Node {
    T value;
    Node* next;
    ~Node() {
        cout << "\ndestroyed\n";
    }
};

template<class T>
class LinkedList {
    Node<T>* head = nullptr;

public:
    LinkedList(initializer_list<T> values) {
        for (const T& value : values) {
            add(value);
        }
    }

    void add(const T& value) {
        Node<T>* newNode = new Node<T>;
        newNode->value = value;
        newNode->next = head;
        head = newNode;
    }

    void print() const {
        Node<T>* tmp = head;
        while (tmp != nullptr) {
            cout << tmp->value << " next node address: " << tmp->next << endl;
            tmp = tmp->next;
        }
    }

    void deleteFirst() {
        if (head == nullptr)
            return;
        Node<T>* tmp = head;
        head = head->next;
        delete tmp;
        cout << "First node is removed." << endl;
    }

    Node<T>* searchNode(const T& value) {
        Node<T>* tmp = head;
        while (tmp != nullptr) {
            if (tmp->value == value) {
                return tmp;
            }
            tmp = tmp->next;
        }
        return nullptr;
    }

    void addAfter(Node<T>* prevNode, const T& value) {
        if (prevNode == nullptr) {
            return;
        }
        Node<T>* newNode = new Node<T>;
        newNode->value = value;
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }

    void removeAfter(Node<T>* prevNode) {
        if (prevNode == nullptr || prevNode->next == nullptr) {
            return;
        }
        Node<T>* temp = prevNode->next;
        prevNode->next = temp->next;
        delete temp;
        cout << "Node after previous node is removed." << endl;
    }

    ~LinkedList() {
        while (head != nullptr) {
            Node<T>* tmp = head->next;
            delete head;
            head = tmp;
        }
    }
};

int main() {
    LinkedList<int> list{ 3, 2, 1, 0 };
    list.print();

    Node<int>* node = list.searchNode(2);
    if (node != nullptr) {
        cout << "Node found with value: " << node->value << endl;
        list.addAfter(node, 10);
        cout << "After adding 10 after node with value 2:" << endl;
        list.print();
    }
    else {
        cout << "Node not found." << endl;
    }

    node = list.searchNode(1);
    if (node != nullptr) {
        cout << "Node found with value: " << node->value << endl;
        list.removeAfter(node);
        cout << "After removing node after node with value 1:" << endl;
        list.print();
    }
    else {
        cout << "Node not found." << endl;
    }

    return 0;
}