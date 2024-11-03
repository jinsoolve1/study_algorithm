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

int N, a, b;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> a >> b;

    if(a+b > N+1) cout << -1;
    else {
        if(a != 1) for(int _=0; _<N-a-b+1; _++) cout << "1 ";
        for(int i=1; i<=a-1; i++) cout << i << ' ';
        cout << max(a,b) << ' ';
        if(a == 1) for(int _=0; _<N-a-b+1; _++) cout << "1 ";
        for(int i=b-1; i>=1; i--) cout << i << ' ';
    }
    cout << '\n';


    return 0;
}
