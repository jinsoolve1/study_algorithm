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

int N, Q;
deque<int> dq;
priority_queue<int, vector<int>, greater<>> pq1;
priority_queue<int, vector<int>, less<>> pq2;

bool turn = false;
bool popped[101010];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(popped, 0, sizeof popped);
    popped[0] = true;

    cin >> N >> Q;
    while(Q--) {
        int cmd, p;
        cin >> cmd;
        if(cmd == 0) {
            cin >> p;
            if(!turn) dq.emplace_front(p);
            else dq.emplace_back(p);
        }
        else if(cmd == 1) {
            while(!dq.empty()) {
                pq1.emplace(dq.front());
                pq2.emplace(dq.front());
                dq.pop_front();
            }
            dq.emplace_front(0);
            turn = false;
        }
        else if(cmd == 2) turn = !turn;
        else {
            int x;
            if(!turn) {
                x = dq.front(); dq.pop_front();
                if(x == 0) {
                    while(!pq1.empty()) {
                        x = pq1.top();
                        pq1.pop();
                        if(!popped[x]) break;
                    }
                    if(!pq1.empty()) dq.emplace_front(0);
                    if(popped[x]) { x=dq.front(); dq.pop_front(); }
                }
            }
            else {
                x = dq.back(); dq.pop_back();
                if(x == 0) {
                    while(!pq2.empty()) {
                        x = pq2.top();
                        pq2.pop();
                        if(!popped[x]) break;
                    }
                    if(!pq2.empty()) dq.emplace_back(0);
                    if(popped[x]) { x=dq.back(); dq.pop_back(); }
                }
            }
            popped[x] = true;
            cout << x << '\n';
        }
    }


    return 0;
}