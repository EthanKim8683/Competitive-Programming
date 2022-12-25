#include <iostream>
#include <cstdio>
#include <algorithm>
#include <numeric>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 5000;

I inds[N];
I a_arr[N];

B cmp(I a, I b) {
  return a_arr[a] < a_arr[b];
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, x;
  cin >> n >> x;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  iota(inds, inds + n, 0);
  sort(inds, inds + n, cmp);
  for (I i = 0; i < n; i++) {
    I l = i + 1;
    I r = n - 1;
    while (l < r) {
      const Lli sum = (Lli) a_arr[inds[i]] + a_arr[inds[l]] + a_arr[inds[r]];
      if (sum == x) {
        printf("%i %i %i\n", inds[i] + 1, inds[l] + 1, inds[r] + 1);
        return 0;
      } else if (sum > x)
        r--;
      else if (sum < x)
        l++;
    }
  }
  printf("IMPOSSIBLE\n");
  return 0;
}