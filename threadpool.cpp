#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <queue>
#include <future>
#include <iostream>
#include <functional>

class ThreadPool {
public:
    explicit ThreadPool(size_t threadNum) : stop_(false) {
        for(size_t i = 0; i < threadNum; ++i) {
            workers_.emplace_back([this]() {
                for(;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> ul(mtx_);
                        cv_.wait(ul, [this]() { return stop_ || !tasks_.empty(); });
                        if(stop_ && tasks_.empty()) { return; }
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> ul(mtx_);
            stop_ = true;
        }
        cv_.notify_all();
        for(auto& worker : workers_) {
            worker.join();
        }
    }

    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        auto taskPtr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        {
            std::unique_lock<std::mutex> ul(mtx_);
            if(stop_) { throw std::runtime_error("submit on stopped ThreadPool"); }
            tasks_.emplace([taskPtr]() { (*taskPtr)(); });
        }
        cv_.notify_one();
        return taskPtr->get_future();
    }

private:
    bool stop_;
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mtx_;
    std::condition_variable cv_;
};


int main(int argc, char* argv[]){

    ThreadPool pool(4);
    std::vector<std::future<int>> results;
    results.reserve(8);
    for(int i = 0; i < 8; ++i) {
        results.emplace_back(pool.submit([i]() {
            // computing task and return result
            printf("I am task %d\n", i);
            return i;
        }));
    }
    for(auto && result: results)
        std::cout << result.get() << ' ';

    return 0;
}