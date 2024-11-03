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

int N;
vector<int> v(101010);
bool cnt[101010];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=1; i<=N; i++) cin >> v[i];

    ll ans = 0;
    for(int s=1, e=1; s<=N; s++) {
        while(e <= N) {
            if(cnt[v[e]]) break;
            cnt[v[e++]] = true;
        }
        ans += (e-s);
        cnt[v[s]] = false;
    }
    cout << ans << '\n';
    return 0;
}