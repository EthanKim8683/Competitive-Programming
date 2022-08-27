#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>
#include <unordered_map>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 40;
const I MIN = -1e9;
const I MAX = 1e9;
const Lli X = 688631;
const Lli Y = 259123;
const Lli MOD = 1e9 + 7;

pair<I, I> lows[N - N / 2];
pair<I, I> upps[N / 2];
unordered_map<Lli, array<I, N - N / 2 + 1>> low_vals;
Lli ress[N + 1];

Lli one(Lli x) {
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = ((x >> 16) ^ x) * 0x45d9f3b;
  x = (x >> 16) ^ x;
  return x;
}

Lli two(Lli x, Lli y) {
  return one(one(x + X) + y + Y);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  Lli xg, yg;
  cin >> xg >> yg;
  const Lli low = n - n / 2;
  const Lli upp = n / 2;
  for (I i = 0; i < low; i++) {
    I x, y;
    cin >> x >> y;
    lows[i] = {x, y};
  }
  for (I i = 0; i < upp; i++) {
    I x, y;
    cin >> x >> y;
    upps[i] = {x, y};
  }
  for (I i = 0; i < (1 << low); i++) {
    Lli x = 0;
    Lli y = 0;
    for (I j = 0; j < low; j++) {
      if (i >> j & 1) {
        x += lows[j].first;
        y += lows[j].second;
      }
    }
    low_vals[two(x, y)][__builtin_popcount(i)]++;
  }
  for (I i = 0; i < (1 << upp); i++) {
    Lli x = xg;
    Lli y = yg;
    for (I j = 0; j < upp; j++) {
      if (i >> j & 1) {
        x -= upps[j].first;
        y -= upps[j].second;
      }
    }
    const auto it = low_vals.find(two(x, y));
    if (it != low_vals.end())
      for (I j = 0; j <= low; j++)
        ress[j + __builtin_popcount(i)] += it->second[j];
  }
  for (I i = 1; i <= n; i++)
    printf("%lli\n", ress[i]);
  return 0;
}