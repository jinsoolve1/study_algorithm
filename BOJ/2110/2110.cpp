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

int N, C;
vector<int> v;

bool check(int len) {
    auto it = v.begin();
    int cnt = 0;
    while(it != v.end()) {
        it = lower_bound(it+1,v.end(),*it+len);
        if(++cnt >= C) return true;
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> C;
    for(int i=0; i<N; i++) {
        int x; cin >> x;
        v.emplace_back(x);
    }
    sort(all(v));
    int l=0, r=1e9;
    while(l<=r) {
        int m = (l+r)/2;
        if(check(m)) l=m+1;
        else r=m-1;
    }
    cout << r << '\n';

    return 0;
}