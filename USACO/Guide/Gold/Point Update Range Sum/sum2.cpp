#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

Lli fens[N + 1];
I x_arr[N];
I n;

void upd(I i, I val) {
  for (; i <= n; i += i & -i)
    fens[i] += val;
}

Lli qry(I i) {
  Lli res = 0;
  for (; i > 0; i -= i & -i)
    res += fens[i];
  return res;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("sum2.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I q;
  cin >> n >> q;
  for (I i = 1; i <= n; i++) {
    I x;
    cin >> x;
    upd(i, x);
    x_arr[i] = x;
  }
  while (q--) {
    I t;
    cin >> t;
    if (t == 1) {
      I k, u;
      cin >> k >> u;
      upd(k, u - x_arr[k]);
      x_arr[k] = u;
    } else if (t == 2) {
      I a, b;
      cin >> a >> b;
      printf("%lli\n", qry(b) - qry(a - 1));
    }
  }
  return 0;
}