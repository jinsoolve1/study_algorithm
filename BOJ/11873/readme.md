## [백준 11873 - 최대 직사각형](https://www.acmicpc.net/problem/11873)

### 알고리즘
- 스택
- 히스토그램에서 가장 큰 직사각형

### 풀이
히스토그램에서 가장 큰 직사각형 의 풀이를 그대로 이용하면 된다.

1. 행 i를 바닥이라 생각했을 떄, 해당 행에서 히스토그램의 높이를 미리 계산한다.
2. stack을 이용해서 O(M)시간 안에 해당 히스토그램에서 가장 큰 직사각형의 넓이를 구한다.

각 행마다의 히스토그램을 살펴보므로 각 테스트케이스마다 총 O(NM)시간이 걸린다. 

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

int N, M;
int ans;
int grid[1000][1000], height[1000][1000];
stack<pii> st;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while(true) {
        cin >> N >> M;
        if(N==0 && M==0) break;
        for(int i=0; i<N; i++)
            for(int j=0; j<M; j++)
                cin >> grid[i][j];
        for(int j=0; j<M; j++) {
            for(int i=0; i<N; i++) {
                if(i==0 || grid[i-1][j]==0 || grid[i][j]==0) height[i][j] = grid[i][j];
                else height[i][j] = height[i-1][j] + 1;
            }
        }
        ans = 0;
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                int idx = j;
                while(!st.empty() && st.top().second >= height[i][j]) {
                    ans = max(ans, (j-st.top().first)*st.top().second);
                    idx = st.top().first;
                    st.pop();
                }
                st.emplace(idx,height[i][j]);
            }
            while(!st.empty())  {
                ans = max(ans, (M-st.top().first)*st.top().second);
                st.pop();
            }
        }
        cout << ans << endl;
    }


    return 0;
}
```