//
// Created by USER1 on 08.01.2022.
//
#include <mutex>

template <class Mutex>
class lock_guard {
private:
    Mutex *mut;
    bool ownership;

public:
    explicit lock_guard(Mutex &m) {
        mut = m;
        m.lock();
        ownership = true;
    }

    lock_guard(Mutex &m, std::adopt_lock_t) {
        mut = m;
        ownership = true;
    }

    lock_guard(const lock_guard &l) = delete;

    ~lock_guard() {
        ownership = false;
        mut->unlock();
    }

    lock_guard &operator=(const lock_guard &) = delete;
};
