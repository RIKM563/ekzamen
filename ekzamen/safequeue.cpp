#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

template<class T>
class SafeQueue {
private:
    std::queue<T> q;
    std::mutex m;

public:

    SafeQueue() = default;

    ~SafeQueue() = default;

    void Pop() {
        std::lock_guard<std::mutex> locker(m);
        q.pop();
    }

    void Push(const T &value) {
        std::lock_guard<std::mutex> locker(m);
        q.push(value);
    }

    bool TryPop(T &value) {
        if (q.front() == value) {
            if (m.try_lock()) {
                q.pop();
                m.unlock();
                return true;
            } else {
                return false;
            }
        } else return false;
    }

    size_t Size() {
        return q.size();
    }
};
