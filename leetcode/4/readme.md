## [leetcode 4 - Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/description/)

### 알고리즘
- 이분탐색

### 풀이
1. nums1.length < nums2.length 로 만든다.
2. nums1을 기준으로 이분탐색을 진행한다.  
   nums1의 현재 mid1을 기준으로 mid2 = target - mid1이 돤다.  
   여기서 target은 median의 인덱스가 된다.
3. l1 = nums1[mid1-1], r1 = nums1[mid1]  
   l2 = nums2[mid2-1], r2 = nums2[mid2] 라 하자.
4. r1 < l2라면,  
   mid1은 현재보다 커져야 한다. low = mid1+1
5. r2 < l1라면,  
   mid1은 현재보다 작아져야 한다. high = mid1-1
6. 나머지의 경우는 범위가 겹치는 경우 이므로  
   min(l1,l2) -> max(l1,l2) -> min(r1,r2) -> max(r1,r2) 순으로 연속적인 값이 된다.  
   전체 수의 개수가 홀수인지 짝수 인지에 따라 정답을 알맞게 출력하면 된다.

### 시간복잡도
log2(min(m,n)) 이 된다.

```c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if(m > n) {
            swap(m, n);
            swap(nums1, nums2);
        }

        int target = (m+n+1)/2;
        int low = 0, high = m;
        while(low <= high) {
            int mid1 = (low+high)/2;
            int mid2 = target - mid1;

            int l1 = INT_MIN, r1 = INT_MAX;
            int l2 = INT_MIN, r2 = INT_MAX;

            if(mid1 < m) r1 = nums1[mid1];
            if(mid1-1 >= 0) l1 = nums1[mid1-1];
            if(mid2 < n) r2 = nums2[mid2];
            if(mid2-1 >= 0) l2 = nums2[mid2-1];

            if(r1 < l2) low = mid1+1;
            else if(r2 < l1) high = mid1-1;
            else {
                if((n+m)%2 == 1) return max(l1, l2);
                else return (max(l1,l2) + min(r1, r2)) / 2.0;
            }
        }
        return 0;
    }
};
```