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

int N;
int dp[1001];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, 0, sizeof dp);

    cin >> N;
    for(int x=2; x<=N; x++) {
        set<int> s;
        for(int y=0; y<=x-2; y++) s.insert(dp[y]^dp[x-2-y]);
        while(s.count(dp[x])) dp[x]++;
    }
    cout << (dp[N] ? 1 : 2) << endl;

    return 0;
}