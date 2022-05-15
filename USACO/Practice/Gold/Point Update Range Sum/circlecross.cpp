#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 50000;

I fens[2 * N + 1];
I opns[N];
I len;

void upd(I i, I val) {
  for (; i <= len; i += i & -i)
    fens[i] += val;
}

I qry(I i) {
  I res = 0;
  for (; i > 0; i -= i & -i)
    res += fens[i];
  return res;
}

I main(void) {
  freopen("circlecross.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("circlecross.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  len = n * 2;
  I opn = 0;
  Lli res = 0;
  for (I i = 1; i <= len; i++) {
    I a;
    cin >> a;
    a--;
    if (opns[a]) {
      res += opn - qry(opns[a]);
      upd(opns[a], -1);
      opn--;
    } else {
      opns[a] = i;
      upd(i, 1);
      opn++;
    }
  }
  printf("%lli\n", res);
  return 0;
}