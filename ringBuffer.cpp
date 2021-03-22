#include <sys/time.h>
#include <stdio.h>
#include <thread>
#include <unistd.h>

using namespace std;

template <typename T>
class RingBuffer {
public:
    RingBuffer(unsigned size) : m_size(size), m_front(0), m_rear(0) {
        m_data = new T[size];
    }

    ~RingBuffer() {
        delete[] m_data;
        m_data = NULL;
    }

    inline bool isEmpty() const {
        return m_front == m_rear;
    }

    inline bool isFull() const {
        return m_front == (m_rear + 1) % m_size;
    }

    bool push(const T &value) {
        if (isFull()) {
            return false;
        }
        m_data[m_rear] = value;
        m_rear = (m_rear + 1) % m_size;
        return true;
    }

    bool push(const T *value) {
        if (isFull()) {
            return false;
        }
        m_data[m_rear] = *value;
        m_rear = (m_rear + 1) % m_size;
        return true;
    }

    inline bool pop(T &value) {
        if (isEmpty()) {
            return false;
        }
        value = m_data[m_front];
        m_front = (m_front + 1) % m_size;
        return true;
    }

    inline unsigned int front() const {
        return m_front;
    }

    inline unsigned int rear() const {
        return m_rear;
    }

    inline unsigned int size() const {
        return m_size;
    }

private:
    unsigned int m_size;// 队列长度
    int m_front;// 队列头部索引
    int m_rear;// 队列尾部索引
    T *m_data;// 数据缓冲区
};



class Test {
public:
    Test(int id = 0, int value = 0) {
        this->id = id;
        this->value = value;
        sprintf(data, "id = %d, value = %d\n", this->id, this->value);
    }

    void display() {
        printf("%s", data);
    }

private:
    int id;
    int value;
    char data[128];
};

double getdetlatimeofday(struct timeval *begin, struct timeval *end) {
    return (end->tv_sec + end->tv_usec * 1.0 / 1000000) -
           (begin->tv_sec + begin->tv_usec * 1.0 / 1000000);
}

RingBuffer<Test> que(1 << 12);

#define N (10 * (1 << 20))

void produce() {
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    unsigned int i = 0;
    while (i < N) {
        if (que.push(Test(i % 1024, i))) {
            i++;
        }
    }
    gettimeofday(&end, NULL);
    double tm = getdetlatimeofday(&begin, &end);
    printf("producer tid=%lu %f MB/s %f msg/s elapsed= %f, size= %u\n", pthread_self(),
           N * sizeof(Test) * 1.0 / (tm * 1024 * 1024), N * 1.0 / tm, tm, i);
}

void consume() {
    this_thread::sleep_for(chrono::seconds(1));
    Test test;
    struct timeval begin, end;
    gettimeofday(&begin, NULL);
    unsigned int i = 0;
    while (i < N) {
        if (que.pop(test)) {
            // test.display();
            i++;
        }
    }
    gettimeofday(&end, NULL);
    double tm = getdetlatimeofday(&begin, &end);
    printf("consumer tid=%lu %f MB/s %f msg/s elapsed= %f, size=%u \n", pthread_self(),
           N * sizeof(Test) * 1.0 / (tm * 1024 * 1024), N * 1.0 / tm, tm, i);
}

int main(int argc, char const *argv[]) {

    std::thread producer1(produce);
    std::thread consumer(consume);
    producer1.join();
    consumer.join();
    return 0;
}