## [백준 11479 - 서로 다른 부분 문자열의 개수 2](https://www.acmicpc.net/problem/11479)

### 알고리즘
- SA와 LCP

### 풀이
1. 문자열 S의 SA와 LCP를 구한다.
2. 문자열 S의 모든 부분 문자열은 SA들의 부분 문자열의 합집합과 같다.
3. 중복되는 문자열은 LCP 배열로 해결이 가능하다.   
   (SA의 부분문자열 수) - (SA문자열의 LCP 길이) 를 해주면 중복을 제외하고 모든 부분문자열을 구할 수 있다.  
   SA문자열의 LCP길이는 이전 SA문자열과 공통되는 부분의 부분문자열의 수와 같기 때문이다.

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

class SuffixArray {
private:
    string str;
    vector<int> sa, rank, tmpRank, lcp;
    int sz;

    void make_sa() {
        sa.assign(sz, 0);
        rank.assign(sz+1, -1);
        tmpRank.assign(sz+1, -1);

        for(int i=0; i<sz; i++) sa[i] = i, rank[i] = str[i]-'a';

        for(int cmpLen=1; cmpLen<sz; cmpLen<<=1) {
            auto cmp = [&](int x, int y) {
                if(rank[x] == rank[y]) return rank[x+cmpLen] < rank[y+cmpLen];
                return rank[x] < rank[y];
            };
            sort(all(sa),cmp);

            tmpRank[sa[0]] = 0;
            for(int i=1; i<sz; i++) {
                if(cmp(sa[i-1],sa[i])) tmpRank[sa[i]] = tmpRank[sa[i-1]] + 1;
                else tmpRank[sa[i]] = tmpRank[sa[i-1]];
            }
            rank = tmpRank;
        }
    }
    void make_lcp() {
        lcp.assign(sz, 0);
        rank.assign(sz, 0);

        for(int i=0; i<sz; i++) rank[sa[i]] = i;

        int len = 0;
        for(int i=0; i<sz; i++) {
            if(rank[i] > 0) {
                int j = sa[rank[i]-1];
                while(str[i+len] == str[j+len]) len++;
                lcp[rank[i]] = len;
                if(len > 0) len--;
            }
        }
    }
    void update() { make_sa(); make_lcp(); }

public:
    SuffixArray(string &s) { this->input_string(s); }

    void input_string(string &s) {
        str = s; sz = s.size();
        update();
    }
    vector<int> get_sa() { return sa; }
    vector<int> get_lcp() { return lcp; }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string S; cin >> S;
    SuffixArray suffixArray(S);
    vector<int> sa = suffixArray.get_sa(), lcp = suffixArray.get_lcp();
    ll ans = 0;
    int sz = S.size();
    for(int i=0; i<sz; i++)
        ans += (sz - sa[i]) - lcp[i];
    cout << ans << '\n';

    return 0;
}
```

### 후기
sa와 lcp에 대한 이해가 없으면 풀 수 없는 문제다.  
문자열 문제에서 sa와 lcp의 활용도는 매우 높으니 정확한 이해와 응용이 필요하다.

### 참고
https://m.blog.naver.com/jqkt15/221795740305  
https://www.crocus.co.kr/614