#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>

using namespace std;

using I = int;
using Lli = long long int;

const I R = 1000;
const I C = 1000;

I cels[R][C];
I lens[R][C];
vector<tuple<I, I, I>> sta;

Lli sub(Lli x) {
  return x * (x + 1) / 2;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I r, c;
    cin >> r >> c;
    for (I i = 0; i < r; i++)
      for (I j = 0; j < c; j++)
        cin >> cels[i][j];
    for (I i = 0; i < c; i++) {
      I len = 1;
      for (I j = r - 1; j >= 0; j--) {
        if (j + 1 < r && cels[j][i] == cels[j + 1][i])
          len++;
        else
          len = 1;
        lens[j][i] = len;
      }
    }
    Lli res = 0;
    for (I i = 0; i < r; i++) {
      for (I j = 0; j < c; j++) {
        if (j - 1 < 0 || cels[i][j] != cels[i][j - 1]) {
          while (!sta.empty()) {
            const auto [beg, upp, low] = sta.back();
            sta.pop_back();
            res += sub(j - beg) * (upp - low);
          }
        }
        const I len = lens[i][j];
        I cur = j;
        while (!sta.empty() && get<1>(sta.back()) >= len) {
          const auto [beg, upp, low] = sta.back();
          sta.pop_back();
          res += sub(j - beg) * (upp - max(low, len));
          cur = beg;
        }
        I low = 0;
        if (!sta.empty())
          low = get<1>(sta.back());
        sta.push_back({cur, len, low});
      }
      while (!sta.empty()) {
        const auto [beg, upp, low] = sta.back();
        sta.pop_back();
        res += sub(c - beg) * (upp - low);
      }
    }
    printf("%lli\n", res);
  }
  return 0;
}