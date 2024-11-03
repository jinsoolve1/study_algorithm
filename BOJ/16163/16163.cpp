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

vector<int> manachers(string &S) {
    string s;
    for(char c : S) s += '#', s += c;
    s += '#';
    int len = s.length();
    vector<int> A(len);
    int r=0, p=0;
    for(int i=0; i<len; i++) {
        if(i<=r) A[i] = min(r-i, A[2*p-i]);
        else A[i] = 0;
        while(0 <= i-A[i]-1 && i+A[i]+1 < len && s[i-A[i]-1] == s[i+A[i]+1])
            A[i]++;
        if(r < i+A[i]) r = i+A[i], p = i;
    }
    return A;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string S; cin >> S;
    vector<int> A = manachers(S);
    ll ans = 0;
    for(int x : A) ans += (x+1)/2;
    cout << ans << endl;

    return 0;
}