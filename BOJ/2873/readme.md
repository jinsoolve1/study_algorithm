## [백준 2837 - 롤러코스터](https://www.acmicpc.net/problem/2873)

### 풀이
(참고: https://www.slideshare.net/Baekjoon/baekjoon-online-judge-2873)
1. 체스판을 흰, 검 칸을 그린다.(출발지점과 도착지점은 흰칸이다.)
2. 방문할 때 [흰 -> 검 -> 흰 -> 검 -> ... -> 흰] 이렇게만 방문할 수 있다. <br/>
   즉, 흰칸은 검은칸보다 하나 더 많아야 한다. 따라서 전체 칸의 수는 홀수여야 전부 방문할 수 있다.
3. R,C 중 최소 하나가 홀수라면 전부 다 방문할 수 있다.
4. R,C가 모두 짝수라면 검은칸 하나만 제외하면 모든 칸을 방문할 수 있다. 검은 칸들 중 값이 가장 작은 값을 찾아 제거한다.
5. 나머지는 방문 기록은 구현인데 최백준님의 슬라이드를 보면 이해하기 쉽다.

~~구현이 조금 더럽지만 그래도 제 기능을 한다.~~

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

int R, C;
int grid[1010][1010];
pii minIdx;
int minVal = INF;

int dx[] = {1,0,-1,0};
int dy_R[] = {0,1,0,1}, dy_L[] = {0,-1,0,-1};
char moveR[4] = {'D','R','U','R'}, moveL[4] = {'D', 'Building', 'U', 'Building'};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> R >> C;
    for(int i=1;i<=R;i++) {
        for(int j=1;j<=C;j++) {
            cin >> grid[i][j];
            if((i+j)%2 == 1 && minVal > grid[i][j]) {
                minVal = grid[i][j];
                minIdx = pii(i,j);
            }
        }
    }
    if(R%2 || C%2) {
        int i=1, j=1;
        while(i != R || j != C) {
            if(i == R-1 && j == 1) {
                int goalI = i+1, goalJ = C, minDist = 0;
                while(i != goalI || j != goalJ) {
                    int ni = i + dx[minDist], nj = j + dy_R[minDist];
                    i = ni, j = nj;
                    cout << moveR[minDist];
                    minDist = (minDist+1) % 4;
                }
            }
            else {
                if(j==1) {
                    for(;j<C; j++) cout << "R";
                }
                else {
                    for(; j>1; j--) cout << "Building";
                }
                if(i != R) {
                    cout << "D";
                    i++;
                }
            }
        }


    }
    else {
        for(int i=1, j=1; i != R || j != C;) {
            if(i == minIdx.x || (minIdx.x == R && i == R-1)) {
                if(j == 1) { // move right
                    int goalI = i+1, goalJ = C, minDist = 0;
                    while(i != goalI || j != goalJ) {
                        int ni = i + dx[minDist], nj = j + dy_R[minDist];
                        if(ni == minIdx.x && nj == minIdx.y) minDist = (minIdx.x != R) ? 1 : 3; // just move right
                        else {
                            i = ni, j = nj;
                            cout << moveR[minDist];
                            minDist = (minDist+1) % 4;
                        }
                    }
                }
                else { // move left
                    j = C;
                    int goalI = i+1, goalJ = 1, minDist = 0;
                    while(i != goalI || j != goalJ) {
                        int ni = i + dx[minDist], nj = j + dy_L[minDist];
                        if(ni == minIdx.x && nj == minIdx.y) minDist = 1; // just move left
                        else {
                            i = ni, j = nj;
                            cout << moveL[minDist];
                            minDist = (minDist+1) % 4;
                        }
                    }
                }
            }
            else {
                if(j==1) {
                    for(int j=0; j<C-1; j++) cout << "R";
                    j = C;
                }
                else {
                    for(int j=0; j<C-1; j++) cout << "Building";
                    j = 1;
                }
            }
            if(i != R) {
                cout << 'D';
                i++;
            }
        }
    }
    cout << '\n';

    return 0;
}
```
