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

int N;
vector<int> P;

int nim_sum_without_j(int j) {
    int ret = 0;
    for(int i=0; i<N; i++) {
        if(i == j) continue;
        ret ^= P[i];
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    P.resize(N);
    for(int i=0; i<N; i++) cin >> P[i];

    int ans = 0;
    for(int i=0; i<N; i++) {
        int tmp = P[i];
        int nimSum = nim_sum_without_j(i);
        while(P[i]--) {
            ans += ((nimSum ^ P[i]) == 0);
        }
        P[i] = tmp;
    }
    cout << ans << '\n';

    return 0;
}