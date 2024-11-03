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

class SuffixArray {
private:
    string str;
    vector<int> sa, rank, tmpRank, lcp;
    int sz;

    void make_sa() {
        sa.assign(sz, 0);
        rank.assign(sz+1, -1);
        tmpRank.assign(sz+1, -1);

        for(int i=0; i<sz; i++) sa[i] = i, rank[i] = str[i]-'a';

        for(int cmpLen=1; cmpLen<sz; cmpLen<<=1) {
            auto cmp = [&](int x, int y) {
                if(rank[x] == rank[y]) return rank[x+cmpLen] < rank[y+cmpLen];
                return rank[x] < rank[y];
            };
            sort(all(sa),cmp);

            tmpRank[sa[0]] = 0;
            for(int i=1; i<sz; i++) {
                if(cmp(sa[i-1],sa[i])) tmpRank[sa[i]] = tmpRank[sa[i-1]] + 1;
                else tmpRank[sa[i]] = tmpRank[sa[i-1]];
            }
            rank = tmpRank;
        }
    }
    void make_lcp() {
        lcp.assign(sz, 0);
        rank.assign(sz, 0);

        for(int i=0; i<sz; i++) rank[sa[i]] = i;

        int len = 0;
        for(int i=0; i<sz; i++) {
            if(rank[i] > 0) {
                int j = sa[rank[i]-1];
                while(str[i+len] == str[j+len]) len++;
                lcp[rank[i]] = len;
                if(len > 0) len--;
            }
        }
    }
    void update() { make_sa(); make_lcp(); }

public:
    SuffixArray(string &s) { this->input_string(s); }

    void input_string(string &s) {
        str = s; sz = s.size();
        update();
    }
    vector<int> get_sa() { return sa; }
    vector<int> get_lcp() { return lcp; }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string A, B; cin >> A >> B;
    string S = A + " " + B;
    SuffixArray SA(S);
    vector<int> sa = SA.get_sa(), lcp = SA.get_lcp();
    int loc=0, len=-1;
    for(int i=1; i<S.length(); i++) {
        if((sa[i-1]<A.length() && sa[i]>=A.length()) || (sa[i-1]>=A.length() && sa[i]<A.length()))
            if(len < lcp[i]) loc = sa[i], len = lcp[i];
    }
    cout << len << endl << S.substr(loc,len) << endl;


    return 0;
}