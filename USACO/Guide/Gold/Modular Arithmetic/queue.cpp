#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 998244353;

queue<pair<I, I>> que;

Lli pow(Lli bse, Lli exp) {
  bse %= MOD;
  Lli res = 1;
  while (exp) {
    if (exp & 1)
      (res *= bse) %= MOD;
    (bse *= bse) %= MOD;
    exp >>= 1;
  }
  return res;
}

Lli inv(Lli val) {
  return pow(val, MOD - 2);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I q;
  cin >> q;
  Lli a_acc = 1;
  Lli b_acc = 0;
  while (q--) {
    I t;
    cin >> t;
    if (t == 0) {
      I a, b;
      cin >> a >> b;
      (a_acc *= a) %= MOD;
      (b_acc *= a) %= MOD;
      (b_acc += b) %= MOD;
      que.push({a, b});
    } else if (t == 1) {
      const auto [a, b] = que.front();
      que.pop();
      (a_acc *= inv(a)) %= MOD;
      (b_acc -= b * a_acc) %= MOD;
    } else if (t == 2) {
      I x;
      cin >> x;
      Lli res = x;
      (res *= a_acc) %= MOD;
      (res += b_acc) %= MOD;
      (res += MOD) %= MOD;
      printf("%lli\n", res);
    }
  }
  return 0;
}