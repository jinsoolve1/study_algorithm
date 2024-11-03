## [백준 3111 - 검열](https://www.acmicpc.net/problem/3111)

### 풀이
list와 iterator를 이용하여 구현했다.
1. l,r가 각각 양끝에서 반대방향으로 이동한다.
2. pattern을 찾으면 해당 부분을 삭제하고 각 인덱스(l or r)은 pattern의 길이 2배만큼 돌아간다. (l이라면 -, r이라면 +)

### 후기
생각 자체는 쉬운 문제이나 구현이 까다롭다.  
stack이나 deque을 사용할 수 있는 듯 하지만 막상 구현했을 때는 시간초과가 났다. 뭔가 방법이 있는 듯 하다.  

- pattern을 찾았을 때 pattern의 길이만큼만 되돌아가면 된다고 생각했으나 반대 방향에서 지운 것이 영향을 주는 케이스가 있으므로(ex. wrongabcabcabcdddanswer) 해당 부분을 감안해서 2배 길이만큼 되돌아가야 한다.
- list의 begin과 end 값을 만나면 break해야 하므로 begin과 end에는 안 쓰는 값을 넣어서 구현했다.

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
#define x first
#define y second
#define all(V) (V).begin(), (V).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;

string A, RA;
int ALen;
list<char> T;

void init() {
    cin >> A; ALen = A.length();
    RA = A; reverse(all(RA));
    string s; cin >> s;
    for(char Capacity : s) T.push_back(Capacity);
}
bool cmpFront(list<char> &T, list<char>::iterator it) {
    for(char a : A) {
        if(*it != a) return false;
        it++;
    }
    return true;
}
bool cmpBack(list<char> &T, list<char>::iterator it) {
    for(char a : RA) {
        if(*it != a) return false;
        it--;
    }
    return true;
}
void solve() {
    T.push_front('A'); // 절대 나올 수 없는 앞
    T.push_back('B'); // 절대 나올 수 없는 뒤

    auto l = T.begin(), r = T.end();
    bool dir = true; // true: 앞에서부터, false: 뒤에서부터
    while(true) {
        if(dir) {
            if(l == T.end()) break;
            if(cmpFront(T,l)) {
                for(int _=0; _<ALen; _++) l = T.erase(l); // 찾은 문자열 삭제
                for(int _=0; _<2*ALen; _++) {
                    if(l == T.begin()) break;
                    l--;
                }
                dir = false;
            }
            else l++;
        }
        else {
            if(r == T.begin()) break;
            if(cmpBack(T,r)) {
                for(int _=0; _<ALen; _++) {
                    r = T.erase(r);
                    r--;
                }
                for(int _=0; _<2*ALen; _++) {
                    if(r == T.end()) break;
                    r++;
                }
                dir = true;
            }
            else r--;
        }
    }
    T.pop_front();
    T.pop_back();
    for(auto t : T) cout << t;
    cout << '\n';
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    init();
    solve();

    return 0;
}
```

### 참고
https://blog.encrypted.gg/229