#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 10000;

I cols[N];
I enes[N];
I pars[N];

I fnd(I x) {
  if (pars[x] < 0)
    return x;
  return pars[x] = fnd(pars[x]);
}

void uni(I& a, I& b) {
  if (a == -1) {
    a = b;
    return;
  }
  if (b == -1) {
    b = a;
    return;
  }
  if ((a = fnd(a)) == (b = fnd(b)))
    return;
  if (pars[a] > pars[b])
    swap(a, b);
  pars[a] += pars[b];
  pars[b] = a;
  uni(enes[a], enes[b]);
}

B con(I a, I b) {
  if (a == -1 || b == -1)
    return false;
  return fnd(a) == fnd(b);
}

B frd(I a, I b) {
  return con(a, b);
}

B ene(I a, I b) {
  return con(a, enes[fnd(b)]) || con(enes[fnd(a)], b);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(pars, n, -1);
  fill_n(enes, n, -1);
  while (true) {
    I c = 0, x = 0, y = 0;
    cin >> c >> x >> y;
    if (c == 0 && x == 0 && y == 0)
      break;
    if (c == 1) {
      if (ene(x, y)) {
        printf("-1\n");
        continue;
      }
      uni(x, y);
    } else if (c == 2) {
      if (frd(x, y)) {
        printf("-1\n");
        continue;
      }
      uni(x, enes[fnd(y)]);
      uni(enes[fnd(x)], y);
    } else if (c == 3)
      printf("%i\n", frd(x, y));
    else if (c == 4)
      printf("%i\n", ene(x, y));
  }
  return 0;
}