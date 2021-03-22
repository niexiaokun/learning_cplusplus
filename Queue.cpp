#include <iostream>
#include <assert.h>

using namespace std;

template <typename T>
struct ListNode {
    T val;
    ListNode *next;
    ListNode(T x) : val(x), next(NULL) {}
};

template <typename T>
class Queue {
private:
    ListNode<T>* m_front;
    ListNode<T>* m_tail;
    int m_size;
public:
    Queue():m_front(nullptr), m_tail(nullptr), m_size(0){

    }
    ~Queue(){
        m_tail = nullptr;
        deleteNode(m_front);
    }
    void deleteNode(ListNode<T>* head){
        if(head == nullptr)
            return;
        deleteNode(head->next);
        delete head;
    }
    void add(T x){
        if(m_size == 0){
            m_front = new ListNode(x);
            m_tail = m_front;
            ++m_size;
            return;
        }
        m_tail->next = new ListNode(x);
        m_tail = m_tail->next;
        ++m_size;
    }
    void pop(){
        ListNode<T>* node = m_front;
        m_front = m_front->next;
        --m_size;
        if(m_size == 0)
            m_tail = m_front;
        delete node;
    }
    T front() const{
        assert(m_size);
        return m_front->val;
    }
    void remove(T x) {
        if (m_size == 0)
            return;
        if (m_front->val == x) {
            pop();
            return;
        }
        ListNode<T> *p = m_front;
        while(p->next && p->next->val != x){
            p = p->next;
        }
        if(p->next == nullptr)
            return;
        ListNode<T>* node = p->next;
        p->next = node->next;
        delete node;
        --m_size;
    }
    bool isEmpty() const{
        return m_size == 0;
    }
};


int main(int argc, char* argv[]){
    
    Queue<int> q;
    for(int i = 1; i <= 10; ++i)
        q.add(i);

    q.remove(2);
    q.remove(5);
    q.remove(10);
    q.remove(1);

    while(!q.isEmpty()){
        cout << q.front() << endl;
        q.pop();
    }

    return 0;
}