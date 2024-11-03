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
#define f first
#define s second
#define x first
#define y second
#define all(v) (v).begin(), (v).end()

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
char moveR[4] = {'D','R','U','R'}, moveL[4] = {'D', 'L', 'U', 'L'};

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
                int goalI = i+1, goalJ = C, d = 0;
                while(i != goalI || j != goalJ) {
                    int ni = i + dx[d], nj = j + dy_R[d];
                    i = ni, j = nj;
                    cout << moveR[d];
                    d = (d+1) % 4;
                }
            }
            else {
                if(j==1) {
                    for(;j<C; j++) cout << "R";
                }
                else {
                    for(; j>1; j--) cout << "L";
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
                    int goalI = i+1, goalJ = C, d = 0;
                    while(i != goalI || j != goalJ) {
                        int ni = i + dx[d], nj = j + dy_R[d];
                        if(ni == minIdx.x && nj == minIdx.y) d = (minIdx.x != R) ? 1 : 3; // just move right
                        else {
                            i = ni, j = nj;
                            cout << moveR[d];
                            d = (d+1) % 4;
                        }
                    }
                }
                else { // move left
                    j = C;
                    int goalI = i+1, goalJ = 1, d = 0;
                    while(i != goalI || j != goalJ) {
                        int ni = i + dx[d], nj = j + dy_L[d];
                        if(ni == minIdx.x && nj == minIdx.y) d = 1; // just move left
                        else {
                            i = ni, j = nj;
                            cout << moveL[d];
                            d = (d+1) % 4;
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
                    for(int j=0; j<C-1; j++) cout << "L";
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