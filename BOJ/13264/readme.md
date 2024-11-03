## [백준 13264 - 접미사 배열 2](https://www.acmicpc.net/problem/13264)

### 알고리즘
- suffix array

### 풀이
그냥 단순하게 suffix array를 구하는 문제다.  
맨버-마이어스 알고리즘을 이용해 O(Nlog^2N)에 구하면 된다.

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

    string s; cin >> s;
    SuffixArray SA(s);
    vector<int> sa = SA.get_sa();
    for(int x : sa) cout << x << endl;


    return 0;
}
```