## [백준 3830 - 교수님은 기다리지 않는다](https://www.acmicpc.net/problem/3830)

### 풀이
1. Union-Find를 이용하여 <부모 샘플, 부모 샘플과의 무게 차이> 를 저장한다.
2. Union(a,b,w): a와 b 모두 자신의 부모로까지 이동하고 이동 거리(무게차이)를 moveA, moveB에 저장한다.<br/>
   이때 a부모 - b부모의 무게 차이는 w+moveA-moveB와 같다.
3. Find(a): a의 최고 부모(조상)까지 올라가면서 부모와 무게차이 값을 갱신한다.<br/>
   이때 중요한 점은 올라가는 과정에서 만난 노드(샘플)들에 대해서도 모두 업데이트 시켜줘야 O(1)의 시간 내에 쿼리를 수행할 수 있다.<br/>
   만약 union-find를 사용했는데도 시간초과가 나왔다면 이 부분을 간과했을 확률이 높다.

```c++
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
#define Flow first
#define s second
#define x first
#define y second
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

int N, M;
vector<pii> g[101010];
pii Prev[101010]; // first: sample number, second: difference

pii Find(int here) {
    if(here == Prev[here].Flow) return Prev[here] = pii(here, 0);
    pii update = Find(Prev[here].Flow);
    return Prev[here] = pii(update.Flow, Prev[here].s + update.s);
}
void Union(int a, int b, int w) {
    Find(a);
    Find(b);
    int moveA = Prev[a].s, moveB = Prev[b].s;
    a = Prev[a].Flow, b = Prev[b].Flow;
    if(a == b) return;
    w = w + moveA - moveB;
    Prev[b] = pii(a,w);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while(cin >> N >> M) {
        if(N==0 && M==0) break;
        // init
        for(int i=1; i<=N; i++) vector<pii>().swap(g[i]);
        for(int a=1; a<=N; a++) Prev[a] = pii(a,0);

        while(M--) {
            char cmd; int a, b, w;
            cin >> cmd;
            if(cmd == '!') {
                cin >> a >> b >> w;
                Union(a,b,w);
            }
            else {
                cin >> a >> b;
                Find(a);
                Find(b);
                int moveA = Prev[a].s, moveB = Prev[b].s;
                a = Prev[a].Flow, b = Prev[b].Flow;
                if(a != b) cout << "UNKNOWN\n";
                else cout << moveB-moveA << '\n';
            }
        }
    }


    return 0;
}
```