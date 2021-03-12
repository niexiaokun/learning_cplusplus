#include <bits/stdc++.h>

using namespace std;


class Mat {
public:
    int *data;
    int rows, cols;
    int *count;
public:
    Mat() : rows(0), cols(0), data(nullptr) {
        this->count = new int(0);
    }

    Mat(int m, int n) : rows(m), cols(n) {
        data = new int[m * n];
        for (int i = 0; i < m * n; ++i)
            data[i] = 0;
        count = new int(1);
    }

    Mat(const vector<vector<int>> &v) {
        rows = v.size();
        if (rows == 0)
            cols = 0;
        else
            cols = v[0].size();
        data = new int[rows * cols];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j)
                data[i * cols + j] = v[i][j];
        }
        count = new int(1);
    }

    int at(int i, int j) const {
        return data[i * cols + j];
    }

    Mat(const Mat &other) {
        if (this != &other) {
            this->data = other.data;
            this->count = other.count;
            ++(*this->count);
        }
    }

    Mat &operator=(const Mat &other) {
        if (this == &other)
            return *this;
        if (this->data) {
            --(*this->count);
            if (*this->count == 0) {
                delete this->data;
                delete this->count;
            }
        }
        this->data = other.data;
        this->count = other.count;
        ++(*this->count);
        return *this;
    }

    ~Mat() {
        cout << "~Mat() " << *this->count << endl;
        if (*this->count)
            --(*this->count);
        if (*this->count == 0)
            delete[] data;
    }

    friend ostream&operator<<(ostream& os, const Mat& mat){
        os << "[" << endl;
        for(int i = 0; i < mat.rows; ++i){
            for(int j = 0; j < mat.cols; ++j){
                os << mat.data[i * mat.cols + j] << " ";
            }
            os << endl;
        }
        os << "]" << endl;
        return os;
    }
};


int main(int argc, char* argv[]) {

    vector<vector<int>> v = {{1,  2,  3,  4},
                             {5,  6,  7,  8},
                             {9,  10, 11, 12},
                             {13, 14, 15, 16}};
    Mat a(v);
    Mat b(4, 5);
    Mat c = a;
    c = b;

    cout << a.data << endl;
    cout << b.data << endl;
    cout << c.data << endl;

    cout << a ;

    cout << a.at(2, 3) << endl;

    return 0;
}