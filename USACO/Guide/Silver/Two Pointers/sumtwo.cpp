#include <iostream>
#include <cstdio>
#include <algorithm>
#include <numeric>

using namespace std;

using I = int;
using B = bool;

const I N = 2e5;

I a_arr[N];
I inds[N];

B cmp(I a, I b) {
  return a_arr[a] > a_arr[b];
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, x;
  cin >> n >> x;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  iota(inds, inds + n, 0);
  sort(inds, inds + n, cmp);
  I l = 0;
  I r = n - 1;
  while (l < r) {
    const I sum = a_arr[inds[l]] + a_arr[inds[r]];
    if (sum == x) {
      printf("%i %i\n", inds[l] + 1, inds[r] + 1);
      return 0;
    } else if (sum < x)
      r--;
    else if (sum > x)
      l++;
  }
  printf("IMPOSSIBLE\n");
  return 0;
}