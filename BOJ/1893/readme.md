## [백준 1893 - 시저 암호](https://www.acmicpc.net/problem/1893)

### 알고리즘
- 문자열
- kmp
- 브루트포스 알고리즘

### 풀이
1. 모든 shift에 대해서 해독한 S가 원문 W에 한 번만 존재하는지 여부를 확인해야 한다.
2. |A| <= 62 이므로 shift는 최대 62번 이루어진다.  
   이때 해독한 S가 원문 W에 한 번만 존재하는 지 확인하는 동작을 kmp 알고리즘으로 해결한다.
3. 패턴 문자열 = shift시킨 S, 기존 문자열 = W 가 되고 시간복잡도는 O(|S| + |W|) 이므로 10^5 안에 해결할 수 있다.

주의해야 할 부분은 shift시킬 때 원문W --(shift)--> 암호문S 가 되는 것이므로 decode할 때는 shift만큼 빼줘야 한다.

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
#include <climits>

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
vector<int> kmp(string s, string p){
    vector<int> ans;
    auto pi = getPi(p);
    int n = s.size(), m = p.size(), j = 0;
    for(int i=0; i<n; i++){
        while(j>0 && s[i] != p[j]) j = pi[j-1];
        if(s[i] == p[j]){
            if(j==m-1){
                ans.push_back(i-m+1);
                j = pi[j];
            }else{
                j++;
            }
        }
    }
    return ans;
}

string A, W, S;

string decode(string &s, unordered_map<char,int> &mp, int shift) {
    string ret = "";
    int sz = A.size();
    for(char c : s) ret += A[(mp[c] + sz -shift)%sz];
    return ret;
}
void print(vector<int> &ans) {
    if(ans.empty()) cout << "no solution\n";
    else if(ans.size() == 1) cout << "unique: " << ans.front() << '\n';
    else {
        cout << "ambiguous: ";
        for(int x : ans) cout << x << ' ';
        cout << '\n';
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        cin >> A >> W >> S;
        unordered_map<char,int> mp;
        for(int i=0; i<A.size(); i++) mp[A[i]] = i;
        vector<int> ans;
        for(int shift=0; shift<A.size(); shift++) {
            vector<int> res = kmp(decode(S, mp, shift), W);
            if(res.size() == 1) ans.push_back(shift);
        }
        print(ans);
    }


    return 0;
}
```