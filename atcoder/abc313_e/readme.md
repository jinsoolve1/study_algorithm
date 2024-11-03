## [atcoder 313-E : Duplicate](https://atcoder.jp/contests/abc313/tasks/abc313_e)

### 알고리즘
- sweeping

### 풀이
S = "AB" 라 하자. 여기서 A와 B는 1~9 사이의 문자다.  

1. A != 1 and B != 1  
   f(S) = A...A (B개)가 될 것이다.    
   f(f(S)) = A...A (A*(B-1)개)가 될 것이다.  
   즉, 무수히 많이 늘어날 것이다.
2. A == 1 and B != 1
   f(S) = 1...1 (B개)가 될 것이다.  
   f(f(S)) = 1...1 (B-1개)가 될 것이다.  
   이런 식으로 계속 줄어든다. 따라서 가능하다.
3. A != 1 and B == 1
   f(S) = A 가 될 것이고 종료가 된다.
4. A == 1 and B == 1
   f(S) = 1 가 될 것이고 마찬가지로 종료가 된다.

위의 경우를 보았을 떄, 우리는 `문자열 S에서 임의의 연속하는 두 수를 보았을 떄 적어도 하나 이상이 1이 되어야 한다.`    
그렇지 않은 문자열 S는 무한히 늘어나므로 -1을 출력해야 한다.  

그러면 이번엔 무수히 많아지지 않는 문자열 S의 operation 수는 어떻게 구해야 할까?  

n[i] := `(모든 증식된) i번째 문자열이 지워지기 위해 필요한 연산 횟수` 라 하자.  
i번째 문자열은 i+1문자열이 지워지기 전까지 S[i+1]-1개 만큼씩 매 operate마다 증식한다.  
( S[i+1]이 아닌 S[i+1]-1개 인 이유는 갯수가 1 -> S[i+1]로 변화하는 것이니 증가량은 S[i+1]-1개가 된다. )  
즉, i번째 문자열이 전부 지워지려면, 1)S[i+1]가 제거되고 나서, 2)증식된 개수만큼 더해야 한다.  
이를 식으로 표현하면 아래와 같다.  
n[i] = `1 + n[i+1]*(S[i+1]-1) + n[i+1]` 이 된다.


예시를 직접 해보면 이해가 쉽다.  

S = "A1B1C"에서 n번 operation을 한 후에야 B가 지워졌다고 하자.  
그렇다면 S = "A1....1"인 형태일텐데, 이때의 1의 개수는 1 + n*(B-1)이 된다.  
왜냐하면 B 앞의 1은 B가 사리지기 전까지 계속 B-1 씩 갯수가 늘어나게 된다.  
그렇다면 B가 n번 째에 사라졌다면 B는 1에서 1+n(B-1)까지 늘어나게 된다.  
1은 매 operation마다 하나씩 지워지므로 S = "A"가 되려면 n += 1 + n(B-1)을 해줘야 하는 것을 알 수 있고,  
n이 정답이 된다.

### 코드
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

const ll p = 998244353;
int N;
string S;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> S;
    for(int i=0; i<N-1; i++) {
        if(S[i] != '1' && S[i+1] != '1') {
            cout << "-1\n";
            return 0;
        }
    }

    ll ans = 1;
    for(int i=N-2; i>=0; i--) {
        ans = (ans + 1 + (ans*(S[i+1]-'0' - 1) % p))  % p;
    }
    cout << ans-1 << endl;


    return 0;
}
```

