#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <list>

using namespace std;

template <typename T>
class Polynomial {
private:
    map<int, T> coefs;

public:
    Polynomial(initializer_list<T> list) {
        *this = Polynomial(list.begin(), list.end());
    }

    Polynomial() {
    }

    Polynomial(const vector<T>& _coefs) {
        for (size_t i = 0; i < _coefs.size(); ++i) {
            coefs[i] = _coefs[i];
        }
        Shrink();
    }

    Polynomial(const T& scalar) {
        coefs[0] = scalar;
        Shrink();
    }

    template <typename It>
    Polynomial(It begin, It end) {
        size_t pos = 0;
        while (begin != end)
            coefs[pos++] = *begin++;
        Shrink();
    }

    void Shrink() {
        auto it = coefs.begin();
        while (it != coefs.end()) {
            if (it->second == T(0))
                it = coefs.erase(it);
            else
                ++it;
        }
    }

    size_t Size() {
        Shrink();
        return coefs.size();
    }

    int Degree() const {
        if (coefs.empty())
            return -1;
        return coefs.rbegin()->first;
    }

    T operator[](int i) const {
        auto it = coefs.find(i);
        if (it != coefs.end())
            return it->second;
        return T(0);
    }

    T operator()(T x) const {
        if (!coefs.size())
            return 0;
        auto it = coefs.crbegin();
        T temp = it++->second;
        for (int i = Degree() - 1; i >= 0; --i) {
            if (it != coefs.crend() && i == it->first)
                temp = it++->second + temp*x;
            else
                temp = temp*x;
        }
        return temp;
    }

    typename map<int, T>::const_iterator begin() const {
        return coefs.cbegin();
    }

    typename map<int, T>::const_iterator end() const {
        return coefs.cend();
    }

    Polynomial<T>& operator+=(Polynomial<T> sec) {
        for (auto [x, y] : sec.coefs)
            coefs[x] += y;
        Shrink();
        return *this;
    }

    Polynomial<T>& operator-=(Polynomial<T> sec) {
        for (auto [x, y] : sec.coefs)
            coefs[x] -= y;
        Shrink();
        return *this;
    }

    Polynomial<T>& operator*=(Polynomial<T> sec) {
        map<int, T> res;
        for (auto [x, y] : coefs) {
            for (auto [i, j] : sec.coefs) {
                res[x + i] += y*j;
            }
        }
        coefs = res;
        Shrink();
        return *this;
    }

    friend bool operator==(const Polynomial<T>& ft, const Polynomial<T>& sec) {
        return ft.coefs == sec.coefs;
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
        auto it = ft.begin();
        if (it == ft.end())
            return res;
        if (it->first == 0) {
            res += it->second;
            ++it;
        }
        Polynomial<T> temp = sec;
        for (int i = 1; i <= ft.Degree(); ++i) {
            if (i == it->first) {
                res += it->second * temp;
                ++it;
            }
            temp *= sec;
        }
        res.Shrink();
        return res;
    }

    friend ostream& operator<<(ostream& out, Polynomial<T> ft) {
        if (!ft.Size()) {
            out << "0";
            return out;
        }
        auto it = ft.coefs.crbegin();
        size_t i = 0;
        while (it != ft.coefs.crend()) {
            if (it->first != 0) {
                if (it->second == T(1)) {
                    if (i != 0)
                        out << '+';
                    if (it->first != 1)
                        out << "x^" << it->first;
                    else
                        out << "x";
                } else if (it->second == T(-1)) {
                    if (it->first != 1)
                        out << "-x^" << it->first;
                    else
                        out << "-x";
                } else {
                    if (i != 0 && it->second > T(0))
                        out << '+';
                    out << it->second << '*';
                    if (it->first != 1)
                        out << "x^" << it->first;
                    else
                        out << "x";
                }
            } else {
                if (i != 0 && it->second > T(0))
                    out << '+';
                out << it->second;
            }
            ++it;
            ++i;
        }
        return out;
    }

    friend Polynomial<T> operator/(Polynomial<T> ft, Polynomial<T> sec) {
        Polynomial<T> res;
        sec.Shrink();
        while (ft.Degree() >= sec.Degree()) {
            Polynomial<T> temp;
            temp.coefs[ft.Degree() - sec.Degree()] = ft[ft.Degree()]/sec[sec.Degree()];
            ft -= sec * temp;
            res += temp;
        }
        return res;
    }

    friend Polynomial<T> operator/(Polynomial<T> ft, T sec) {
        for (auto& [x, y] : ft.coefs) {
            y /= sec;
        }
        return ft;
    }
};


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
    if (sec.Degree() != -1)
        return sec/sec[sec.Degree()];
    return T(0);
}