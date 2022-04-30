#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I N = 10000;

I d_arr[N];
priority_queue<I, vector<I>, greater<I>> stage;
I n, t;

B check(I k) {
  I tim = 0;
  I ind = k;
  for (I i = k; i--;)
    stage.push(d_arr[i]);
  while (!stage.empty()) {
    tim = stage.top();
    stage.pop();
    if (ind < n) {
      stage.push(tim + d_arr[ind]);
      ind++;
    }
  }
  return tim <= t;
}

I main(void) {
  freopen("cowdance.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("cowdance.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> t;
  for (I i = 0; i < n; i++)
    cin >> d_arr[i];
  I l = 1;
  I r = n;
  while (l < r) {
    const I m = l + (r - l) / 2;
    if (check(m))
      r = m;
    else
      l = m + 1;
  }
  printf("%i\n", l);
  return 0;
}