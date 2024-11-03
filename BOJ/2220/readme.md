## [백준 2220 - 힙 정렬](https://www.acmicpc.net/problem/2220)

### 알고리즘
- 자료구조
- 그리디

### 풀이
예제의 답을 거꾸로 삭제해보면 다음과 같은 결론을 얻을 수 있다.
1. n번째 수를 삭제하면 n-1번째 수의 최대 swap 형태가 되어야 한다.
2. 마지막 수가 1이어야 한다.

힙 정렬의 구성을 생각해 보면 쉽다.
1. i = 1 ~ n 의 수를 힙에 넣는다.
2. 1이 항상 마지막 수가 되도록 i번재 수를 넣으면 1과 항상 swap 해 준다.  
   이때, 1은 항상 마지막에 있었으므로 heap[i-1]과 heap[i]를 swap해주면 된다.
3. heap[i-1]이 max heap의 규칙에 따라 부모 노드와 비교하면서 root로 올린다.

다음과 같은 규칙을 따르면, 1 ~ n이 들어간 heap에서 최댓값을 제거하면 1 ~ n-1이 들어간 swap이 최대가 되는 heap이 된다. 

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

int n;
vector<int> heap;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    heap.resize(n+1);
    heap[1] = 1;
    for(int i=2; i<=n; i++) {
        heap[i] = i;
        swap(heap[i-1],heap[i]);
        for(int j=i-1; j>1; j>>=1) swap(heap[j], heap[j/2]);
    }
    for(int i=1; i<=n; i++) cout << heap[i] << ' ';
    cout << '\n';

    return 0;
}
```

### 참고
https://danidani-de.tistory.com/47