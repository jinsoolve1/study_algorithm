## [백준 1201 - NMK](https://www.acmicpc.net/problem/1201)

### 풀이
길이가 K이하인 연속 감소 부분수열이 M개가 되도록 만들면 된다.<br/>
> 연속 감소 부분수열이란, 각 수가 연속적이면서 감소하는 수열을 뜻한다.<br/>
> (ex. 5,4,3 -> 연속 감소O, 6,4,3 -> 연속 감소X)<br/>

i번째 연속 감소 부분수열의 가장 큰 값이 i+1번째 연속 감소 부분수열의 가장 작은 값보다 1만큼 작게 만든다.<br/>
해당 조건으로 만들 수 있으면 길이 N인 수열을 LCS = M, SCS = K가 되도록 만들 수 있다.
> 예를 들면, [(4 3 2 1) (6 5) (8 7)] 이런 식이 된다. 

이때 길이가 K 이하인 연속 감수 부분 수열을 총 M개를 만들 수 있는 지를 확인해야 한다.<br/>
1. 모든 연속감소 부분 수열의 길이가 K일 때 만들 수 있는 부분수열의 개수는 ceil(N/K)이다.<br/>
   (마지막 부분수열의 길이는 N%K가 될 것이다.)<br/>
   부분수열의 개수가 LCS가 되므로 M은 ceil(N/K) 이상이어야 한다.
2. 첫번째 연속감소 부분수열의 길이만 K이고 나머지 연속감소 부분수열의 길이는 1이라고 하자.<br/>
   부분수열의 개수는 1 + (N-K) 이 된다.<br/>
   부분수열의 개수가 LCS가 되므로 M은 (N-K+1) 이하이어야 한다.

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

int N, M, K;
double dN, dM, dK;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M >> K;
    dN = N; dM = M; dK = K;
    if(!(ceil(dN/dK) <= dM && dM <= dN-dK+1)) cout << "-1\n";
    else {
        int low = 0;
        for(int i=K; i>low; i--) cout << i << ' ';
        if(M > 1) {
            low = K;
            int cnt = (N-K)/(M-1);
            int j=1;
            for(; j<=(N-K)%(M-1); j++) {
                for(int i=low+cnt+1; i>low; i--) cout << i << ' ';
                low += cnt+1;
            }
            for(;j <= M-1; j++) {
                for(int i=low+cnt; i>low; i--) cout << i << ' ';
                low += cnt;
            }
        }
        cout << '\n';
    }



    return 0;
}
```