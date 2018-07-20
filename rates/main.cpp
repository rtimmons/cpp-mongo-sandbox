
#include <iostream>

#include "rates.h"

using namespace std;
using namespace rr;

const unit
    mile    {"mile"},
    foot    {"foot"},
    hour    {"hour"},
    minute  {"minute"}
;

table<long> tab {{
    {{1, mile}, {5028, foot}},
    {{1, hour}, {60,   minute}}
}};


//int foo(int& p) {
//    p = 17;
//    return 0;
//}

class Foo {
int val;
public:
    explicit Foo(int v) : val{v} {}
    Foo& operator=(const Foo& other) {
        val = other.val + 1;
        return *this;
    }
    Foo& operator=(Foo&& other) {
        val = other.val * -10;
        return *this;
    }
    Foo(const Foo&other) : val{other.val * 2} {}
    Foo(Foo&&other) : val{other.val * 13} {}

    auto weak_order_lense() -> decltype(auto) { return std::tie(this->val); }

    int x() const {
        return val;
    }
    int y() {
        return -val;
    }
    Foo operator+=(const Foo& other) {
        val += other.val - 50;
        return *this;
    }
};




const Foo operator+(const Foo& a, const Foo& b) {
    Foo temp = a;
    temp += b;
    return temp;
}

void pr(const Foo& f) {
    std::cout << f.x() << std::endl;

}

template<typename T>
class Actor : public T {
public:
    template<typename...Args>
    explicit Actor(Args&&...args)
    : T{std::forward<Args>(args)...}
    {}
};

class Empty {
    std::string name_;
public:
    explicit Empty(std::string n) : name_{std::move(n)} {}
    const std::string& name() const {
        return this->name_;
    }
};
std::ostream& operator <<(std::ostream&out, const Empty& e) {
    out << "[" << e.name() << "]";
    return out;
}

template<typename T>
std::ostream& operator <<(std::ostream&out, const Actor<T>& a) {
    return operator<<(out, static_cast<T>(a));
}


int main() {
    auto e = Actor<Empty>("foo");
    std::cout << e << endl;
    return 0;
}

//int main() {
//    Foo f1{7};
//    Foo f2{100};
//    pr(f1);
//    pr(f1 + f2);
//    pr(f2 + f1);
//    pr(f2 + f1 + f2);
//
//    int x =7;
//    char c = 'c';
//    char d = 'd';
//    bool ok = false;
//
//    auto caller = calls_foo(&x, &c, &d, &ok);
//    auto out = caller();
//    std::cout << "out=[" << out << "]" << endl;
//    return 0;
//}


int omain2() {
    const int x = 10;
//    const int *xp = &x;
    // int *npx = &x; // error; x is const

//    int y = 20;
//    const int *yp = &y;
//    int * npy = &y;
//    const int * const yzc = &y;

    cout << "x=" << x;

    return 0;
}

int omain() {
    cout << "hello, world" << endl;
    cout << tab << endl;
    return 0;
}

