#include <bits/stdc++.h>

using namespace std;


class BaseNode {
private:
    void deleteNode(BaseNode *head) {
        if (head == nullptr)
            return;
        deleteNode(head->next);
        head = nullptr;
    }

public:
    BaseNode *next;

    BaseNode() {
        next = nullptr;
    }

    virtual ~BaseNode() {
        deleteNode(next);
    }

    virtual void operator<<(ostream &os) = 0;
};

template <typename T>
class Node : public BaseNode {
private:
    T val;
public:
    BaseNode *next;

    Node(T val) {
        this->val = val;
        next = nullptr;
    }

    virtual ~Node() {
        delete next;
    }

    virtual void operator<<(ostream &os) {
        os << val;
    }
};

class List {
private:
    BaseNode *head;
    BaseNode *tail;
public:
    List() {
        head = tail = nullptr;
    }

    ~List() {
        if (head) {
            delete head;
            delete tail;
        }
    }

    template<typename T>
    void add(T val) {
        if (head == nullptr) {
            head = new Node<T>(val);
            tail = head;
        }
        tail->next = new Node<T>(val);
        tail = tail->next;
    }

    friend ostream &operator<<(ostream &os, const List &list) {
        if (list.head == nullptr) {
            os << "nullptr" << endl;
            return os;
        }
        BaseNode *cur = list.head;
        os << "[ ";
        while (cur != list.tail) {
            cur->operator<<(os);
            cout << " ";
            cur = cur->next;
        }
        cur->operator<<(os);
        cout << " ]";
        return os;
    }
};

int main(int argc, char* argv[]){

    List list;

    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5.6);
    list.add('x');
    list.add(string("abc"));

    cout<<list<<endl;

    return 0;
}
