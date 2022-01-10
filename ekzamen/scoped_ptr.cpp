#include <memory>

template<class T>
class scoped_ptr {
private:
    T *ptr;
public:
    scoped_ptr(T *value) { ptr = value; };

    ~scoped_ptr() { delete ptr; }

    T *operator->() { return ptr; }

    T &operator*() { return *ptr; }

    T *get() { return ptr; }
};

template<typename T, typename... Args>
scoped_ptr<T> make_scoped(Args &&... args) {
    return scoped_ptr<T>(new T(std::forward<Args>(args)...));
}