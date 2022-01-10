//
// Created by USER1 on 08.01.2022.
//

#include <iostream>
#include <mutex>
#include <stack>

template<class T>

class SafeStack {

private:
    std::stack<T> st;
    std::mutex mut;

public:

    ~SafeStack() = default;

    SafeStack() = default;

    void Pop() {
        std::lock_guard<std::mutex> locker(mut); //mut.lock();
        if (!st.empty()) {
            st.pop();
        }
        //mut.unlock()
    }

    void Push(const T &value) {
        std::lock_guard<std::mutex> locker(mut); //mut.lock();
        st.push(value);
        //mut.unlock();
    }

    bool TryPop(T &value) {
        if (st.top() == value) {
            if (mut.try_lock()) {
                st.pop();
                mut.unlock();
                return true;
            } else return false;
        } else {
            return false;
        }
    }
};
