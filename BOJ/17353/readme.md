## [백준 10999 - 구간 합 구하기 2](https://www.acmicpc.net/problem/10999)

### 풀이
- 느리게 갱신되는 세그먼트 트리

구간 변경이 있는 것으로 보았을 때 lazy segment 문제임을 알 수 있다.  
tree[node]에는 다음의 값을 저장한다.
- sum = 합
- sv = 등차수열의 시작값
- minDist = 등차수열의 공차

segment에 들어온 값들은 결국 등차수열의 합이다. 그 이유를 살펴보자.  

1. 크기가 4인 tree[node]에 다음과 같은 구간변경이 들어왔다고 가정하자.  
   [3, 4, 5, 6], [10, 11, 12, 13], [100, 101, 102, 103]   
2. 위 수열들을 다음과 같이 변경해 볼 수 있을 것이다.  
   [3, 3+1, 3+2, 3+3], [10, 10+1, 10+2, 10+3], [100, 100+1, 100+2, 100+3]
3. 이 수열들을 합쳤을 때 다음과 같다. 시작값은 3+10+100 = 113이 된다.  
   [113, 113+3, 113+6, 113+9] 

결국 들어온 수열의 갯수가 해당 등차수열의 공차가 된다.  
따라서 등차수열의 시작값과 공차만 저장해주면 우리가 원하는 합을 구할 수 있게 된다.  
나머지는 lazy segment의 구현이다.

```C++
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
#define x first
#define y second
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

struct lazy {
    ll sum, sv, minDist;
};

class segment {
public:
    vector<lazy> tree; //tree[node] := a[start ~ end] 의 합

    segment() {}
    segment(int size) {
        this->resize(size);
    }
    void resize(int size) {
        size = (int) floor(log2(size)) + 2;
        size = pow(2, size);
        tree.resize(size, {0,0,0});
    }
    ll init(vector<ll> &a, int node, int start, int end) {
        if(start == end) return tree[node].sum = a[start];
        return tree[node].sum = init(a, 2*node, start, (start+end)/2) + init(a, 2*node+1, (start+end)/2+1, end);
    }
    void update_lazy(int node, int start, int end) {
        if(tree[node].minDist == 0) return;
        tree[node].sum += tree[node].sv * (end-start+1) + tree[node].minDist * (end-start) * (end-start+1) / 2;
        if(start != end) {
            tree[2*node].sv += tree[node].sv; tree[2*node].minDist += tree[node].minDist;
            tree[2*node+1].sv += tree[node].sv + ((start+end)/2+1 - start) * tree[node].minDist; tree[2*node+1].minDist += tree[node].minDist;
        }
        tree[node].sv = tree[node].minDist = 0;
    }
    ll sum(int node, int start, int end, int idx) {
        update_lazy(node, start, end);
        if(idx < start || end < idx) return 0;
        if(start == end) return tree[node].sum;
        return sum(node * 2, start, (start + end) / 2, idx) +
               sum(node * 2 + 1, (start + end) / 2 + 1, end, idx);
    }
    void update(int node, int start, int end, int left, int right) {
        update_lazy(node, start, end);
        if(right < start || end < left) return;
        if(left <= start && end <= right) {
            tree[node].sv += max(start, left) - left + 1;
            tree[node].minDist++;
            update_lazy(node, start, end);
            return;
        }
        update(node * 2, start, (start + end) / 2, left, right);
        update(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
        tree[node].sum = tree[2*node].sum + tree[2*node+1].sum;
    }
};

int N, Q;
vector<ll> V;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    V.resize(N+1);
    for(int i=1; i<=N; i++) cin >> V[i];
    segment root(N);
    root.init(V, 1,1,N);

    cin >> Q;
    while(Q--) {
        int q; cin >> q;
        if(q == 1) {
            int l, r; cin >> l >> r;
            root.update(1,1,N,l,r);
        }
        else {
            int x; cin >> x;
            cout << root.sum(1,1,N,x) << '\n';
        }
    }



    return 0;
}
```
