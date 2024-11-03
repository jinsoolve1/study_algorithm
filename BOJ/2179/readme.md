## 백준 2179 - 비슷한 단어

### 풀이
정렬로 풀어도 가능하지만 그것보다는 Trie를 사용하는 게 더 직관적인듯하여 Trie로 풀었다.

- Trie에 insert를 하다가 해당 노드(글자)에 두번째 방문하는 것이면 공통된 글자임을 알 수 있다.
- logVec[길이] 배열에 해당 길이의 접두사를 가지는 S,T 후보들을 저장한다.
- 가장 긴 길이의 후보들을 오름차순 정렬하여 출력한다.

### 주의
같은 길이라면 (S,T)가 오름차순으로 정렬했을 때 첫번째 값으로 해야 한다.
> input <br/>
> 4 <br/>
> aa <br/>
> bb <br/>
> bc <br/>
> aj<br/>

> answer<br/>
> aa<br/>
> aj<br/>

가 되어야 한다. bb,bc가 출력되지는 않는지 확인해보자.

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

vector<pii> logVec[101];
int sdx, tdx;
class Trie {
public:
    int firstIdx, secondIdx;
    unordered_map<char,Trie*> child;

    Trie() : firstIdx(-1), secondIdx(-1) {}
    void insert(const char* key, int idx, int len) {
        if(firstIdx != -1 && secondIdx == -1) logVec[len].emplace_back(firstIdx, idx);
        if(firstIdx == -1) firstIdx = idx;
        else if(secondIdx == -1) secondIdx = idx;
        if(*key == 0) return;
        if (!child[*key]) child[*key] = new Trie();
        child[*key]->insert(key + 1, idx, len+1);
    }
};

int N;

vector<string> V;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    Trie *root = new Trie();
    for(int i=0; i<N; i++) {
        string s; cin >> s;
        V.emplace_back(s);
        root->insert(s.c_str(), i, 0);
    }
    for(int l=100; l>=0; l--) {
        if(logVec[l].empty()) continue;
        sort(all(logVec[l]));
        cout << V[logVec[l][0].Flow] << '\n' << V[logVec[l][0].s] << '\n';
        break;
    }


    return 0;
}
```