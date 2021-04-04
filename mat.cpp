#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Mat {
public:
    T *data;
    int rows, cols;
    int *count;
public:
    Mat() : rows(0), cols(0), data(nullptr) {
        this->count = new int(0);
    }

    Mat(int m, int n) : rows(m), cols(n) {
        data = new T[m * n];
        for (int i = 0; i < m * n; ++i)
            data[i] = 0;
        count = new int(1);
    }

    Mat(const vector<vector<T>> &v) {
        rows = v.size();
        assert(rows);
        cols = v[0].size();
        for(int i = 1; i < rows; ++i)
            assert(v[i].size() == cols);
        data = new T[rows * cols];
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

    Mat operator*(const Mat &other){
        assert(cols == other.rows);
        int m = rows, n = cols, k = other.cols;
        Mat<T> res(m, k);
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < k; ++j){
                for(int x = 0; x < n; ++x)
                    res.data[i*k+j] += data[i*n+x] * other.data[x*k+j];
            }
        }
        return res;
    }

    Mat operator+(const Mat &other){
        assert(rows == other.rows && cols == other.cols);
        Mat res(rows, cols);
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < cols; ++j){
                res.data[i*cols+j] = data[i*cols+j] + other.data[i*cols+j];
            }
        }
        return res;
    }

    Mat operator-(const Mat &other){
        assert(rows == other.rows && cols == other.cols);
        Mat res(rows, cols);
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < cols; ++j)
                res.data[i*cols+j] = data[i*cols+j] - other.data[i+cols+j];
        }
        return res;
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
        if (*this->count == 0 && data)
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

    vector<vector<double>> v = {{1,  2,  3,  4},
                             {5,  6,  7,  8},
                             {9,  10, 11, 12},
                             {13, 14, 15, 16}};
    Mat a(v);
    Mat<double> b(4, 5);
    Mat c = a;
    c = b;

    cout << a.data << endl;
    cout << b.data << endl;
    cout << c.data << endl;

    cout << a ;

    cout << a.at(2, 3) << endl;

    Mat d = a * a;
    cout << d;

    d = a + a;
    cout << d;

    cout << a + a << endl;

    return 0;
}