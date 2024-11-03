## [백준 10220 - Self Representing Seq](https://www.acmicpc.net/problem/10220)

### 알고리즘
- 수학
- 애드 혹(정형화된 방법이 아니라, 그 문제를 위한 창의적인 아이디어)

### 풀이
1. A[0] = 0 일 때, 0이 필요한데 0이 0개이므로 모순이다.
2. A[0] = 1 일 때,  
   A[1 ~ N-1] 에서 0이 1개 나와야 한다.  
   N = 4 -> {1,2,1,0} 인 경우가 있으나, 나머지 N들에 대해서는 불가능하다.
3. A[0] = 2 일 때,  
   A[1 ~ N-1] 에서 0이 2개 나와야 한다.  
   N = 4 -> {2,0,2,0}
   N = 5 -> {2,1,2,0,0} 인 경우가 있으나, 나머지 N들에 대해서는 불가능하다.
4. A[0] > 2 일 때,  
   N = 7 -> {3,2,1,1,0,0,0}  
   N = 8 -> {4,2,1,0,1,0,0,0}  
   N = 9 -> {5,2,1,0,0,1,0,0,0}  
   N = 10 -> {6,2,1,0,0,0,1,0,0,0}  
   이런 식으로 N >= 7 에 대하여 A[0]=N-4, A[1]=2, A[2]=1, A[N-4]=1 이고 나머지는 0이 된다. 

결과적으로,  
N = 1,2,3,6 -> 0 이고,  
N = 4 -> 2 이고,  
나머지 N들에 대하여 1이 정답이 된다.

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


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T; cin >> T;
    while(T--) {
        int a; cin >> a;
        if(6%a == 0) cout << 0 << endl;
        else if(a == 4) cout << 2 << endl;
        else cout << 1 << endl;
    }

    return 0;
}
```

### 참고
https://blog.encrypted.gg/139  
https://m.blog.naver.com/phj8498/221341457121