#include <algorithm>
#include <cstddef>
#include <utility>

template<typename T>
class UniquePtr {
private:
    T* data = nullptr;

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

public:
    UniquePtr() noexcept : data(nullptr) {}

    UniquePtr(std::nullptr_t) noexcept : data(nullptr) {}

    UniquePtr(T* temp) noexcept : data(temp) {}

    UniquePtr(UniquePtr&& other) noexcept : data(other.data) {
        other.data = nullptr;
    }

    UniquePtr& operator=(std::nullptr_t temp) noexcept {
        data = nullptr;
        return *this;
    }

    UniquePtr& operator=(UniquePtr&& other) {
        delete data;
        data = other.data;
        other.data = nullptr;
        return *this;
    }

    T& operator*() noexcept {
        return *data;
    }

    const T& operator*() const noexcept {
        return *data;
    }

    T* operator->() const noexcept {
        return data;
    }

    T* release() noexcept {
        T* temp = data;
        data = nullptr;
        return temp;
    }

    void reset(T* ptr) {
        delete data;
        data = nullptr;
        std::swap(data, ptr);
    }

    void swap(UniquePtr<T>& other) {
        std::swap(data, other.data);
    }

    T* get() const noexcept {
        return data;
    }

    explicit operator bool() const noexcept {
        return data != nullptr;
    }

    ~UniquePtr() {
        delete data;
    }
};