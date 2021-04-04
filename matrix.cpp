#include <bits/stdc++.h>

using namespace std;

#define tuple_arr [i] get<(i)>(tuple_arr)

template <typename T>
class DenseMatrix {
private:
    int m, n;
    vector<vector<T>> data;
public:
    DenseMatrix(int m_, int n_):m(m_),n(n_){
        assert(m);
        assert(n);
        data.resize(m, vector<T>(n));
    }
    DenseMatrix(const vector<vector<T>>& data_):data(data_){
        m = data_.size();
        assert(m);
        n = data_[0].size();
        assert(n);
    }
    DenseMatrix(const DenseMatrix& other){
        if(this != &other) {
            m = other.m;
            n = other.n;
            data.resize(m, vector<T>(n));
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j)
                    data[i][j] = other.data[i][j];
            }
        }
    }
    DenseMatrix& operator=(const DenseMatrix& other) {
        m = other.m;
        n = other.n;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j)
                data[i][j] = other.data[i][j];
        }
        return *this;
    }
    ~DenseMatrix(){}
    void set(int i, int j, T v){
        assert(i >= 0 && i < m && j >= 0 && j < n);
        data[i][j] = v;
    }
    T at(int i, int j) const {
        assert(i >= 0 && i < m && j >= 0 && j < n);
        return data[i][j];
    }
    friend ostream& operator<<(ostream& os, const DenseMatrix& denseMatrix){
        for(int i = 0; i < denseMatrix.data.size(); ++i){
            for(int j = 0; j < denseMatrix.data[0].size(); ++j)
                cout << denseMatrix.data[i][j] << " ";
            cout << endl;
        }
        return os;
    }
    DenseMatrix operator+(const DenseMatrix& other){
        assert(m == other.m);
        assert(n == other.n);
        DenseMatrix res(m, n);
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j)
                res.data[i][j] = data[i][j] + other.data[i][j];
        }
        return res;
    }
    DenseMatrix operator-(const DenseMatrix& other){
        assert(m == other.m);
        assert(n == other.n);
        DenseMatrix res(m, n);
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j)
                res.data[i][j] = data[i][j] - other.data[i][j];
        }
        return res;
    }
    DenseMatrix operator*(const DenseMatrix& other){
        assert(n == other.m);
        int k = other.n;
        assert(k);
        DenseMatrix res(m, k);
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < k; ++j){
                for(int x = 0; x < n; ++x)
                    res.data[i][j] += data[i][x] * other.data[x][j];
            }
        }
        return res;
    }
};

template <typename T>
class SparseMatrix {
private:
    int m, n;
    vector<tuple<int, int, T>> data;
public:
    SparseMatrix(int m_, int n_):m(m_),n(n_){}
    SparseMatrix(const vector<vector<T>>& data_){
        m = data_.size();
        assert(m);
        n = data_[0].size();
        assert(n);
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j)
                if(data_[i][j] != 0)
                    data.emplace_back(i, j, data_[i][j]);
        }
    }
    SparseMatrix(const SparseMatrix& other){
        if(this != &other){
            m = other.m;
            n = other.n;
            data = other.data;
        }
    }
    SparseMatrix& operator=(const SparseMatrix& other){
        m = other.m;
        n = other.n;
        data = other.data;
        return *this;
    }
    ~SparseMatrix(){}
    void set(int i, int j, T v){
        assert(i >= 0 && i < m && j >= 0 && j < n);
        for(int k = 0; k < data.size(); ++k){
            if(get<0>(data[k]) == i && get<1>(data[k]) == j){
                get<2>(data[k]) = v;
                return;
            }
        }
        data.emplace_back(i, j, v);
        sort(data.begin(), data.end(), [](tuple<int,int,T>& t1, tuple<int,int,T>& t2) -> bool {
            return get<0>(t1) == get<0>(t2) ? get<1>(t1) < get<1>(t2) : get<0>(t1) < get<0>(t2);
        });
    }
    T at(int i, int j) const {
        assert(i >= 0 && i < m && j >= 0 && j < n);
        for(int k = 0; k < data.size(); ++k){
            if(get<0>(data[k]) == i && get<1>(data[k]) == j)
                return get<2>(data[k]);
        }
        return 0;
    }
    DenseMatrix<T> toDense() const {
        DenseMatrix<T> res(m, n);
        for(auto& v : data)
            res.set(get<0>(v), get<1>(v), get<2>(v));
        return res;
    }
    friend ostream& operator<<(ostream& os, const SparseMatrix& other){
        for(int i = 0; i < other.data.size(); ++i){
            os << "(" << get<0>(other.data[i]) << ", " << get<1>(other.data[i])
                    << ", " << get<2>(other.data[i]) << ")" << endl;
        }
        return os;
    }
    SparseMatrix operator+(const SparseMatrix& other) const {
        assert(m == other.m);
        assert(n == other.n);
        SparseMatrix res(m, n);
        vector<bool> keep(other.data.size());
        for(auto& x : data){
            for(int i = 0; i < other.data.size(); ++i){
                if(!keep[i])
                    continue;
                if(get<0>(x) == get<0>(other.data) && get<1>(x) == get<1>(other.data)) {
                    res.data.emplace_back(get<2>(x) + get<2>(other.data));
                    keep[i] = false;
                } else
                    res.data.emplace_back(get<2>(x));
            }
        }
        for(int i = 0; i < other.data.size(); ++i){
            if(keep[i])
                res.data.emplace_back(other.data[i]);
        }
        sort(res.data.begin(), res.data.end(), [](tuple<int,int,T>& t1, tuple<int,int,T>& t2) -> bool {
            return get<0>(t1) == get<0>(t2) ? get<1>(t1) < get<1>(t2) : get<0>(t1) < get<0>(t2);
        });
        return res;
    }
    SparseMatrix operator*(const SparseMatrix& other) const {
        assert(n == other.m);
        int k = other.n;
        assert(k);
        SparseMatrix res(m, k);
        for(auto& x : data){
            for(auto& y : other.data){
                if(get<1>(x) == get<0>(y)){
                    int tmp = get<2>(x) * get<2>(y);
                    bool flag = true;
                    for(auto& z : res.data){
                        if(get<0>(x) == get<0>(z) && get<1>(y) == get<1>(z)) {
                            get<2>(z) += tmp;
                            flag = false;
                            break;
                        }
                    }
                    if(flag)
                        res.data.emplace_back(get<0>(x), get<1>(y), tmp);
                }
            }
        }
        sort(res.data.begin(), res.data.end(), [](tuple<int,int,T>& t1, tuple<int,int,T>& t2) -> bool {
            return get<0>(t1) == get<0>(t2) ? get<1>(t1) < get<1>(t2) : get<0>(t1) < get<0>(t2);
        });
        return res;
    }
};


int main(int argc, char* argv[]){

    DenseMatrix<int> a({
                               {1,2,3,0},
                               {2,1,0,1},
                               {1,1,1,3},
                               {2,3,1,0},
                               {2,1,0,1}
    });

    DenseMatrix<int> b({
                               {1,2,0},
                               {0,1,1},
                               {2,2,1},
                               {1,0,2}
    });

    DenseMatrix<int> c({
                               {1,1,1},
                               {2,1,0},
                               {0,1,1},
                               {0,0,1}
    });

    cout << a << endl;
    cout << b << endl;
    cout << a * (b - c) << endl;

    SparseMatrix<int> sa({
                            {0,0,0,0,1},
                            {1,0,0,2,3},
                            {0,0,0,1,0},
                            {0,1,2,0,1},
                            {0,0,0,0,0},
                            {1,0,0,0,0}
                    });

    SparseMatrix<int> sb({
                            {0,0,1,0},
                            {0,1,0,0},
                            {0,0,0,0},
                            {0,0,1,1},
                            {0,0,0,0}
                    });


    cout << sa.toDense() << endl;
    cout << sb.toDense() << endl;

    SparseMatrix sc = sa * sb;
    cout << sc.toDense() << endl;

    cout << sa.toDense() * sb.toDense() << endl;

    return 0;
}