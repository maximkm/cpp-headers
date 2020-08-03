#include <utility>

// Это исключение нужно генерировать в функции value
// при обращении к пустому объекту Optional
struct BadOptionalAccess {};

template<typename T>
class Optional {
private:
    // alignas нужен для правильного выравнивания блока памяти
    alignas(T) unsigned char data[sizeof(T)];
    bool defined = false;

public:
    Optional() = default;
    Optional(const T& elem) {
        new (data) T(elem);
        defined = true;
    }
    Optional(T && elem) {
        new (data) T(std::move(elem));
        defined = true;
    }
    Optional(const Optional& other) {
        if (other.defined)
            new (data) T(*reinterpret_cast<T*>(other.data));  // !!
        defined = other.defined;
    }

    Optional& operator=(const Optional& other) {
        if (other.defined) {
            if (defined)
                *reinterpret_cast<T*>(data) = *reinterpret_cast<const T*>(other.data);
            else
                new (data) T(*reinterpret_cast<const T*>(other.data));
            defined = true;
        } else {
            if (defined)
                reinterpret_cast<T*>(data)->~T();
            defined = false;
        }
        return *this;
    }
    Optional& operator=(const T& elem) {
        if (defined) {
            *reinterpret_cast<T*>(data) = elem;
        } else {
            new (data) T(elem);
            defined = true;
        }
        return *this;
    }
    Optional& operator=(T&& elem) {
        if (defined) {
            *reinterpret_cast<T*>(data) = std::move(elem);
        } else {
            new (data) T(std::move(elem));
            defined = true;
        }
        return *this;
    }

    bool has_value() const { return defined; }

    T& operator*() { return *reinterpret_cast<T*>(data); }
    const T& operator*() const { return *reinterpret_cast<const T*>(data); }

    T* operator->() { return reinterpret_cast<T*>(data); }
    const T* operator->() const { return reinterpret_cast<const T*>(data); }

    T& value() {
        if (!defined)
            throw BadOptionalAccess();
        return *reinterpret_cast<T*>(data);
    }
    const T& value() const {
        if (!defined)
            throw BadOptionalAccess();
        return *reinterpret_cast<const T*>(data);
    }

    void reset() {
        if (defined) {
            reinterpret_cast<T*>(data)->~T();
            defined = false;
        }
    }

    ~Optional() {
        if (defined)
            reinterpret_cast<T*>(data)->~T();
    }
};