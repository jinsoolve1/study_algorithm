## [백준 16163 - #15164번_제보](https://www.acmicpc.net/problem/16163)

### 알고리즘
- palindrome (팰린드롬, 회문)
- manacher 알고리즘

### 풀이
문자열의 길이가 최대 2e6이므로 O(n)에 해결해야 한다.  
manacher 알고리즘을 이용해서 각 위치의 palindrome의 최대 길이의 반지름을 구한다.  
(반지름+1)를 하면 해당 위치를 중심으로 하는 팰린드롬의 개수가 나온다.  
다만, manacher 알고리즘 특성 상 중간에 #을 넣기 때문에 갯수가 2배가 된다. 따라서 2로 나눠주면 된다.

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

vector<int> manachers(string &S) {
    string s;
    for(char c : S) s += '#', s += c;
    s += '#';
    int len = s.length();
    vector<int> A(len);
    int r=0, p=0;
    for(int i=0; i<len; i++) {
        if(i<=r) A[i] = min(r-i, A[2*p-i]);
        else A[i] = 0;
        while(0 <= i-A[i]-1 && i+A[i]+1 < len && s[i-A[i]-1] == s[i+A[i]+1])
            A[i]++;
        if(r < i+A[i]) r = i+A[i], p = i;
    }
    return A;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string S; cin >> S;
    vector<int> A = manachers(S);
    ll ans = 0;
    for(int x : A) ans += (x+1)/2;
    cout << ans << endl;

    return 0;
}
```