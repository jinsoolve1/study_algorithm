## [백준 2647 - 검은점과 하얀점 연결](https://www.acmicpc.net/problem/2647)

### 알고리즘
- 다이나믹 프로그래밍
- 분할정복

### 풀이
[BOJ 3012 - 올바른 괄호 문자열](https://github.com/jinsoolve/study_algorithm/tree/main/BOJ/3012)과 동일한 방식으로 풀면 된다.    
다만 dp[s][e] := (s ~ e 구간을 처리하는데 first = 최소비용, second = 가장 높은 높이) 가 저장된다.  

값 자체는 쉽게 구할 수 있으나, 연결 상태(경로)를 출력하는 부분이 까다로웠다.  
link[s][e] := s ~ e 구간에서 s와 i를 연결했을 때 최소라고 할 때, 해당 i를 저장하고 있다.  
재귀함수로 탐색하면서 경로를 저장하여 출력한다.

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

int n;
vector<int> p;
pll dp[100][100];
int link[100][100];

pll solve(int s, int e) {
    if(s>e) return {0,0};
    pll &ret = dp[s][e];
    if(ret.first != -1) return ret;
    ret.first = INF;
    for(int i=s+1; i<=e; i+=2) {
        if(p[s] + p[i] != 1) continue;
        pll left = solve(s+1,i-1), right = solve(i+1,e);
        ll dist = left.first + right.first + (i-s) + (left.second+1)*2;
        ll depth = max(left.second+1, right.second);
        if((ret.first > dist) || (ret.first == dist && ret.second > depth)) {
            link[s][e] = i;
            ret = {dist, depth};
        }
    }
    return ret;
}
void conn(int s, int e, vector<pii> &log) {
    log.emplace_back(s,link[s][e]);
    if(s+1 < link[s][e]-1) conn(s+1,link[s][e]-1,log);
    if(link[s][e]+1 < e) conn(link[s][e]+1,e,log);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fill(&dp[0][0], &dp[99][100], pll(-1, 100));
    cin >> n; p.resize(n);
    string s; cin >> s;
    for(int i=0; i<n; i++) p[i] = s[i] - '0';
    cout << solve(0,n-1).first << endl;
    vector<pii> ans;
    conn(0,n-1,ans);
    for(pii x : ans) cout << x.first+1 << ' ' << x.second+1 << endl;

    return 0;
}
```

### 참고
https://blog.encrypted.gg/334