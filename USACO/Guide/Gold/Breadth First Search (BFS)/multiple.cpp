#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

using I = int;
using B = bool;

const I K = 1e5;
const I L = 18;

I pows[L + 1];
queue<pair<I, I>> que;
B viss[100000 + 1][9 * 5];
I res;

I sum(I val) {
  I res = 0;
  for (; val; val /= 10)
    res += val % 10;
  return res;
}

void add(I cry, I con) {
  if (con < res && !viss[cry][con]) {
    viss[cry][con] = true;
    que.push({cry, con});
    res = min(res, con + sum(cry));
  }
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I k;
  cin >> k;
  res = sum(k);
  for (I i = 1; i <= 9; i++) {
    const I sum = i * k;
    add(sum / 10, sum % 10);
  }
  while (!que.empty()) {
    const auto [cry, con] = que.front();
    que.pop();
    for (I i = 0; i <= 9; i++) {
      const I sum = cry + i * k;
      add(sum / 10, con + sum % 10);
    }
  }
  printf("%i\n", res);
  return 0;
}