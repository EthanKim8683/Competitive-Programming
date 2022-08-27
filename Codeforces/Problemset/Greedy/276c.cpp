#include <iostream>
#include <cstdio>
#include <numeric>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 2e5;
const I Q = 2e5;

I a_arr[N];
pair<I, I> rngs[Q];
I ps[N + 1];
I inds[N];

B cmp(I a, I b) {
  return ps[a] < ps[b];
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, q;
  cin >> n >> q;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < q; i++) {
    I l, r;
    cin >> l >> r;
    rngs[i] = {l - 1, r - 1};
  }
  for (I i = 0; i < q; i++) {
    const auto [l, r] = rngs[i];
    ps[l]++;
    ps[r + 1]--;
  }
  for (I i = 1; i < n; i++)
    ps[i] += ps[i - 1];
  iota(inds, inds + n, 0);
  sort(inds, inds + n, cmp);
  sort(a_arr, a_arr + n);
  Lli res = 0;
  for (I i = 0; i < n; i++)
    res += (Lli) ps[inds[i]] * a_arr[i];
  printf("%lli\n", res);
  return 0;
}