//
// Created by USER1 on 10.01.2022.
//

#include <atomic>

#include "memory"
#include "utility"

template<typename T>
class SharedPtr {
private:
    T *object{nullptr};
    std::atomic_uint *count{nullptr};

public:
    SharedPtr() { count = new std::atomic_uint(0); }

    explicit SharedPtr(T *ptr) {
        object = ptr;
        count = new std::atomic_uint(0);
        *count += 1;
    }

    SharedPtr(const SharedPtr &r) {
        count = r.count;
        object = r.object;
        *count += 1;
    }

    SharedPtr(SharedPtr &&r) {
        count = std::move(r.count);
        object = std::move(r.object);
        *count += 1;
    }

    ~SharedPtr() {
        if (*count != 0) {
            --(*count);
        }
        if (*count == 0) {
            delete object;
            delete count;
        }
    }

    auto operator=(const SharedPtr &r) -> SharedPtr & {
        delete count;
        object = r.object;
        count = r.count;
        *count += 1;
        return *this;
    }

    auto operator=(SharedPtr &&r) -> SharedPtr & {
        delete count;
        object = std::move(r.object);
        count = std::move(r.count);
        *count += 1;
        return *this;
    }

    operator bool() const { return object != nullptr; }

    auto operator*() const -> T & { return *object; }

    auto operator->() const -> T * { return object; }

    auto get() -> T * { return object; }

    T *release() {
        T *newptr = object;
        (*count)--;
        delete object;
        return newptr;
    }

    void reset() {
        delete count;
        count = new std::atomic_uint(0);
        object = nullptr;
    }

    void reset(T *ptr = nullptr) {
        *count -= 1;
        delete count;
        count = new std::atomic_uint(0);
        object = ptr;
    }

    void swap(SharedPtr &r) {
        std::swap(object, r.object);
        std::swap(count, r.count);
    }
};