## [백준 24337 - 가희와 탑](https://www.acmicpc.net/problem/24337)

### 풀이
- a+b > N+1 보다 크면 불가능하다.
- 가장 긴 빌딩을 공유해야 한다.  
  1, 2, ... , a-1, max(a,b), b-1, ..., 2, 1 으로 구성하고  
  남은 갯수인 N - (a+B-1) 만큼의 1을 맨 앞에다가 출력한다.
- 주의해야 할 점은 a = 1일 때는 남은 갯수의 1을 맨 앞에다가 놓으면 안 된다. 가희가 보이는 건물이 2개가 되기 때문이다.  
  b, b-1, ... , 1인 상태에서 b와 b-1 사이에 남은 갯수의 1들을 넣는 것이 최선이다.

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

int N, a, b;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> a >> b;

    if(a+b > N+1) cout << -1;
    else {
        if(a != 1) for(int _=0; _<N-a-b+1; _++) cout << "1 ";
        for(int i=1; i<=a-1; i++) cout << i << ' ';
        cout << max(a,b) << ' ';
        if(a == 1) for(int _=0; _<N-a-b+1; _++) cout << "1 ";
        for(int i=b-1; i>=1; i--) cout << i << ' ';
    }
    cout << '\n';


    return 0;
}

```