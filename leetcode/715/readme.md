## [leetcode 715 - Range Module](https://leetcode.com/problems/range-module/description/)

### 알고리즘
- map
- lazy segment tree
- coordinate compression

### 풀이1
1. query가 10^4만 들어오므로 모든 left, right를 vector에 넣어 좌표압축을 한다.
2. lazy segment tree를 이용해 해결한다.

그러나 문제에 함수만 주어져서 모든 입력을 한 번에 받을 수가 없다. 그래서 실제 활용하지는 못 했다.

### 풀이2
1. map[x] = y : [x,y) 를 의미한다고 정의하자.
2. O(klogn) 정도의 시간안에 추가 및 삭제할 수 있다. (여기서 k는 map에 할당되어 활성화되어 있는 range 수이다.)
3. O(logn) 시간에 query를 해결할 수 있다.

주의할 점은 추가 및 삭제할 때 범위에 따라 삭제를 잘 해야 하므로 반례가 생기지 않도록 논리적으로 잘 구현하자.

```c++
class RangeModule {
public:
    map<int, int> mp;

    RangeModule() {}
    
    void addRange(int left, int right) {
        auto it = mp.upper_bound(left);
        if(it != mp.begin() && left <= prev(it)->second) {
            left = prev(it)->first;
            right = max(right, prev(it)->second);
        }
        while(it != mp.end() && it->first <= right) {
            right = max(right, it->second);
            mp.erase(it++);
        }
        mp[left] = right;
    }
    
    bool queryRange(int left, int right) {
        auto it = mp.upper_bound(left);
        if(it == mp.begin()) return false;
        return (--it)->second >= right;
    }
    
    void removeRange(int left, int right) {
        auto it = mp.lower_bound(left);
        if(it != mp.begin() && left < prev(it)->second) {
            it = prev(it);
            mp[left] = it->second;
            it->second = left;
            it = next(it);
        }
        while(it != mp.end() && it->second <= right) mp.erase(it++);
        if(it != mp.end() && it->first < right) {
            mp[right] = it->second;
            mp.erase(it++);
        }
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
```