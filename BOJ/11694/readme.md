## [백준 11694 - 님 게임](https://www.acmicpc.net/problem/11694)

### 알고리즘
- 필승 전략 게임

### 풀이
마지막 돌을 가져가는 사람이 패배하는 님게임이다.  
oneStoneCnt := (돌이 1개짜리 더미의 개수) 라 하자.  
nim_sum()은 모든 돌더미의 개수를 xor연산한 값을 의미한다.
1. if oneStoneCnt == 0, nim_sum != 0이면 선공 필승이다.
2. if oneStoneCnt == N, nim_sum == 0이면 선공 필승이다.
3. else (나머지의 경우),
   1. 만약 oneStoneCnt가 짝수이면, 1개짜리 더미가 아닌 더미를 1개로 만들어서 oneStoneCnt를 홀수로 만든다.
   2. nim_sum != 0이면 선공 필승이다.

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

class NIM_Game {
private:
    int N;
    vector<int> stones;

    int nim_sum() {
        int ret = 0;
        for(int stone : stones)
            ret ^= stone;
        return ret;
    }
    int get_one_stone_cnt() {
        int ret = 0;
        for(int stone : stones) {
            ret += (stone == 1);
        }
        return ret;
    }
public:
    NIM_Game(vector<int> &_stones) : N(_stones.size()), stones(_stones) {}

    // true: 선공 승리, false: 후공 승리
    bool final_stone_victory() {
        return nim_sum() != 0;
    }
    // true: 선공 승리, false: 후공 승리
    bool final_stone_defeat() {
        int oneStoneCnt = get_one_stone_cnt();
        if(oneStoneCnt == 0) return nim_sum() != 0; // 돌이 1개인 더미가 없는 경우
        if(oneStoneCnt == N) return nim_sum() == 0; // 모든 돌더미가 돌이 1개인 더미인 경우
        if(oneStoneCnt%2 == 0) { // 돌이 1개인 더미가 짝수 개인 경우, 1개가 아닌 더미를 1개로 만들어서 oneStoneCnt를 홀수개로 만든다.
            for (int i = 0; i < N; i++)
                if (stones[i] != 1) { stones[i] = 1; break; }
        }
        return nim_sum() != 0;
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;
    vector<int> P; P.resize(N);
    for(int i=0; i<N; i++) cin >> P[i];
    NIM_Game nimGame(P);
    if(nimGame.final_stone_defeat()) cout << "koosaga\n";
    else cout << "cubelover\n";
    return 0;
}
```