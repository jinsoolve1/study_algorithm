## [백준 19585 - 전설](https://www.acmicpc.net/problem/19585)

### 알고리즘
- Trie
- 문자열
- 자료구조

### 풀이
trie의 공간복잡도는 (포인터 크기 = 8 byte) x (포인터 배열 개수 = 26개) x (총 노드 개수) 이다.  
색상 trie의 공간복잡도는 8 x 26 x (4000개 x 1000글자) = 약 832MB이다.  
닉네임 trie는 2000글자까지 가능하므로 메모리초과가 나온다. 따라서 색상 문자열들만 trie를 생성한다.  

닉네임 문자열들은 unordered_set을 이용해 존재 여부를 확인한다.  
색상 trie를 이용해 terminal = true인 노드에서 다음 문자부터의 부분문자열과 일치하는 닉네임이 있는지를 확인한다.

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

#define INF 987654321
#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

unordered_set<string> nicks;
class Trie {
public:
    bool terminal;
    map<char, Trie*> child;

    Trie() : terminal(false) {}
    void insert(const char* key) {
        if(*key == 0) terminal = true;
        else {
            if (!child[*key]) child[*key] = new Trie();
            child[*key]->insert(key + 1);
        }
    }
    bool query(const char *key) {
        if(*key == 0) return false;
        if(terminal && nicks.count(string(key))) return true;
        if(!child[*key]) return false;
        return child[*key]->query(key+1);
    }
};

int C, N, Q;
Trie *colors = new Trie();
string s;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> C >> N;
    for(int i=0; i<C; i++) {
        cin >> s;
        colors->insert(s.c_str());
    }
    for(int i=0; i<N; i++) {
        cin >> s;
        nicks.insert(s);
    }

    cin >> Q;
    while(Q--) {
        cin >> s;
        if(colors->query(s.c_str())) cout << "Yes\n";
        else cout << "No\n";
    }

    return 0;
}
```

### 후기
trie를 만들 때 map을 사용하는 것이 unordered_map과 정적배열보다 메모리 효율과 속도 모두 좋게 나온다.  
속도가 빠른 건 당연한 것처럼 보이는데 메모리 효율이 좋은 건 이해가 잘 가지 않는다.  
입력 데이터의 특징 때문일수도 있을 듯 하다. 좀 더 자세히 알아봐야 할 듯 하다.