#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using F = double;

const I N = 100000;

I m_arr[N];
I ps[N + 1];
I sum = 0;
I n;

F check(I m) {
  I tot = 0;
  for (I i = 1; i < n; i++) {
    const I u = i + m;
    if (u < n)
      tot = max(tot, ps[u] - ps[i]);
  }
  return (F) (sum - tot) / (n - m);
}

I main(void) {
  freopen("sabotage.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("sabotage.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> m_arr[i];
  for (I i = 0; i <= n; i++) {
    ps[i] = sum;
    sum += m_arr[i];
  }
  for (I i = 1; i < n - 1; i++)
    printf("%i %f\n", i, check(i));
  return 0;
}