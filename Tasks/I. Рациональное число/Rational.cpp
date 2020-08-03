#include <iostream>
#include <cmath>
#include <numeric>

using namespace std;

class Rational {
private:
    int num = 0;
    int den = 1;

public:
    Rational& Simplify() {
        int x = gcd(num, den);
        num /= x;
        den /= x;
        if (den < 0) {
            den *= -1;
            num *= -1;
        }
        return *this;
    }

    Rational() {
    }

    Rational(int x, int y)
    : num(x)
    , den(y) {
        this->Simplify();
    }

    int& numerator() {
        return num;
    }

    int& denominator() {
        return den;
    }

    int numerator() const {
        return num;
    }

    int denominator() const {
        return den;
    }

    Rational operator-() const {
        return Rational(-num, den);
    }

    Rational operator+() const {
        return *this;
    }

    Rational& operator++();
    Rational& operator--();

    Rational operator++(int);
    Rational operator--(int);
};

Rational& operator+=(Rational& ft, const Rational& st) {
    int temp = abs(ft.denominator() * st.denominator())/gcd(ft.denominator(), st.denominator());
    ft = Rational(temp/ft.denominator()*ft.numerator() + temp/st.denominator()*st.numerator(),
                temp);
    return ft.Simplify();
}

Rational& operator+=(Rational& ft, int k) {
    return ft += Rational(k, 1);
}

Rational& operator-=(Rational& ft, const Rational& st) {
    int temp = abs(ft.denominator() * st.denominator())/gcd(ft.denominator(), st.denominator());
    ft = Rational(temp/ft.denominator()*ft.numerator() - temp/st.denominator()*st.numerator(),
                temp);
    return ft.Simplify();
}

Rational& operator-=(Rational& ft, int k) {
    Rational st(k, 1);
    return ft -= st;
}

Rational& operator*=(Rational& ft, const Rational& st) {
    ft = Rational(ft.numerator()*st.numerator(), ft.denominator()*st.denominator());
    return ft.Simplify();
}

Rational& operator*=(Rational& ft, int k) {
    return ft *= Rational(k, 1);
}

Rational& operator/=(Rational& ft, const Rational& st) {
    ft = Rational(ft.numerator()*st.denominator(), ft.denominator()*st.numerator());
    return ft.Simplify();
}

Rational& operator/=(Rational& ft, int k) {
    return ft /= Rational(k, 1);
}

Rational operator+(const Rational& ft, const Rational& st) {
    Rational temp = ft;
    return temp += st;
}

Rational operator+(const Rational& ft, int k) {
    return ft + Rational(k, 1);
}

Rational operator+(int k, const Rational& ft) {
    return ft + k;
}

Rational operator-(const Rational& ft, const Rational& st) {
    Rational temp = ft;
    return temp -= st;
}

Rational operator-(const Rational& ft, int k) {
    return ft - Rational(k, 1);
}

Rational operator-(int k, const Rational& ft) {
    return -(ft - k);
}

Rational operator*(const Rational& ft, const Rational& st) {
    Rational temp = ft;
    return temp *= st;
}

Rational operator*(const Rational& ft, int k) {
    return ft * Rational(k, 1);
}

Rational operator*(int k, const Rational& ft) {
    return ft * k;
}

Rational operator/(const Rational& ft, const Rational& st) {
    Rational temp = ft;
    return temp /= st;
}

Rational operator/(const Rational& ft, int k) {
    return ft / Rational(k, 1);
}

Rational operator/(int k, const Rational& ft) {
    return Rational(k, 1) / ft;
}

Rational& Rational::operator++() {
    *this += 1;
    return *this;
}

Rational& Rational::operator--() {
    *this -= 1;
    return *this;
}

Rational Rational::operator++(int) {
    Rational temp = *this;
    *this += 1;
    return temp;
}

Rational Rational::operator--(int) {
    Rational temp = *this;
    *this -= 1;
    return temp;
}

bool operator==(const Rational& ft, const Rational& st) {
    return (ft.numerator() == st.numerator()) && (ft.denominator() == st.denominator());
}

bool operator!=(const Rational& ft, const Rational& st) {
    return !(ft == st);
}