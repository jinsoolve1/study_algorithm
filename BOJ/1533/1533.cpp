#include <iostream>
#include <algorithm>
#include <cmath>
#include <utility>
#include <string>
#include <cstring>
#include <vector>
#include <tuple>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <unordered_map>
#include <climits>

#define INF 987654321
#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

const int mod = 1e6 + 3;

class Matrix {
public:
    int r, c;
    ll **item;

    Matrix(int r, int c) {
        this->r = r;
        this->c = c;
        item = new ll *[r];
        for (int i = 0; i < r; i++) {
            item[i] = new ll[c];
            for (int j = 0; j < c; j++) {
                item[i][j] = 0;
            }
        }
    }
    ~Matrix() {
        delete[]item;
    }

    void iden() {
        if(r != c) exit(-1);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if(i==j) item[i][j] = 1;
                else item[i][j] = 0;
            }
        }
    }
    Matrix& operator =(const Matrix& cp) {
        if(!(r == cp.r && c == cp.c)) exit(-1);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                item[i][j] = cp.item[i][j];
            }
        }
        return *this;
    }
    Matrix operator *(const Matrix& cp) const {
        if(c != cp.r) exit(-1);
        Matrix mat(r, cp.c);
        for (int i = 0; i < mat.r; i++) {
            for (int j = 0; j < mat.c; j++) {
                for (int k = 0; k < c; k++) {
                    mat.item[i][j] = (mat.item[i][j] + item[i][k] * cp.item[k][j]) % mod;
                }
            }
        }
        return mat;
    }
    Matrix& operator *=(const Matrix &cp) {
        if(c != cp.r) exit(-1);
        (*this) = (*this) * cp;
        return *this;
    }
    void exp(ll times) {
        Matrix a(r, c);
        a = *this;
        (*this).iden();

        while(times) {
            if(times%2) *this *= a;
            a *= a;
            times /= 2;
        }
    }
    void print() {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << item[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, S, E, T; cin >> N >> S >> E >> T; S--; E--;
    Matrix adj(5*N, 5*N);
    for(int i=0; i<5*N; i++) {
        if(i%5 == 4) continue;
        adj.item[i][i+1] = 1;
    }
    for(int u=0; u<N; u++) {
        string s; cin >> s;
        for(int v=0; v<N; v++) {
            int val = s[v] - '0';
            if(val == 0) continue;
            adj.item[5*u+4][5*v+5-val] = 1;
        }
    }
    adj.exp(T);
    cout << adj.item[5*S+4][5*E+4] << '\n';

    return 0;
}