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
#define all(v) (v).begin(), (v).end()

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
    for(char c : s) T.push_back(c);
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