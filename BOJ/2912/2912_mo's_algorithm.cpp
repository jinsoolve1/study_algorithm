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
#define x first
#define y second
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

int sqrt_N;
struct Query {
    int idx, s, e;

    bool operator< (Query other) const {
        if(s/sqrt_N == other.s/sqrt_N) return e < other.e;
        return s < other.s;
    }
};

const int color_mxn = 1e4;
int N, C, M;
vector<int> v, ans;
vector<Query> querys;
int cnt[color_mxn+1];

void add(int s, int e) {
    for(int i=s; i<=e; i++) cnt[v[i]]++;
}
void remove(int s, int e) {
    for(int i=s; i<=e; i++) cnt[v[i]]--;
}
int check(int M) {
    for(int c=1; c<=C; c++) {
        if(cnt[c] > M) return c;
    }
    return -1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(cnt, 0, sizeof cnt);

    cin >> N >> C;
    v.resize(N+1); sqrt_N = sqrt(N);
    for(int i=1; i<=N; i++) cin >> v[i];

    cin >> M;
    querys.resize(M); ans.resize(M);
    for(int i=0; i<M; i++) {
        querys[i].idx = i;
        cin >> querys[i].s >> querys[i].e;
    }
    sort(all(querys));

    int l = querys[0].s, r = querys[0].s;
    cnt[v[l]]++;
    for(Query query : querys) {
        if(l < query.s) remove(l, query.s-1);
        if(query.s < l) add(query.s, l-1);
        if(r < query.e) add(r+1, query.e);
        if(query.e < r) remove(query.e+1, r);
        l = query.s, r = query.e;

        ans[query.idx] = check((query.e-query.s+1)/2);
    }
    for(int x : ans) {
        if(x != -1) cout << "yes " << x << '\n';
        else cout << "no\n";
    }


    return 0;
}