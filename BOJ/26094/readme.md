## [백준 26094 - 더 어려운 스케줄링](https://www.acmicpc.net/problem/26094)

### 풀이
deque와 priority_queue를 이용한다.
1. reverse는 deque front, back을 사용한다.
2. sort는 deque의 모든 값을 꺼내서 priority queue에 넣는다.
3. print는 deque의 front,back을 이용하되 정렬된 값을 꺼낼 때는 min heap과, max heap을 구별해서 사용한다.

### 주의
- sort를 하고 나서는 turn을 다시 false로 바꿔주어야 한다.
- pq에 모든 값을 넣고나서 deque에 표시하기 위해 0을 넣었는데, 0을 출력하지 않기 위해서 popped[0] = true 처리를 해주자.

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
#define x first
#define y second
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

int N, Q;
deque<int> dq;
priority_queue<int, vector<int>, greater<>> pq1;
priority_queue<int, vector<int>, less<>> pq2;

bool turn = false;
bool popped[101010];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(popped, 0, sizeof popped);
    popped[0] = true;

    cin >> N >> Q;
    while(Q--) {
        int cmd, Prev;
        cin >> cmd;
        if(cmd == 0) {
            cin >> Prev;
            if(!turn) dq.emplace_front(Prev);
            else dq.emplace_back(Prev);
        }
        else if(cmd == 1) {
            while(!dq.empty()) {
                pq1.emplace(dq.front());
                pq2.emplace(dq.front());
                dq.pop_front();
            }
            dq.emplace_front(0);
            turn = false;
        }
        else if(cmd == 2) turn = !turn;
        else {
            int x;
            if(!turn) {
                x = dq.front(); dq.pop_front();
                if(x == 0) {
                    while(!pq1.empty()) {
                        x = pq1.top();
                        pq1.pop();
                        if(!popped[x]) break;
                    }
                    if(!pq1.empty()) dq.emplace_front(0);
                    if(popped[x]) { x=dq.front(); dq.pop_front(); }
                }
            }
            else {
                x = dq.back(); dq.pop_back();
                if(x == 0) {
                    while(!pq2.empty()) {
                        x = pq2.top();
                        pq2.pop();
                        if(!popped[x]) break;
                    }
                    if(!pq2.empty()) dq.emplace_back(0);
                    if(popped[x]) { x=dq.back(); dq.pop_back(); }
                }
            }
            popped[x] = true;
            cout << x << '\n';
        }
    }


    return 0;
}
```