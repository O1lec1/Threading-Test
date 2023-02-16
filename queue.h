#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class Queue // making std::queue thread safe. This is a monitor.
{
private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable empty_q_cond_;
public:
    Queue()=default;
    Queue(const Queue&) = delete;            // disable copying
    Queue& operator=(const Queue&) = delete; // disable assignment

    void push(T t)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(t);
        empty_q_cond_.notify_one();
    }

    T pop() // Blocking pop
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        empty_q_cond_.wait(mlock, [this]{return !queue_.empty();});
        auto val = queue_.front();
        queue_.pop();
        return val;
    }

    void pop(T& item) // pop will not wait with an empty queue
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        if (queue_.empty())
        {
            return;
        }
        item = queue_.front();
        queue_.pop();
    }
};
