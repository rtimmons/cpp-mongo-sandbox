//
// Created by Ryan Timmons on 3/26/18.
//

#include <iostream>

using namespace std;

template <class T>
class complex_base {
private:
    T real_pt;
    T imag_pt;
public:
    explicit complex_base() : complex_base({},{}) {}

    complex_base(T real_, T imag_={})
    : real_pt{real_}, imag_pt{imag_} {}

    complex_base(const complex_base& rhs)
    : real_pt{rhs.real_pt}, imag_pt{rhs.imag_pt} {}

    inline complex_base& operator=(const complex_base& rhs) = default;

    inline T real() const { return this->real_pt; }
    inline T imag() const { return this->imag_pt; }

    inline complex_base& operator+=(const complex_base& other) {
        this->real_pt += other.real_pt;
        this->imag_pt += other.imag_pt;
        return *this;
    }
    inline complex_base& operator-=(const complex_base& other) {
        this->real_pt -= other.real_pt;
        this->imag_pt -= other.imag_pt;
        return *this;
    }
    inline complex_base& operator*=(const complex_base& other) {
        auto real = (this->real_pt * other.real_pt) - (this->imag_pt * other.imag_pt);
        this->imag_pt = (this->real_pt * other.imag_pt) + (this->imag_pt * other.real_pt);
        this->real_pt = real;
        return *this;
    }
};

inline complex_base<long double> operator"" _i(const long double imag) {
    return {0, imag};
}

template <class T>
inline complex_base<T> operator+(T a, const complex_base<T>& b) {
    return complex_base<T>{a} += b;
}

//inline complex_base<long double> operator+(long double a, const complex_base<long double>& b) {
//    return complex_base<long double>{a} += b;
//}

inline complex_base<long double> operator+(complex_base<long double> b, int a) {
    return b += a;
}

inline complex_base<long double> operator+(int a, complex_base<long double> b) {
    return b += a;
}


template <class T>
inline complex_base<T> operator+(complex_base<T> a, const complex_base<T>& b) {
    return a+=b;
}

template <class T>
inline complex_base<T> operator-(complex_base<T> a,const complex_base<T>& b) {
    return a-=b;
}
template <class T>
inline complex_base<T> operator*(complex_base<T> a,const complex_base<T>& b) {
    return a*=b;
}


template <class T>
ostream& operator<<(ostream& io, const complex_base<T>& c) {
    io << "(" << c.real() << "+" << c.imag() << "i" << ")";
    return io;
}

using complex = complex_base<long double>;

int main() {
    complex a = 3 + 1.0_i;
    complex b = 3 + 1.0_i;
    complex d = -100.0 + 1.0_i;
    auto const c = b;
    cout << "c is " << c << endl;
    b = a;
    a = a;

    cout << a       << endl;
    cout << (a*a)   << endl;
    cout << (a+b)   << endl;
    cout << (a-b)   << endl;
    cout << (a*b)   << endl;
    cout << (a*b+1) << endl;
    cout << (a*b+1-1.0_i) << endl;
    cout << (a*b+1-1.0_i * d) << endl;
}
