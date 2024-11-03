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
using ti3 = tuple<int, int, int>;

int N, M;
vector<pii> edges;
vector<int> usedEdges;
unordered_map<int,int> p;
int tree_cnt;

unordered_map<int,int> visited;
vector<int> t1_node, t1_edge, t2_node, t2_edge;
int except_node = -1, except_edge = -1;

int f(int i) {
    if(i == p[i]) return i;
    return p[i] = f(p[i]);
}
bool u(int a, int b) {
    a = f(a), b = f(b);
    if(a == b) return false;
    p[b] = a;
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
    // init p
    for(int i=1; i<=N; i++) p[i]=i;

    // make tree
    tree_cnt = N;
    for(int e=0; e<M && tree_cnt > 1; e++) {
        int a = edges[e].first, b = edges[e].second;
        if(!u(a,b)) continue;
        usedEdges.emplace_back(e);
        tree_cnt--;
    }
    // tree more than 3 is impossible
    if(N<=2 || tree_cnt > 2) {
        cout << "-1\n";
        return 0;
    }

    // divide tree1 and tree2
    for(int i=1; i<=N; i++) {
        if(f(i) == f(1)) t1_node.emplace_back(i);
        else t2_node.emplace_back(i);
    }
    for(int e : usedEdges) {
        if(f(edges[e].first) == f(1)) t1_edge.emplace_back(e);
        else t2_edge.emplace_back(e);
    }

    // check if it is impossible when tree's cnt is 2
    if(tree_cnt == 2) {
        if(t1_node.size() == t2_node.size()) cout << "-1\n";
        else print();
        return 0;
    }

    // find leaves and cut it out from tree
    for(int e : usedEdges) {
        int a = edges[e].first, b = edges[e].second;
        visited[a]++; visited[b]++;
    }
    for(int e : usedEdges) {
        int a = edges[e].first, b = edges[e].second;
        if(visited[a] == 1) {
            except_node = a;
            except_edge = e;
            break;
        }
        if(visited[b] == 1) {
            except_node = b;
            except_edge = e;
            break;
        }
    }

    // cut one leaf from tree1
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