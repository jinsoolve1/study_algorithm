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
vector<int> target, dp, psum;
int t, h;

void resize() {
    target.resize(N+1);
    dp.resize(N+1); fill(all(dp), 0);
    psum.resize(N+1); fill(all(psum), 0);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    resize();
    for(int i=1; i<=N; i++) cin >> target[i];
    sort(all(target));
    for(int i=1; i<=N; i++) psum[i] = psum[i-1] + target[i];
    cin >> t >> h;

    for(int i=1; i<=N; i++) {
        dp[i] = dp[i-1] + target[i]*t;
        // j ~ i
        for(int j=i; j>=1; j--) {
            int m = (i+j)/2;
            int cost = 0;
            cost += (m-j)*target[m] - (psum[m-1]-psum[j-1]); // j ~ m-1
            cost += (psum[i]-psum[m]) - (i-m)*target[m]; //m+1 ~ i
            cost = t*cost + h;
            dp[i] = min(dp[i], dp[j-1] + cost);
        }
    }
    cout << dp[N] << '\n';

    return 0;
}