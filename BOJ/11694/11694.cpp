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