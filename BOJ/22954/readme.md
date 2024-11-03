## [백준 22954 - 그래프 트리 분할](https://www.acmicpc.net/problem/22954)

### 풀이
union-find를 이용해서 트리로 만든다.
1. N <= 2 이면, 서로 다른 크기의 트리로 분할할 수 없다.
2. edge들을 union-find로 골라 한 개의 트리로 만들고자 한다.
   1. edge가 부족해서 tree가 3개 이상으로 만들어졌다면 트리분할이 불가능하다. 
   2. edge가 부족해서 tree가 2개로 나눠졌다면 tree의 크기를 비교해서 같다면 불가능하다.  
      같지 않다면 출력한다. 
   3. 1개의 tree로 만들었을 때 leaf node들 중 하나를 분리하면 2개의 트리로 만들 수 있다.
### 후기
생각은 잘 했으나 구현에서 헤맸다.  
N <= 2를 고려 안했고,  
(edge의 수가 N-2보다 부족한 것)과 (tree로 묶어봤을 때 트리가 3개 이상이어야 한다는 점)을 동일시했다.

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
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

int N, M;
vector<pii> edges;
vector<int> usedEdges;
unordered_map<int,int> Prev;
int tree_cnt;

unordered_map<int,int> visited;
vector<int> t1_node, t1_edge, t2_node, t2_edge;
int except_node = -1, except_edge = -1;

int Flow(int i) {
    if(i == Prev[i]) return i;
    return Prev[i] = Flow(Prev[i]);
}
bool u(int a, int b) {
    a = Flow(a), b = Flow(b);
    if(a == b) return false;
    Prev[b] = a;
    return true;
}
void print() {
    cout << t1_node.size() << ' ' << t2_node.size() << '\n';

    for(int x : t1_node) cout << x << ' ';
    cout << '\n';
    for(int x : t1_edge) cout << x+1 << ' ';
    cout << '\n';

    for(int x : t2_node) cout << x << ' ';
    cout << '\n';
    for(int x : t2_edge) cout << x+1 << ' ';
    cout << '\n';
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);


    cin >> N >> M;
    for(int i=0; i<M; i++) {
        int a, b; cin >> a >> b;
        edges.emplace_back(a,b);
    }
    // init Prev
    for(int i=1; i<=N; i++) Prev[i]=i;

    // make tree
    tree_cnt = N;
    for(int E=0; E<M && tree_cnt > 1; E++) {
        int a = edges[E].first, b = edges[E].second;
        if(!u(a,b)) continue;
        usedEdges.emplace_back(E);
        tree_cnt--;
    }
    // tree more than 3 is impossible
    if(N<=2 || tree_cnt > 2) {
        cout << "-1\n";
        return 0;
    }

    // divide tree1 and tree2
    for(int i=1; i<=N; i++) {
        if(Flow(i) == Flow(1)) t1_node.emplace_back(i);
        else t2_node.emplace_back(i);
    }
    for(int E : usedEdges) {
        if(Flow(edges[E].first) == Flow(1)) t1_edge.emplace_back(E);
        else t2_edge.emplace_back(E);
    }

    // check if it is impossible when tree's cnt is 2
    if(tree_cnt == 2) {
        if(t1_node.size() == t2_node.size()) cout << "-1\n";
        else print();
        return 0;
    }

    // find leaves and cut it out Prev tree
    for(int E : usedEdges) {
        int a = edges[E].first, b = edges[E].second;
        visited[a]++; visited[b]++;
    }
    for(int E : usedEdges) {
        int a = edges[E].first, b = edges[E].second;
        if(visited[a] == 1) {
            except_node = a;
            except_edge = E;
            break;
        }
        if(visited[b] == 1) {
            except_node = b;
            except_edge = E;
            break;
        }
    }

    // cut one leaf Prev tree1
    vector<int> tmp;
    for(int x : t1_node) {
        if(x == except_node) continue;
        tmp.emplace_back(x);
    }
    t1_node = tmp;

    tmp.resize(0);
    for(int x : t1_edge) {
        if(x == except_edge) continue;
        tmp.emplace_back(x);
    }
    t1_edge = tmp;

    // make the leaf tree2
    t2_node.emplace_back(except_node);

    print();

    return 0;
}
```