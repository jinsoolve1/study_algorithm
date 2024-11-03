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

int N, M, K;
double dN, dM, dK;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> K;
    dN = N; dM = M; dK = K;
    if(!(ceil(dN/dK) <= dM && dM <= dN-dK+1)) cout << "-1\n";
    else {
        int low = 0;
        for(int i=K; i>low; i--) cout << i << ' ';
        if(M > 1) {
            low = K;
            int cnt = (N-K)/(M-1);
            int j=1;
            for(; j<=(N-K)%(M-1); j++) {
                for(int i=low+cnt+1; i>low; i--) cout << i << ' ';
                low += cnt+1;
            }
            for(;j <= M-1; j++) {
                for(int i=low+cnt; i>low; i--) cout << i << ' ';
                low += cnt;
            }
        }
        cout << '\n';
    }



    return 0;
}