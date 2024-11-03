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
vector<int> current, target;
int dp[100][10][10][10];


vector<int> get_stovi() {
    string s; cin >> s;
    vector<int> ret;
    for(char c : s) ret.emplace_back(c-'0');
    return ret;
}
int rotate(int x, int mv) { return (x + mv + 10) % 10; }
int solve(int idx, int n1, int n2, int n3) {
    if(idx == N) return 0;

    int &ret = dp[idx][n1][n2][n3];
    if(ret != -1) return ret;

    ret = INF;
    if(n1 == target[idx]) ret = min(ret, solve(idx+1, n2, n3, current[idx+3]));
    for(int i=-3; i<=3; i++)
        if(i) ret = min(ret, solve(idx, rotate(n1,i), n2, n3) + 1);
    for(int i=-3; i<=3; i++)
        if(i) ret = min(ret, solve(idx, rotate(n1,i), rotate(n2,i), n3) + 1);
    for(int i=-3; i<=3; i++)
        if(i) ret = min(ret, solve(idx, rotate(n1,i), rotate(n2,i), rotate(n3,i)) + 1);

    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(dp, -1, sizeof dp);

    cin >> N;
    current = get_stovi(); current.emplace_back(0); current.emplace_back(0); current.emplace_back(0);
    target = get_stovi();

    cout << solve(0, current[0], current[1], current[2]);

    return 0;
}