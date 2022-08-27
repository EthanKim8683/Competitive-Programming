#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 2e5;

I a_arr[N];
pair<I, I> vals[N];
pair<I, I> dp[N];
I ress[N];

void cmb(pair<I, I>& a, pair<I, I> b) {
  if (b.first > a.first)
    a = b;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  fill_n(dp, n, pair<I, I>(1, -1));
  for (I i = 0; i < n; i++)
    vals[i] = {a_arr[i], i};
  sort(vals, vals + n);
  for (I i = 0; i < n; i++) {
    const I a = a_arr[i];
    const auto low = upper_bound(vals, vals + n, pair<I, I>(a, i));
    const auto upp = upper_bound(vals, vals + n, pair<I, I>(a + 1, i));
    if (low != vals + n && low->first == a)
      cmb(dp[low->second], dp[i]);
    if (upp != vals + n && upp->first == a + 1)
      cmb(dp[upp->second], {dp[i].first + 1, i});
  }
  pair<I, I> res = {1, 0};
  for (I i = 0; i < n; i++)
    cmb(res, {dp[i].first, i});
  auto [len, cur] = res;
  for (I i = 0; i < len; i++) {
    ress[i] = cur;
    cur = dp[cur].second;
  }
  reverse(ress, ress + len);
  printf("%i\n", res);
  for (I i = 0; i < len; i++)
    printf("%i ", ress[i] + 1);
  return 0;
}