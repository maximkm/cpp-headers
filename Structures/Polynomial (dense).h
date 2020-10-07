#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

template <typename T>
class Polynomial {
private:
    vector<T> coefs;

public:
    Polynomial(initializer_list<T> list) {
        *this = Polynomial(list.begin(), list.end());
    }

    Polynomial() {
    }

    Polynomial(const vector<T>& _coefs) : coefs(_coefs) {
        Shrink();
    }

    Polynomial(const T& scalar) : coefs({scalar}) {
        Shrink();
    }

    template <typename It>
    Polynomial(It begin, It end) {
        while (begin != end)
            coefs.emplace_back(*begin++);
        Shrink();
    }

    void Shrink() {
        while (!coefs.empty() && coefs.back() == T(0))
            coefs.pop_back();
    }

    size_t Size() {
        Shrink();
        return coefs.size();
    }

    int Degree() const {
        return static_cast<int>(coefs.size()) - 1;
    }

    const vector<T>& GetCoefs() const {
        return coefs;
    }

    const T operator[](int i) const {
        if (0 <= i && i <= Degree())
            return coefs[i];
        return 0;
    }

    T operator()(T x) const {
        if (!coefs.size())
            return 0;
        auto it = coefs.crbegin();
        T temp = *it++;
        while (it != coefs.crend()) {
            temp = *it++ + temp*x;
        }
        return temp;
    }

    typename vector<T>::const_iterator begin() const {
        return coefs.cbegin();
    }

    typename vector<T>::const_iterator end() const {
        return coefs.cend();
    }

    Polynomial<T>& operator+=(Polynomial<T> sec) {
        size_t mx = sec.Size(), res = max(Size(), mx);
        coefs.resize(res, 0);
        for (size_t i = 0; i < mx; ++i) {
            coefs[i] += sec[i];
        }
        Shrink();
        return *this;
    }

    Polynomial<T>& operator-=(Polynomial<T> sec) {
        size_t mx = sec.Size(), res = max(Size(), mx);
        coefs.resize(res, 0);
        for (size_t i = 0; i < mx; ++i) {
            coefs[i] -= sec[i];
        }
        Shrink();
        return *this;
    }

    Polynomial<T>& operator*=(Polynomial<T> sec) {
        size_t sz = Size() + sec.Size();
        if (sz == 0)
            return *this;
        coefs.resize(--sz, 0);
        sec.coefs.resize(sz, 0);
        vector<T> res(sz, 0);
        for (size_t i = 0; i < sz; ++i) {
            for (size_t j = 0; j <= i; ++j) {
                res[i] += coefs[j] * sec.coefs[i - j];
            }
        }
        coefs = res;
        Shrink();
        return *this;
    }

    friend bool operator==(const Polynomial<T>& ft, const Polynomial<T>& sec) {
        return ft.GetCoefs() == sec.GetCoefs();
    }

    friend bool operator!=(const Polynomial<T>& ft, const Polynomial<T>& sec) {
        return !(ft == sec);
    }

    friend Polynomial<T> operator+(Polynomial<T> ft, const Polynomial<T>& sec) {
        return ft += sec;
    }

    friend Polynomial<T> operator-(Polynomial<T> ft, const Polynomial<T>& sec) {
        return ft -= sec;
    }

    friend Polynomial<T> operator*(Polynomial<T> ft, const Polynomial<T>& sec) {
        return ft *= sec;
    }

    friend Polynomial<T> operator&(Polynomial<T> ft, const Polynomial<T>& sec) {
        Polynomial<T> res;
        res += ft[0];
        size_t sz = ft.Size();
        for (size_t i = 1; i < sz; ++i) {
            if (ft[i] == T(0))
                continue;
            Polynomial<T> temp = sec;
            for (size_t j = 1; j < i; ++j)
                temp *= sec;
            res += ft[i] * temp;
        }
        return res;
    }
};

template <typename T>
Polynomial<T> operator/(Polynomial<T> ft, Polynomial<T> sec) {
    Polynomial<T> res;
    sec.Shrink();
    while (ft.Degree() >= sec.Degree()) {
        vector<T> next(ft.Degree() - sec.Degree() + 1, 0);
        next.back() = ft[ft.Degree()]/sec[sec.Degree()];
        Polynomial<T> temp(next);
        ft -= sec * temp;
        res += temp;
    }
    return res;
}

template <typename T>
Polynomial<T> operator/(Polynomial<T> ft, T sec) {
    vector<T> res(ft.Size(), 0);
    for (size_t i = 0; i < ft.Size(); ++i)
        res[i] = ft[i]/sec;
    return Polynomial<T>(res);
}

template <typename T>
Polynomial<T> operator%(Polynomial<T> ft, const Polynomial<T>& sec) {
    return ft - (ft/sec)*sec;
}

template <typename T>
Polynomial<T> operator,(Polynomial<T> ft, Polynomial<T> sec) {
    while (ft != T(0) && sec.Degree() > 0) {
        sec = sec % ft;
        swap(ft, sec);
    }
    if (sec.Size())
        return sec/sec[sec.Degree()];
    return T(0);
}

template <typename T>
ostream& operator<<(ostream& out, Polynomial<T> ft) {
    auto tmp = ft.Size();
    if (!tmp--) {
        out << "0";
        return out;
    }
    auto data = ft.GetCoefs();
    for (size_t i = 0; i <= tmp; ++i) {
        if (data[tmp - i] == T(0))
            continue;
        if (tmp - i != 0) {
            if (data[tmp - i] == T(1)) {
                if (i != 0)
                    out << '+';
                if (tmp - i != 1)
                    out << "x^" << tmp-i;
                else
                    out << "x";
            } else if (data[tmp - i] == T(-1)) {
                if (tmp - i != 1)
                    out << "-x^" << tmp-i;
                else
                    out << "-x";
            } else {
                if (i != 0 && data[tmp - i] > T(0))
                    out << '+';
                out << data[tmp - i] << '*';
                if (tmp - i != 1)
                    out << "x^" << tmp-i;
                else
                    out << "x";
            }
        } else {
            if (i != 0 && data[tmp - i] > T(0))
                out << '+';
            out << data[tmp - i];
        }
    }
    return out;
}