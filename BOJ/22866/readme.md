## [백준 22866 - 탑 보기](https://www.acmicpc.net/problem/22866)

### 풀이
stack을 이용하여 푸는 문제다.  
현재 건물에서 왼쪽에 보이는 건물의 수를 먼저 구해보자.  

1. stack에는 내림차순(top이 가장 작도록) 계산한다.
2. stack.top() > H[i] 이면 i번째 건물에서는 stack에 있는 모든 건물이 다 보인다.  
   즉, stack의 size가 i번째 건물이 왼쪽을 바라봤을 때 보이는 건물의 수가 된다.
3. stack.top() <= H[i]이면 stack.top() > H[i]가 될 때가지 stack을 지운다.(혹은 stack이 empty가 될 때까지)  
   어차피 i번째 건물이 추가되면 stack에 있던 H[i]보다 작은 건물들은 안 보일 것이기 때문이다.  
   다 지우고 나면 2번 과정처럼 왼쪽에 보이는 건물의 수를 구한다.

오른쪽은 반대로 N -> 1 건물로 이동하면서 stack에 같은 메커니즘으로 개수를 구한다.

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

int N;
int H[101010];
int lcnt[101010], rcnt[101010];
int ldx[101010], rdx[101010];
stack<int> st;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=1; i<=N; i++) cin >> H[i];
    for(int i=1; i<=N; i++) {
        while(!st.empty() && H[st.top()] <= H[i]) st.pop();
        lcnt[i] = st.size();
        if(!st.empty()) ldx[i] = st.top();
        else ldx[i] = -INF;
        st.emplace(i);
    }
    while(!st.empty()) st.pop();
    for(int i=N; i>=1; i--) {
        while(!st.empty() && H[st.top()] <= H[i]) st.pop();
        rcnt[i] = st.size();
        if(!st.empty()) rdx[i] = st.top();
        else rdx[i] = INF;
        st.emplace(i);
    }
    for(int i=1; i<=N; i++) {
        int cnt = lcnt[i] + rcnt[i];
        if(cnt == 0) cout << "0\n";
        else cout << cnt << ' ' << (i-ldx[i] <= rdx[i]-i ? ldx[i] : rdx[i]) << '\n';
    }

    return 0;
}
```