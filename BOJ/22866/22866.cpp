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
int H[101010];
int lcnt[101010], rcnt[101010];
int ldx[101010], rdx[101010];
stack<int> st;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=1; i<=N; i++) cin >> H[i];
    for(int i=1; i<=N; i++) {
        while(!st.empty() && H[st.top()] <= H[i]) st.pop();
        lcnt[i] = st.size();
        if(!st.empty()) ldx[i] = st.top();
        else ldx[i] = -INF;
        st.emplace(i);
    }
    while(!st.empty()) st.pop();
    for(int i=N; i>=1; i--) {
        while(!st.empty() && H[st.top()] <= H[i]) st.pop();
        rcnt[i] = st.size();
        if(!st.empty()) rdx[i] = st.top();
        else rdx[i] = INF;
        st.emplace(i);
    }
    for(int i=1; i<=N; i++) {
        int cnt = lcnt[i] + rcnt[i];
        if(cnt == 0) cout << "0\n";
        else cout << cnt << ' ' << (i-ldx[i] <= rdx[i]-i ? ldx[i] : rdx[i]) << '\n';
    }

    return 0;
}