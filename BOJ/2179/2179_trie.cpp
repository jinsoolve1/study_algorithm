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

vector<string> v;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    Trie *root = new Trie();
    for(int i=0; i<N; i++) {
        string s; cin >> s;
        v.emplace_back(s);
        root->insert(s.c_str(), i, 0);
    }
    for(int l=100; l>=0; l--) {
        if(logVec[l].empty()) continue;
        sort(all(logVec[l]));
        cout << v[logVec[l][0].f] << '\n' << v[logVec[l][0].s] << '\n';
        break;
    }


    return 0;
}