#include <bits/stdc++.h>

using namespace std;


template <typename T>
class SmartPtr {
private :
    T *_ptr;
    size_t *_count;

public:
    SmartPtr(T *ptr = nullptr) : _ptr(ptr) {
        if (_ptr) {
            _count = new size_t(1);
        } else {
            _count = new size_t(0);
        }
    }

    ~SmartPtr() {
        (*this->_count)--;
        if (*this->_count == 0) {
            delete this->_ptr;
            delete this->_count;
        }
    }

    SmartPtr(const SmartPtr &ptr) // 拷贝构造：计数 +1
    {
        if (this != &ptr) {
            this->_ptr = ptr._ptr;
            this->_count = ptr._count;
            (*this->_count)++;
        }
    }

    SmartPtr &operator=(const SmartPtr &ptr) // 赋值运算符重载
    {
        if (this->_ptr == ptr._ptr) {
            return *this;
        }
        if (this->_ptr) // 将当前的 ptr 指向的原来的空间的计数 -1
        {
            (*this->_count)--;
            if (this->_count == 0) {
                delete this->_ptr;
                delete this->_count;
            }
        }
        this->_ptr = ptr._ptr;
        this->_count = ptr._count;
        (*this->_count)++; // 此时 ptr 指向了新赋值的空间，该空间的计数 +1
        return *this;
    }

    T &operator*() const {
        assert(this->_ptr != nullptr);
        return *(this->_ptr);
    }

    T *operator->() const {
        assert(this->_ptr != nullptr);
        return this->_ptr;
    }

    size_t use_count() {
        return *this->count;
    }
};

struct Point{
    int x, y;
    Point(int _x, int _y):x(_x),y(_y){}
    void display(){
        cout << "(" << x << ", " << y << ")" << endl;
    }
    friend ostream&operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")" << endl;
        return os;
    }
};



int main(int argc, char* argv[]){

    SmartPtr<Point> ptr(new Point(3, 4));

    ptr->display();

    cout << *ptr <<endl;

    return 0;
}