## [백준 9938 - 방 청소](https://www.acmicpc.net/problem/9938)

### 알고리즘
- union-find

### 풀이
언뜻 보았을 떄는 이분매칭의 dfs처럼 보이지만 시간복잡도가 O(VE)이므로 시간초과가 난다.  
이분매칭은 재귀적으로 탐색하기 때문에 시간초과가 나고 간선이 한 노드당 2개 밖에 없다는 점을 고려했을 때, union-find를 이용하여 해결할 수 있다.  

find()를 통해 서랍에 있는 술을 몇 번 서랍으로 옮길 수 있는 지를 찾는다.  
merge()를 통해 나중에 옮길 수 있는 서랍쪽으로 union해준다.  
즉, p[x]에는 x번 서랍이 술을 옮길 수 있는 서랍번호가 최종적으로 저장이 되어 있다.

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
```