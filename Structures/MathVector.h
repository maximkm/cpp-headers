#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class MathVector {
private:
    std::vector<T> data;

public:
    // Zero vector of size n
    MathVector(size_t n) {
        data.resize(n);
    }

    template <typename Iter>
    MathVector(Iter first, Iter last) {
        while (first != last)
            data.push_back(*first++);
    }

    size_t Dimension() const {
        return data.size();
    }

    T& operator[](size_t i) {
        return data[i];
    }

    const T& operator[](size_t i) const {
        return data[i];
    }

    using iterator = typename vector <T>::iterator;
    using const_iterator = typename vector <T>::const_iterator;

    iterator begin() {
        return data.begin();
    }

    iterator end() {
        return data.end();
    }

    const_iterator begin() const {
        return data.cbegin();
    }

    const_iterator end() const {
        return data.cend();
    }
};


// Output format: (1, 2, 3, 4, 5)
template <typename T>
std::ostream& operator << (std::ostream& out, const MathVector<T>& v) {
    out << '(';
    for (size_t i = 0; i != v.Dimension(); ++i) {
        if (i > 0)
            out << ", ";
        out << v[i];
    }
    out << ')';
    return out;
}

template <typename T>
MathVector<T>& operator *= (MathVector<T>& v, const T& scalar) {
    for (size_t i = 0; i != v.Dimension(); ++i)
        v[i] *= scalar;
    return v;
}

template <typename T>
MathVector<T> operator * (const MathVector<T>& v, const T& scalar) {
    MathVector<T> tmp(v.begin(), v.end());
    tmp *= scalar;
    return tmp;
}

template <typename T>
MathVector<T> operator * (const T& scalar, const MathVector<T>& v) {
    return v * scalar;
}

template <typename T>
MathVector<T>& operator += (MathVector<T>& v, const MathVector<T>& v2) {
    for (size_t i = 0; i != v.Dimension(); ++i)
        v[i] += v2[i];
    return v;
}

template <typename T>
MathVector<T> operator + (const MathVector<T>& v, const MathVector<T>& v2) {
    MathVector<T> temp(v.begin(), v.end());
    temp += v2;
    return temp;
}