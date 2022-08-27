#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;
const Lli MOD = 1e9 + 7;

I h_arr[N];
I w_arr[N];
vector<tuple<Lli, I, I>> sta;

Lli sub(Lli x) {
  x %= MOD;
  Lli y = x + 1;
  if (x % 2 == 0)
    x /= 2;
  else
    y /= 2;
  return x * y % MOD;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> h_arr[i];
  for (I i = 0; i < n; i++)
    cin >> w_arr[i];
  Lli res = 0;
  Lli end = 0;
  for (I i = 0; i < n; i++) {
    const I h = h_arr[i];
    const I w = w_arr[i];
    Lli cur = end;
    while (!sta.empty() && get<1>(sta.back()) > h) {
      const auto [beg, upp, low] = sta.back();
      sta.pop_back();
      Lli cnt = 1;
      (cnt *= sub(end - beg)) %= MOD;
      (cnt *= sub(upp) - sub(max(h, low))) %= MOD;
      (res += cnt) %= MOD;
      cur = beg;
    }
    I low = 0;
    if (!sta.empty())
      low = get<1>(sta.back());
    sta.push_back({cur, h, low});
    end += w;
  }
  while (!sta.empty()) {
    const auto [beg, upp, low] = sta.back();
    sta.pop_back();
    Lli cnt = 1;
    (cnt *= sub(end - beg)) %= MOD;
    (cnt *= sub(upp) - sub(low)) %= MOD;
    (res += cnt) %= MOD;
  }
  printf("%lli\n", (res + MOD) % MOD);
  return 0;
}