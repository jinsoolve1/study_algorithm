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

int sqrt_N;
struct Query {
    int idx, l, r;

    bool operator<(Query other) const {
        if(l/sqrt_N == other.l/sqrt_N) return r < other.r;
        return l < other.l;
    }
};

int N, Q;
int res;
vector<int> ans, cnt;
vector<int> v, values;
vector<Query> qs;

void add(int s, int e) {
    for(int i=s; i<=e; i++) {
        if(cnt[v[i]]++ == 0) res++;
    }
}
void remove(int s, int e) {
    for(int i=s; i<=e; i++) {
        if(--cnt[v[i]] == 0) res--;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    sqrt_N = sqrt(N); v.resize(N+1);
    for(int i=1; i<=N; i++) {
        cin >> v[i];
        values.emplace_back(v[i]);
    }
    sort(all(values));
    values.erase(unique(all(values)), values.end());
    for(int i=1; i<=N; i++) {
        v[i] = lower_bound(all(values), v[i]) - values.begin();
    }
    cnt.resize(values.size());
    cin >> Q;
    ans.resize(Q);
    for(int i=0; i<Q; i++) {
        int l, r; cin >> l >> r;
        qs.emplace_back(Query{i,l,r});
    }
    sort(all(qs));
    int l = qs[0].l, r = qs[0].l;
    cnt[v[l]]++; res = 1;
    for(Query q : qs) {
        if(q.l < l) add(q.l, l-1);
        if(l < q.l) remove(l, q.l-1);
        if(q.r < r) remove(q.r+1, r);
        if(r < q.r) add(r+1, q.r);
        l = q.l, r = q.r;
        ans[q.idx] = res;
    }
    for(int x : ans) cout << x << '\n';

    return 0;
}