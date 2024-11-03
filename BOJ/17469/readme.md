## [백준 17469 - 트리의 색깔과 쿼리](https://www.acmicpc.net/problem/17469)

### 알고리즘
- union find
- 작은 집합에서 큰 집합으로 합치는 테크닉 (Small to Large Trick)

### 풀이
쿼리가 많기 떄문에 mo's algorithm을 사용해야 하는 것처럼 보이지만, 쿼리 간의 순서가 중요하기 때문에 어렵다.  
트리의 정점 분리 쿼리가 N-1개인 점과 분리보다는 합치는 것이 쉽다는 점을 보았을 때 쿼리의 순서롤 반대로 접근하는 것이 좋다는 점을 알 수 있다.  

쿼리 순서를 반대로 접근하여 점차 트리를 합치는 방식으로 한다.  
합칠 때 union-find를 이용하여 트리를 합친다.  
이떄, 까다로운 점이 색상의 개수를 체크하고 이를 합치는 점인데 이를 set 클래스로 구현한다.  
a와 b를 merge한다고 할 때, set[a]의 사이즈가 set[b]보다 항상 크도록 하여 set[b]를 탐색하면서 set[a]에 값을 insert하는 것이 효율적이다.(Small to Large Trick)  
그러면 총 N-1번 합치게 되고, 시간복잡도는 O(Nlg^2(N))이 된다. (증명은 [여기](https://ryute.tistory.com/52)를 참고하자.)

결과를 출력할 떄는 find함수를 통해 최종 그룹의 set사이즈를 출력하면 된다.

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
#define INF 987654321
#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

int N, Q;
vector<int> parent, color, p;
vector<set<int>> sets;
vector<pii> querys;
vector<int> ans;

int f(int i) {
    if(p[i] == i) return i;
    return p[i] = f(p[i]);
}
bool merge(int a, int b) {
    a = f(a), b = f(b);
    if(a == b) return false;
    if(sets[a].size() < sets[b].size()) swap(a, b);
    p[b] = a;
    for(auto x : sets[b]) sets[a].insert(x);
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> Q;
    parent = vector<int>(N+1), p = vector<int>(N+1);

    parent[1] = 1;
    for(int i=2; i<=N; i++) cin >> parent[i];
    for(int i=1; i<=N; i++) p[i] = i;

    sets = vector<set<int>>(N+1);
    color = vector<int>(N+1);
    for(int i=1; i<=N; i++) {
        cin >> color[i];
        sets[i].insert(color[i]);
    }

    Q += N-1;
    while(Q--) {
        int cmd, a; cin >> cmd >> a;
        querys.emplace_back(cmd, a);
    }
    for(auto it = querys.rbegin(); it != querys.rend(); it++) {
        if(it->first == 1) merge(it->second, parent[it->second]);
        else ans.emplace_back(sets[f(it->second)].size());
    }
    for(auto it = ans.rbegin(); it != ans.rend(); it++)
        cout << *it << endl;

    return 0;
}
```

### 참고
https://ryute.tistory.com/52