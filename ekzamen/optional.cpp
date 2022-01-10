//
// Created by USER1 on 10.01.2022.
//

#include <iostream>
#include <new>
#include <optional>
#include <utility>

template <typename T>
class optional {
private:
    T* data;
    bool contain;

public:
    constexpr optional() noexcept {
        data = nullptr;
        contain = false;
    }

    constexpr explicit optional(std::nullopt_t) noexcept {
        data = nullptr;
        contain = false;
    }

    constexpr optional(const optional& other) {
        if (std::is_copy_constructible_v<T>) {
            if (other.data != nullptr) {
                T obj;
                data = new (&obj) T(*other.data);
                contain = true;
            } else {
                data = nullptr;
                contain = false;
            }
        }
    }

    constexpr optional(optional&& other) noexcept {
        if (std::is_move_constructible_v<T>) {
            if (other.data != nullptr) {
                T obj;
                data = new (&obj) T;
                *data = std::move(other.data);
                contain = true;
            } else {
                data = std::nullopt;
                contain = false;
            }
        }
    }

    template <class... Args>
    constexpr explicit optional(std::in_place_t, Args&&... args) {
        if (std::is_constructible_v<T, Args...>) {
            T obj(std::forward<Args>(args)...);
            data = new (&obj) T(std::forward<Args>(args)...);
            contain = true;
        }
    }

    ~optional() {
        if (contain)
            if (!std::is_trivially_destructible_v<T>) {
                data->T::~T();
            }
    }

    optional<T>& operator=(const optional<T>& other) {
        if ((contain) && (!other.contain)) {
            contain = false;
            data = nullptr;
        }
        if ((contain) && (other.contain)) {
            if (std::is_copy_assignable_v<T>) {
                T obj;
                data = new (&obj) T;
            }
        }
    }

    optional<T>& operator=(optional<T>&& other) {
        if ((contain) && (!other.contain)) {
            contain = false;
            data = nullptr;
        }
        if ((contain) && (other.contain)) {
            if (std::is_move_assignable_v<T>) {
                T obj;
                data = new (&obj) T;
                *data = std::move(other.data);
                contain = true;
            }
        }
    }

    T& operator*() { return *data; }

    T* operator->() { return data; }

    explicit operator bool() const { return contain; }

    T& value() {
        if (contain) return *data;
        throw std::bad_optional_access{};
    }

    template <class U>
    T value_or(U&& default_value) {
        if (contain) return *data;
        return static_cast<T>(std::forward<U>(default_value));
    }
};

template <class T, class... Args>
constexpr optional<T> make_optional(Args&&... args) {
    return optional<T>(std::in_place, std::forward<Args>(args)...);
}
