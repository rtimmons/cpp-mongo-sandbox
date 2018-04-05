#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>

using namespace std;

struct Node{
    Node* next = nullptr;
    Node* prev = nullptr;
    int value;
    int key;
//    Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
    Node(int k, int val):next(nullptr),prev(nullptr),value(val),key(k){};

    ~Node() {
        delete next;
    }
};

ostream& operator<<(ostream& out, Node* node) {
    set<Node*> seen{};
    int max = 11;
    while(node != nullptr && --max) {
        if (seen.find(node) != seen.end()) {
            out << "INFINITE RECURSION AT " << node->key << "," << node->value << *seen.find(node);
            break;
        }
        out << "{"
            << (node->prev ? node->prev->key : -1)
            << "<-"
            << "("
            << node->key
            << ":"
            << node->value
            << ")"
            << "->"
            << (node->next ? node->next->key : -1)
            << "} ";
        seen.insert(node);
        node = node->next;
    }
    return out;
}

class Cache{

protected:
    map<int,Node*> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function

};

class LRUCache : public Cache {
public:
    explicit LRUCache(int capacity)
//    : cp{capacity},
//      mp{map<int,Node*>{}}
     {
        head = nullptr;
        tail = nullptr;
        cp = capacity;
        mp = map<int,Node*>{};
     }
    Node * getHead() const {
        return this->head;
    }
    void set(int k, int v) override {
        auto found = traverse(k);

        if(found) {
            // already updated frequency
            found->value = v;
            cout << "Found it!" << endl;
            // TODO: add to map
            return;
        }

        promote(new Node(k, v));
    }
    void promote(Node* p) {
        if (p == nullptr || p == this->head) {
            return;
        }

        const auto hd      = this->head;
        const auto parent  = p->prev;
        const auto child   = p->next;

        if (parent) {
            parent->next = child;
        }
        if (child) {
            child->prev = parent;
        }

        p->next = hd;
        p->prev = nullptr;

        if (hd) {
            hd->prev = p;
        }

        if (this->tail == p) {
            this->tail = child;
        }
        if (this->tail == nullptr) {
            this->tail = p;
        }

        this->head = p;
    }
    int get(int k) override {
        Node* found = nullptr;

        auto fm = mp.find(k);
        if (fm != mp.end()) {
            found = fm->second;
        }
        else {
            found = traverse(k);
        }

        promote(found);
        return found ? found->value : -1;
    }
    Node * traverse(int k) {
        auto n = head;
        while(n != nullptr) {
            if (n->key == k) {
                break;
            }
            n = n->next;
        }
        if (n == nullptr) {
            return nullptr;
        }
        promote(n);
        return n;
    }
};

ostream& operator<<(ostream& out, LRUCache& lru) {
    out << "LRU:" << lru.getHead();
    return out;
}

int main() {
    auto lr = LRUCache{3};
//    cout << lr.get(0) << endl;
//    cout << lr.get(1) << endl;
//
    lr.set(100, 1);
//    cout << lr << endl;
//
//    cout << lr.get(100) << endl;
//    cout << lr << endl;
//
    lr.set(200,2);
//    cout << lr << endl;
//
//    cout << lr.get(200) << endl;
//    cout << lr << endl;
//
//    cout << lr.get(200) << endl;
//    cout << lr << endl;
//
//    cout << lr.get(100) << endl;
    cout << lr << endl;

    lr.set(300, 3);
    cout << lr << endl;

    cout << lr.get(300) << endl;
    cout << lr << endl;

    cout << lr.get(200) << endl;
    cout << lr << endl;

    cout << lr.get(100) << endl;
    cout << lr << endl;

    cout << lr.get(100) << endl;
    cout << lr << endl;

    lr.set(400, 4);
    cout << lr << endl;

    lr.set(500, 5);
    cout << lr << endl;

    lr.set(600, 6);
    cout << lr << endl;


//    cout << lr.get(100) << endl;
//    cout << lr << endl;
//    lr.set(300, 3);
//    cout << lr << endl;
//
//    cout << lr.get(300) << endl;
//    cout << lr << endl;


//    lr.set(0, 2);
//    cout << lr << endl;
//    cout << lr.get(0) << endl;
}