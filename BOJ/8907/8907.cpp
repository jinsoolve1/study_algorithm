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
vector<int> blue, red;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        cin >> N;
        blue = vector<int>(N+1, 0);
        red = vector<int>(N+1, 0);
        for(int i=1; i<=N; i++) {
            for(int j=i+1; j<=N; j++) {
                int c; cin >> c;
                if(c) red[i]++, red[j]++;
                else blue[i]++, blue[j]++;
            }
        }
        ll ans = N*(N-1)*(N-2) / 6;
        ll sum = 0;
        for(int i=1; i<=N; i++) sum += red[i] * blue[i];
        cout << ans-sum/2 << endl;
    }

    return 0;
}