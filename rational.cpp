#include <iostream>

constexpr int gcd(int, int);
constexpr int lcm(int, int);

class rational {
public:
    inline explicit rational(int num, int den) : numerator{abs(num)}, denominator{abs(den)} {
        if(den == 0) {
            throw zero_denominator{};
        }
    }
    class zero_denominator {};
private:
    int numerator;
    int denominator;

    rational& operator+=(const rational& other) {
        int lcm = this->lcm_of(other);
        this->numerator = this->numerator*(lcm/this->denominator) + (other.numerator*(lcm/other.denominator));
        this->denominator = lcm;
        return *this;
    }
    int lcm_of(const rational& other) {
        return lcm(this->denominator, other.denominator);
    }
    friend std::ostream& operator<<(std::ostream& out, const rational& r);
    friend rational operator+(rational a, const rational& b);
};

constexpr int lcm(const int a, const int b) {
    return a*b / gcd(a,b);
}

constexpr int gcd(int a, int b) {
    a = abs(a); b = abs(b);
    while(b!=0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

rational operator+(rational a, const rational& b) {
    a += b;
    return a;
}

std::ostream& operator<<(std::ostream& out, const rational& r) {
    out << r.numerator << "/" << r.denominator;
    return out;
}

int main() {
    const auto a = rational{1,4};
    const auto b = rational{1,3};
    const auto c = a + b;

    auto d = rational{3,11};
    auto e = rational{5,22};

    std::cout << a << "+" << b << "=" << c << "==" << (a+b) << std::endl;
    std::cout << d << "+" << e << "=" << (d+e) << std::endl;

    std::cout << (rational{3,3} + rational{1,1}) << std::endl;
}

