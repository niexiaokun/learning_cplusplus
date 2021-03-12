#include <bits/stdc++.h>


using namespace std;


int global_var = 0;

class Singleton {
private:
    Singleton() {
        cout << "Singleton()" << endl;
    }

    Singleton(const Singleton &) = delete;

    Singleton &operator=(const Singleton &) = delete;

    static shared_ptr<Singleton> mptr;
    static std::mutex mtx;
public:
    ~Singleton() {
        cout << "~Singleton()" << endl;
    }

    static shared_ptr<Singleton> getInstance() {
        if (mptr == nullptr) {
            std::unique_lock<std::mutex> lck(mtx);
            if (mptr == nullptr) {
                mptr = shared_ptr<Singleton>(new Singleton);
                ++global_var;
            }
        }
        return mptr;
    }

    void f() const {
        cout << global_var << endl;
    }
};

shared_ptr<Singleton> Singleton::mptr = nullptr;
std::mutex Singleton::mtx;


int main(int argc, char* argv[]) {

    shared_ptr<Singleton> instance = Singleton::getInstance();
    instance->f();
    shared_ptr<Singleton> instance2 = Singleton::getInstance();
    instance2->f();
    assert(instance == instance2);

    auto func = [] {
        shared_ptr<Singleton> instance = Singleton::getInstance();
        instance->f();
        cout << instance << endl;
    };
    thread th[5];
    for (int i = 0; i < 5; ++i)
        th[i] = thread(func);
    for (int i = 0; i < 5; ++i) {
        if (th[i].joinable())
            th[i].join();
    }

    return 0;
}