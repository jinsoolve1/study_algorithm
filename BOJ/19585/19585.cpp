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