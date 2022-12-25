#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e9 + 7;
const I N = 2e5;

vector<I> vals;
I x_arr[N];
Lli fens[N + 1];
I n;

I cps(I i) {
  return upper_bound(vals.begin(), vals.end(), i) - vals.begin();
}

void upd(I i, I val) {
  for (; i <= n; i += i & -i)
    fens[i] = (fens[i] + val) % MOD;
}

Lli qry(I i) {
  Lli res = 0;
  for (; i > 0; i -= i & -i)
    res = (res + fens[i]) % MOD;
  return res;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("increasing.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++) {
    I x;
    cin >> x;
    x_arr[i] = x;
    vals.push_back(x);
  }
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  Lli res = 0;
  for (I i = 0; i < n; i++) {
    const auto x = cps(x_arr[i]);
    const auto sum = qry(x - 1) + 1;
    res = (res + sum) % MOD;
    upd(x, sum);
  }
  printf("%lli\n", res);
  return 0;
}