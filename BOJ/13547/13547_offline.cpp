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
#define f first
#define s second
#define x first
#define y second
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

int sqrt_N;
struct Query {
    int idx, s, e;

    bool operator < (Query other) const {
        if(s/sqrt_N == other.s/sqrt_N) return e < other.e;
        return s < other.s;
    }
};

int N, M;
vector<int> A;
vector<Query> qs;
int cnt[1010101];
int now = 0;
vector<int> ans;

void add(int s, int e) {
    for(int i=s; i<=e; i++) {
        if(cnt[A[i]]++ == 0) now++;
    }
}
void remove(int s, int e) {
    for(int i=s; i<=e; i++) {
        if(--cnt[A[i]] == 0) now--;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    A.resize(N+1);
    sqrt_N = sqrt(N);
    for(int i=1; i<=N; i++) cin >> A[i];

    cin >> M;
    ans.resize(M);
    for(int i=0; i<M; i++) {
        int s, e; cin >> s >> e;
        qs.push_back({i,s,e});
    }

    sort(all(qs));
    int ldx = qs[0].s, rdx = qs[0].s;
    add(ldx,rdx);
    for(Query q : qs) {
        if(q.s < ldx) add(q.s, ldx-1);
        if(ldx < q.s) remove(ldx, q.s-1);
        if(q.e < rdx) remove(q.e+1, rdx);
        if(rdx < q.e) add(rdx+1, q.e);
        ldx = q.s; rdx = q.e;
        ans[q.idx] = now;
    }
    for(int x : ans) cout << x << '\n';

    return 0;
}