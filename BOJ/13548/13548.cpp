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

int sqrtN;
struct Query {
    int idx, s, e;
    bool operator<(const Query &other) const {
        if(s/sqrtN == other.s/sqrtN) return e < other.e;
        return s < other.s;
    }
};

const int mxn = 1e5;
int N, M;
vector<int> A, ans;
vector<Query> qs;
int cnt[mxn+1], ccnt[mxn+1];
int now = 0;

void add(int x) {
    ccnt[cnt[A[x]]++]--;
    ccnt[cnt[A[x]]]++;
    now = max(now, cnt[A[x]]);
}
void remove(int x) {
    ccnt[cnt[A[x]]--]--;
    ccnt[cnt[A[x]]]++;
    if(ccnt[now]==0) now--;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(cnt, 0, sizeof cnt); memset(ccnt, 0, sizeof ccnt);

    cin >> N; A.resize(N+1); sqrtN = sqrt(N);
    for(int i=1; i<=N; i++) cin >> A[i];

    cin >> M; qs.resize(M); ans.resize(M);
    for(int i=0; i<M; i++) {
        qs[i].idx = i;
        cin >> qs[i].s >> qs[i].e;
    }
    sort(all(qs));
    int l = qs[0].s, r = qs[0].s;
    add(l);
    for(Query q : qs) {
        while(l < q.s) remove(l++);
        while(l > q.s) add(--l);
        while(r < q.e) add(++r);
        while(r > q.e) remove(r--);
        ans[q.idx] = now;
    }
    for(int x : ans) cout << x << endl;

    return 0;
}