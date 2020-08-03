#include <iostream>
#include <cmath>

using namespace std;

class Complex {
private:
    double re = 0;
    double im = 0;

public:
    Complex(double first)
    : re(first) {
    }

    Complex(double first, double second)
    : re(first)
    , im(second) {
    }

    double& Re() {
        return re;
    }

    double& Im() {
        return im;
    }

    double Re() const {
        return re;
    }

    double Im() const {
        return im;
    }

    Complex operator-() const {
        return Complex(-re, -im);
    }

    Complex operator+() const {
        return Complex(re, im);
    }
};

double abs(const Complex& ft) {
    return sqrt(ft.Re()*ft.Re() + ft.Im()*ft.Im());
}

Complex operator+(const Complex& ft, const Complex& sc) {
    return Complex(ft.Re() + sc.Re(), ft.Im() + sc.Im());
}

Complex operator+(const Complex& ft, double sc) {
    return Complex(ft.Re() + sc, ft.Im());
}

Complex operator+(double sc, const Complex& ft) {
    return ft + sc;
}

Complex operator-(const Complex& ft, const Complex& sc) {
    return Complex(ft.Re() - sc.Re(), ft.Im() - sc.Im());
}

Complex operator-(const Complex& ft, double sc) {
    return Complex(ft.Re() - sc, ft.Im());
}

Complex operator-(double sc, const Complex &ft) {
    return -(ft - sc);
}

Complex operator*(const Complex& ft, const Complex& sc) {
    return Complex(ft.Re()*sc.Re() - ft.Im()*sc.Im(),
            ft.Re()*sc.Im() + ft.Im()*sc.Re());
}

Complex operator*(const Complex& ft, double sc) {
    return Complex(ft.Re() * sc, ft.Im() * sc);
}

Complex operator*(double sc, const Complex& ft) {
    return ft * sc;
}

Complex operator/(const Complex& ft, double sc) {
    return Complex(ft.Re() / sc, ft.Im() / sc);
}

Complex operator/(const Complex& ft, const Complex& sc) {
    double denom = abs(sc);
    Complex temp(sc.Re(), -sc.Im());
    Complex inv = temp / (denom * denom);
    return ft * inv;
}


Complex operator/(double sc, const Complex& ft) {
    double denom = abs(ft);
    Complex temp(ft.Re(), -ft.Im());
    Complex inv = temp / (denom * denom);
    return sc * inv;
}

bool operator==(const Complex& ft, const Complex& sc) {
    return ft.Re() == sc.Re() && ft.Im() == sc.Im();
}

bool operator!=(const Complex& ft, const Complex& sc) {
    return !(ft == sc);
}