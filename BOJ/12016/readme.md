## [백준 12016 - 라운드 로빈 스케줄러](https://www.acmicpc.net/problem/12016)

### 알고리즘
- 세그먼트 트리
- 정렬, 오프라인 쿼리

### 풀이
i번째 작업을 마무리하는데 필요한 작업시간을 t라 하자.  
ans[i] = (1 ~ i 작업 중 미완료된 작업 개수) x t + (i+1 ~ N 작업 중 미완료된 작업 개수) x (t-1) + (완료된 작업들의 작업시간의 합) 이 된다.  

(완료된 작업들의 작업시간의 합) 을 더하는 이유는 미완료된 작업들만 고려했기 때문에 완료된 작업들에 대해서도 해당 작업시간만큼 일을 했어야 완료 했을 것이다.    
따라서 해당 시간들을 더해줘야 한다.

각 작업 별 필요한 작업시간이 오름차순이 되도록 정렬한 후에 해야 (완료된 작업들의 작업시간의 합)을 더하는 것이 이치에 맞으므로 정렬을 해줘야 한다.

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

class segment {
public:
    vector<ll> tree; //tree[node] := a[start ~ end] 의 합

    segment() {}
    segment(int size) {
        this->resize(size);
    }
    void resize(int size) {
        size = (int) floor(log2(size)) + 2;
        size = pow(2, size);
        tree.resize(size);
    }
    ll init(int node, int start, int end) {
        if(start == end) return tree[node] = 1;
        else return tree[node] = init(2 * node, start, (start + end) / 2) +
                                 init(2 * node + 1, (start + end) / 2 + 1, end);
    }
    ll sum(int node, int start, int end, int left, int right) {
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return tree[node];
        return sum(node * 2, start, (start + end) / 2, left, right) +
               sum(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
    }
    void update(int node, int start, int end, int index, ll diff) {
        if(index < start || end < index) return;
        tree[node] += diff;
        if(start != end) {
            update(node * 2, start, (start + end) / 2, index, diff);
            update(node * 2 + 1, (start + end) / 2 + 1, end, index, diff);
        }
    }
};

int N;
vector<ll> a, ans;
vector<pll> qs;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    a = vector<ll>(N+1); ans = vector<ll>(N+1);
    for(int i=1; i<=N; i++) {
        cin >> a[i];
        qs.emplace_back(a[i],i);
    }

    segment root(N);
    root.init(1,1,N);

    sort(all(qs));
    ll tm = 0;
    for(pll q : qs) {
        ans[q.second] = root.sum(1,1,N,1,q.second) * q.first + root.sum(1,1,N,q.second+1,N) * (q.first-1) + tm;
        tm += q.first;
        root.update(1,1,N,q.second,-1);
    }
    for(int i=1; i<=N; i++) cout << ans[i] << endl;

    return 0;
}
```

### 참고
https://jason9319.tistory.com/46