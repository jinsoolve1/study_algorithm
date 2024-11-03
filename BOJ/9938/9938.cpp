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

const int mxn = 3e5 + 1;
int N, L;
int p[mxn];
bool used[mxn];

int find(int i) {
    if(i == p[i]) return i;
    return p[i] = find(p[i]);
}
void merge(int a, int b) {
    a = find(a), b = find(b);
    if(a != b) p[a] = b;
}
bool solve(int a, int b) {
    if(!used[a]) {
        used[a] = true;
        merge(a,b);
        return true;
    }
    if(!used[b]) {
        used[b] = true;
        merge(b,a);
        return true;
    }
    if(a == find(a) && b == find(b)) return false;
    return solve(find(a), find(b));
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(used, 0, sizeof used);

    cin >> N >> L;
    for(int i=1; i<=L; i++) p[i] = i;
    for(int i=1; i<=N; i++) {
        int a, b; cin >> a >> b;
        if(solve(a,b)) cout << "LADICA\n";
        else cout << "SMECE\n";
    }


    return 0;
}