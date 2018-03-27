#include <iostream>
#include <cstring>
#include <vector>
#include <set>

using namespace std;
static int copies = 0;
static int instanceid = 0;

class Widget {
private:
    int* data;
    int id;
public:
    const size_t nelts = 10;
    Widget()
            :   id{++instanceid}
    {
        data = new int[nelts];
        cout << "constructed " << id << "\n";
    }
    ~Widget()
    {
        cout << "destructed " << id << "\n";
        delete[] data;
    }
    Widget(const Widget& other)
            :   id{++instanceid}
    {
        data = new int[nelts];
        cout << "COPY ctor " << id << "\n";
        memcpy(data, other.data, nelts * sizeof(int));
        copies++;
    }
    Widget(Widget &&other)
            :   data { other.data }
    {
        cout << "MOVE ctor" << id << "\n";
        other.data = nullptr;
    }
    Widget &operator=(const Widget &other)
    {
        if (this == &other) { return *this; }
        cout << "COPY opr " << id << " to " << other.id << "\n";
//        cout << "this=" << (this) << ", other=" << (&other)
//             << ", data=" << (&data) << ", other.data=" << (&other.data) << "\n";
        memcpy(data, other.data, nelts * sizeof(int));
        copies++;
        return *this;
    }
    Widget &operator=(Widget &&other)
    {
        if (this == &other) { return *this; }
        cout << "MOVE opr" << id << "\n";
//        cout << "this=" << (this) << ", other=" << (&other)
//             << ", data=" << (&data) << ", other.data=" << (&other.data) << "\n";
        data = other.data;
        other.data = nullptr;

        return *this;
    }

    bool operator<(const Widget &other) const {
        cout << "<\n";
        return &this->data < &other.data;
    }
};


Widget create() {
    Widget out;
    cout << out.nelts << endl;
    return out;
}

int omain() {
    const Widget w1;
    Widget w2;
    Widget w3;
//    Widget w4 = w1;
    w3 = w2;
    w2 = w3;
    w3 = Widget{};

    cout << "copy::" << endl;
    Widget w4 {w3};

    cout << "copy??" << endl;
    Widget w5 = Widget{w4};

    cout << "move??" <<endl;
    Widget w6 { create() };

    cout << "Did " << copies << " copies\n";

    cout << endl << endl;
    return 0;
}

class Foo {
private:
    int x;
public:
    explicit Foo(int x_) : x{x_} {}
    int getx() const { return x; }
    void setx(int to) { x = to;   }
};


//class Foo {
//    int x;
//    Foo() : x{7} {}
//};

class Wat {
    int *data;
public:
    static constexpr size_t nelts = 10;
    Wat() { data = new int[nelts]; }
};

class Wat2 {
    int *data;
public:
    static constexpr size_t nelts = 10;
    Wat2() : data{new int[nelts]} { }
};

void works() {
    std::vector<Wat> x(10);
}

int oomain() {
    // works:
//    std::vector<Wat> x(10);

    // std::bad_array_new_length;
    std::vector<Wat2> x2(10);
    return 0;
}


int main3333() {
    Foo x {100};
    cout << x.getx() << endl;
    x.setx(50);
    cout << x.getx() << endl;

    const Foo y {79};
//    y.setx(700);
    cout << y.getx() << endl;
    cout << y.getx() << endl;

    return 0;
}

int omain2() {

    vector<int> x {1,2,3};
    vector<int> y = move(x);
    for(const auto& i : x) {
        cout << "x" << i << ",";
    }
    for(const auto& i : y) {
        cout << "y" << i << ",";
    }
    return 0;
}

int main() {
    using namespace std;

    set<int> vs;

    int queries = 0;
    cin >> queries;
    while(queries--) {
        int typ = 0;
        int val = 0;
        cin >> typ >> val;
        if (typ == 1) {
            vs.insert(val);
        } else if (typ == 2) {
            vs.erase(val);
        } else if (typ == 3) {
            if (vs.find(val) != vs.end()) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }

    return 0;
}


//int n = 0;
//struct C {
//    explicit C(int) {}
//    C(const C&) { ++n; } // the copy constructor has a visible side effect
//};                     // it modifies an object with static storage duration
//
//int main() {
//    C c1(42); // direct-initialization, calls C::C(42)
//    C c2 = C(42); // copy-initialization, calls C::C( C(42) )
//
//    std::cout << n << std::endl; // prints 0 if the copy was elided, 1 otherwise
//    return 0;
//}


// ----------------------------------------




