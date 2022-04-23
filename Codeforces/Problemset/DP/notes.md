# Practice Problem Notes

## [1285B](https://codeforces.com/contest/1285/problem/B) - Just Eat It!

### Problem:

Find the maximum subarray sum of an array.

<h3 id="kadanes-algorithm">Solution: Kadane's Algorithm</h3>

```cpp
#define N 100000

int ps[N + 1];

// By setting the minimum as the array is traversed, it
// ensures the minimum prefix sum is always to the left of
// the current sum, producing a legal subarray sum which
// may be maximized.
int kadane(int arr[], int n) {
  int result = 0;
  int prefix = 0;
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += arr[i];
    ps[i + 1] = sum;
    result = max(result, sum - prefix);
    prefix = min(prefix, sum);
  }
  return result;
}
```

