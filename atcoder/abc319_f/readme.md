## [atcoder abc319-f Fighter Takahashi](https://atcoder.jp/contests/abc319/tasks/abc319_f)

### 알고리즘
- 시뮬레이션, 구현
- 비트마스크
- dp
- 그리디

### 풀이
풀이는 간단하나 구현이 생각하기 어려웠다.

1. 이길 수 있는 모든 적을 이긴다.
2. 먹을 수 있는 약 중 하나를 선택해서 먹는다. 
3. 1~2를 끝날 때까지 반복한다.

여기서 문제는 2번인데, 어떤 약을 먼저 먹는냐에 따라 최대힘이 달라진다. 이를 모든 약의 순서에 따라서 다해버리면 아무리 10! 곱해지지만 TLE가 날 가능성이 매우 높다.  
힌트는 약의 갯수가 10개밖에 안 된다는 점을 참고해서 비트마스킹을 떠올릴 수 있다.

`dp[medicine_mask] := medicine_mask에 마스킹되어 있는 약을 먹은 상황에서의 최대 힘`  
위 개념을 이용해서 정답을 찾아볼 수 있다.

하지만 문제가 있다. 각 약을 먹은 상황에 대해서 1)먹을 수 있는 약의 종류와 2)이겨야 할 적들의 종류를 알아야 한다. 따라서 이를 각 약의 mask에 따라 저장해 놔야 한다.  
필자는 여기서 구현이 막혔다.

해결 방법은 struct를 새로 구현해서 이를 이용한 array를 만들어 버리는 거다.
```c++
struct State {
    ll strength = 0; // 힘
    int conquer = 0; // 현재까지 정복한 정점 수
    priority_queue<int, vector<int>, cmp> enemies; // 앞으로 이겨야 할 적의 목록
    set<int> medicines; // 먹을 수 있는 약의 목록

    bool check() const {
        return (conquer + medicines.size() == N);
    }
} A[1<<10];
```
위 같이 구현하면 각 medicine_mask 상황에 따라서 정보를 담고 있을 수 있다.

각 A[nstate]의 업데이트는 다음과 같이 하면 된다.
```c++
if(A[state].strength * g[medicine] > A[nstate].strength) {
    A[nstate] = A[state];
    A[nstate].strength *= g[medicine];
    A[nstate].medicines.erase(medicine);
}
```
A[nstate]에 대해서 기존에 저장되어 있던 힘보다 새롭게 만들어 온 힘이 더 클 경우 업데이트 해주면 된다.  
업데이트하고 나서 먹을 수 있는 약과 이겨야할 적 리스트 또한 업데이트 해주며 된다.

이런 식으로 1~2를 반복할 수 있다.

그리고 strength가 $10^9$을 넘거나, conquer한 수(먹기 전인 약들 포함)가 N이 되면 "Yes"이고, 불가능하면 "No"를 반환하면 정답이다.  

### 코드
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
#include <set>
#include <unordered_set>
#include <climits>

#define endl "\n"

#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

const int MAX_N = 501, INF = 1e9;
int N;
vector<int> adj[MAX_N];
vector<int> t(MAX_N), s(MAX_N), g(MAX_N);

int medicine_cnt = 0;
vector<int> medicine_idx(MAX_N);

enum {Enemy=1, Medicine};

struct cmp {
    bool operator()(int a, int b) {
        return s[a] > s[b];
    }
};

struct State {
    ll strength = 0;
    int conquer = 0;
    priority_queue<int, vector<int>, cmp> enemies;
    set<int> medicines;

    bool check() const {
        return (conquer + medicines.size() == N);
    }
} A[1<<10];

void move(State &a, int here) {
    a.conquer++;
    for(int &there : adj[here]) {
        if(t[there] == Enemy) a.enemies.emplace(there);
        else a.medicines.insert(there);
    }
}
void work(State &a) {
    auto &[strength, conquer, enemies, medicines] = a;
    while(!enemies.empty()) {
        int enemy = enemies.top();
        if(strength < s[enemy]) break;
        enemies.pop();
        strength += g[enemy];
        move(a,enemy);
    }
}

bool solve() {
    // init
    A[0].strength = 1; A[0].enemies.emplace(1);

    for(int state=0; state<(1<<medicine_cnt); state++) {
        work(A[state]);
        if(A[state].strength >= INF || A[state].check()) return true;
        // take one of medicines and update max strength
        for(int medicine : A[state].medicines) {
            int nstate = state | (1<<medicine_idx[medicine]);
            if(A[state].strength * g[medicine] <= A[nstate].strength) continue;
            A[nstate] = A[state];
            A[nstate].strength *= g[medicine];
            A[nstate].medicines.erase(medicine);
            move(A[nstate], medicine);
        }
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=2; i<=N; i++) {
        int p; cin >> p >> t[i] >> s[i] >> g[i];
        adj[p].emplace_back(i);
        if(t[i] == 2) medicine_idx[i] = medicine_cnt++;
    }

    cout << (solve() ? "Yes" : "No") << endl;

    return 0;
}
```