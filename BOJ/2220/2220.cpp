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
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

int n;
vector<int> heap;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n;
    heap.resize(n+1);
    heap[1] = 1;
    for(int i=2; i<=n; i++) {
        heap[i] = i;
        swap(heap[i-1],heap[i]);
        for(int j=i-1; j>1; j>>=1) swap(heap[j], heap[j/2]);
    }
    for(int i=1; i<=n; i++) cout << heap[i] << ' ';
    cout << '\n';

    return 0;
}