#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

stack<pair<Lli, I>> stts;
Lli k_arr[N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("advert.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> k_arr[i];
  Lli res = 0;
  for (I i = 0; i < n; i++) {
    const auto k = k_arr[i];
    I ind = i;
    while (!stts.empty() && stts.top().first >= k) {
      const auto [hgt, beg] = stts.top();
      stts.pop();
      ind = beg;
      res = max(res, hgt * (i - beg));
    }
    stts.push({k, ind});
  }
  while (!stts.empty()) {
    const auto [hgt, beg] = stts.top();
    stts.pop();
    res = max(res, hgt * (n - beg));
  }
  printf("%lli\n", res);
  return 0;
}