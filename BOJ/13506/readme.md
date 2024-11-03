## [백준 13506 - 카멜레온 부분 문자열](https://www.acmicpc.net/problem/13506)

### 알고리즘
- kmp
- 문자열

### 풀이
kmp알고리즘의 pi배열을 이용하는 것이 핵심이다.  
카멜레온 부분문자열은 전치사와 접두사가 같으면서 해당 부분문자열이 중간에 등장하는 지를 확인하면 된다.  
전치사와 접두사는 x = pi[S.length()-1]로 확인하고 해당 부분문자열이 없다면, x = pi[x]로 점점 줄여가면 된다.  
부분문자열이 등장하는지 확인하는 것은 10^6이고, x = pi[x]로 점차 줄어들기 때문에 상수시간에 가깝기 때문에 통과할 수 있다.

```c++
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
```