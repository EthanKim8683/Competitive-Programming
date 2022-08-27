#include <iostream>
#include <cstdio>
#include <unordered_set>
#include <queue>

using namespace std;

using I = int;
using B = bool;

B viss[387420489];
I pows[9];
queue<pair<I, I>> que;

I qry(I i, I dgt) {
  return i / pows[dgt] % 9;
}

I mov(I i, I dgt) {
  return i * pows[dgt];
}

I swp(I i, I a, I b) {
  const auto a_val = qry(i, a);
  const auto b_val = qry(i, b);
  return i + mov(b_val - a_val, a) + mov(a_val - b_val, b);
}

I ind(I i, I j) {
  return i * 3 + j;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("swap.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I acc = 1;
  for (I i = 0; i < 9; i++) {
    pows[i] = acc;
    acc *= 9;
  }
  I bse = 0;
  for (I i = 0; i < 3; i++) {
    for (I j = 0; j < 3; j++) {
      I d;
      cin >> d;
      bse += mov(d - 1, ind(i, j));
    }
  }
  I trg = 0;
  I dgt = 0;
  for (I i = 0; i < 3; i++)
    for (I j = 0; j < 3; j++)
      trg += mov(dgt++, ind(i, j));
  que.push({bse, 0});
  while (!que.empty()) {
    const auto [a, dst] = que.front();
    que.pop();
    if (!viss[a]) {
      viss[a] = true;
      if (a == trg) {
        printf("%i\n", dst);
        break;
      }
      for (I i = 0; i < 3; i++) {
        for (I j = 0; j < 3; j++) {
          if (i + 1 < 3) {
            const auto b = swp(a, ind(i, j), ind(i + 1, j));
            if (!viss[b])
              que.push({b, dst + 1});
          }
          if (j + 1 < 3) {
            const auto b = swp(a, ind(i, j), ind(i, j + 1));
            if (!viss[b])
              que.push({b, dst + 1});
          }
        }
      }
    }
  }
  return 0;
}