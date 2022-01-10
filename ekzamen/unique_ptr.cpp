//
// Created by USER1 on 07.01.2022.
//

template<class T>
class unique_ptr {
private:
    T *data;

public:
    unique_ptr() {
        data = nullptr;
    }

    ~unique_ptr() {
        delete data;
    }

    unique_ptr(unique_ptr<T> &&rhs) noexcept {
        data = std::move(rhs.data);
        delete rhs.data;
    }

    explicit unique_ptr(T *smth) {
        data = smth;
    }

    unique_ptr<T> &operator=(unique_ptr<T> &&rhs) noexcept {
        delete data;
        data = std::move(rhs.data);
        delete rhs.data;
    }

    void reset(T *ptr) {
        if (data == ptr) {
            delete data;
            data = nullptr;
        } else {
            delete data;
            data = ptr;
        }
    }

    T *release() {
        T *copy = data;
        delete data;
        data = nullptr;
        return copy;
    }

    void swap(unique_ptr<T> &rhs) {
        T *copy = data;
        delete data;
        data = rhs.data;
        delete rhs.data;
        rhs.data = copy;
    }

    T operator->() {
        return data;
    }

    T &operator() {
            return *data;
    }

    explicit operator bool() const {
        if (data == nullptr)
            return false;
        return true;
    }

    [[nodiscard]] T *get() const noexcept {
        return data;
    }

    unique_ptr(unique_ptr<T> &a) = delete;

    unique_ptr<T> operator=(unique_ptr<T> &a) = delete;
}

template<class T, class... Args>
unique_ptr<T> make_unique(Args &&... args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

