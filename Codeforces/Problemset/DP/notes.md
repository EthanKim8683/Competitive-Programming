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

The function returns the maximum subarray sum.

## [1526B](https://codeforces.com/problemset/problem/1526/B) - I Hate 1111

### Problem:

Find the largest value impossible to make using any amount of 11 or 111's.

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

using I=int;

// Chicken McNugget theorem happens here!
I cmn(I n,I m){
  return n*m-n-m;
}

// I/O
I main(){
  cin.tie(0)->sync_with_cstdio(0);
  I n,m;cin>>n>>m;
  printf("%i\n",cmn(n,m));
  return 0;
}
```

The function returns 1099 as the largest impossible sum, allowing all values below to be brute forced in decent time.