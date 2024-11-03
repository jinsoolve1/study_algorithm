## [백준 14891 - 톱니바퀴](https://www.acmicpc.net/problem/14891)

### 풀이
deque를 이용해서 톱니바퀴를 구현한다.
### 주의
왼쪽과 오른쪽 톱니바퀴를 보면서 어느 톱니바퀴까지 돌려야 하는 지 확인할 떄, 톱니바퀴를 돌리지 않은 상태에서 비교해야 한다.
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

deque<int> gear[4];
int K;

void turn_clockwise(int num) {
    int back = gear[num].back();
    gear[num].pop_back();
    gear[num].emplace_front(back);
}
void turn_counterclockwise(int num) {
    int front = gear[num].front();
    gear[num].pop_front();
    gear[num].emplace_back(front);
}
void turn(int num, int dir) {
    if(dir == 1) turn_clockwise(num);
    else turn_counterclockwise(num);
}
void go(int num, int dir) {
    int r = num+1;
    while(r<4 && gear[r-1][2] != gear[r][6]) r++;
    int nextDir = dir;
    for(int i=num+1; i<r; i++) {
        turn(i,-nextDir);
        nextDir *= -1;
    }

    int l = num-1;
    while(l>=0 && gear[l][2] != gear[l+1][6]) l--;
    nextDir = dir;
    for(int i=num-1; i>l; i--) {
        turn(i, -nextDir);
        nextDir *= -1;
    }

    turn(num, dir);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for(int i=0; i<4; i++) {
        string s; cin >> s;
        for(int j=0; j<8; j++) {
            gear[i].emplace_back(s[j] - '0');
        }
    }
    cin >> K;
    while(K--) {
        int num, dir; cin >> num >> dir;
        go(num-1, dir);
    }
    int ans = 0;
    for(int i=0; i<4; i++) {
        ans += gear[i].front() * pow(2,i);
    }
    cout << ans << '\n';

    return 0;
}
```