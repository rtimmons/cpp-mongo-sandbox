

#include <iostream>
#include <utility>
#include <vector>
#include <cassert>

using namespace std;

ostream& operator<<(ostream& out, const vector<int>&r) {
    for(const auto& v : r) { out << v << " "; }
    return out;
}

template<unsigned long R, unsigned long C>
class Matrix {
    vector<vector<int>> rows;
public:
    explicit Matrix(const vector<int>& cells)
    : rows{ vector<vector<int>>{} }
    {
        assert(cells.size() == R * C);
        for(unsigned long row = 0; row < R; ++row) {
            auto start = cells.begin() + ((row+0) * R);
            auto end   = cells.begin() + ((row+1) * R);
            this->rows.push_back(move(vector<int>{start, end}));
        }
    }
    explicit Matrix(vector<vector<int>> cells)
    : rows{std::move(cells)} {}

    ~Matrix() = default;

    Matrix(const Matrix& other) {
        cout << "copy ctr" << endl;
        this->rows = other.rows;
    }
    Matrix& operator=(const Matrix &other) {
        cout << "copy opr" << endl;
        this->rows = other.rows;
        return *this;
    }
    Matrix& operator=(Matrix &&other) noexcept {
        cout << "move opr" << endl;
        this->rows = move(other.rows);
        return *this;
    }
    Matrix(Matrix&&other) noexcept {
        cout << "move ctr" << endl;
        this->rows = move(other.rows);
    }

    const vector<int>& operator[](int row) const {
        return rows[row];
    }

    const Matrix operator+(const Matrix &rhs) const {
        vector<vector<int>> rows{};
        for (unsigned long row = 0; row < R; ++row) {
            vector<int> nRow{};
            for (unsigned long col = 0; col < C; ++col) {
                int sum = this->rows[row][col] + rhs[row][col];
                nRow.push_back(sum);
            };
            rows.push_back(move(nRow));
        }
        return Matrix{rows};
    }
};


template<unsigned long R, unsigned long C>
ostream& operator<<(ostream& out, const Matrix<R,C>& m) {
    cout << "[";
    for(unsigned long row = 0; row < R; ++row) {
        cout << "[";
        cout << m[row];
        cout << "]";
    }
    cout << "]";
    return out;
};

int main() {
    const Matrix<2,2> a{vector<int>{
            1, 2,
            3, 4
    }};
    const Matrix<2,2> b{vector<int>{
            1, 2,
            3, 4
    }};
    cout << a << endl;
    cout << b << endl;
    Matrix<2,2> c = a + b + a + b;
    Matrix<2,2> d = c;
    cout << c << endl;
}
