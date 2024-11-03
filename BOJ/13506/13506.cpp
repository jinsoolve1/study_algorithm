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
#include <set>
#include <unordered_set>
#include <climits>

#define endl "\n"
#define INF 987654321
#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

vector<int> getPi(string p){
    int m = (int)p.size(), j=0;
    vector<int> pi(m, 0);
    for(int i=1; i<m; i++){
        while(j > 0 && p[i] !=  p[j])
            j = pi[j-1];
        if(p[i] == p[j])
            pi[i] = ++j;
    }
    return pi;
}
string solve(string S) {
    vector<int> pi = getPi(S);
    int x = pi[S.length()-1];
    while(x) {
        for(int i=1; i<S.length()-1; i++) {
            if(pi[i] == x) return S.substr(0,x);
        }
        x = pi[x-1];
    }
    return "-1";
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string S; cin >> S;
    cout << solve(S) << endl;

    return 0;
}