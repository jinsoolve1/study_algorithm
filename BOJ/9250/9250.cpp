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

class Trie {
public:
    bool terminal;
    Trie *fail;
    unordered_map<char, Trie*> children;

    Trie() : terminal(false) {}

    void insert(const char* key) {
        if(*key == 0) terminal = true;
        else {
            if (!children[*key]) children[*key] = new Trie();
            children[*key]->insert(key + 1);
        }
    }
    void linkFail() {
        Trie *root = this;
        queue<Trie*> q;
        q.push(root);
        while(!q.empty()) {
            Trie *here = q.front(); q.pop();
            for(auto &child : here->children) {
                Trie *there = child.second;
                if(here == root) there->fail = root;
                else {
                    Trie *prev = here->fail;
                    while(prev != root && prev->children.find(child.first) == prev->children.end()) prev = prev->fail;
                    if(prev->children.find(child.first) != prev->children.end()) prev = prev->children[child.first];
                    there->fail = prev;
                }
                if(there->fail->terminal) there->terminal = true;
                q.push(there);
            }
        }
    }
};

int N, Q;
Trie *root = new Trie();

// find substring of text in root
bool kmp(Trie *root, string text) {
    Trie *here = root;
    for(char c : text) {
        while(here != root && here->children.find(c) == here->children.end()) here = here->fail;
        if(here->children.find(c) != here->children.end()) here = here->children[c];
        if(here->terminal) return true;
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=0; i<N; i++) {
        string s; cin >> s;
        root->insert(s.c_str());
    }
    root->linkFail();

    cin >> Q;
    while(Q--) {
        string s; cin >> s;
        if(kmp(root, s)) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}