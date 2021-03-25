#include <bits/stdc++.h>

using namespace std;

class ob {
public:
    int x{};
    ob(){}
    ~ob(){
        cout << "~ob()" << endl;
    }
};

int main(int argc, char *argv[]){


    const int m = 4;
    const int n = 5;
    ob **p = new ob*[m];
    for(int i = 0; i < m; ++i){
        p[i] = new ob[n];
        for(int j = 0; j < n; ++j)
            (p[i] + j)->x = i * n + j;
    }

    for(int i = 0; i < m; ++i){
        ob *q = p[i];
        for(int j = 0; j < n; ++j)
            cout << q[j].x << " ";
        cout << endl;
    }

    for(int i = 0; i < m; ++i){
        delete [] p[i];
    }
    delete [] p;

    int arr[m][n];
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j)
            arr[i][j] = i * n + j;
    }
    int (*pa)[n] = arr;
    cout << sizeof(pa) << endl;
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            cout << *(*(pa + i) + j) << " ";
        }
        cout << endl;
    }
}