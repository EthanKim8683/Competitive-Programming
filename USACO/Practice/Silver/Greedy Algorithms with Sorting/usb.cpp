#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using S = string;
using Lli = long long int;
using B = bool;

const I M = 3e5;

pair<I, B> mous[M];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I a, b, c;
  cin >> a >> b >> c;
  I m;
  cin >> m;
  for (I i = 0; i < m; i++) {
    I val;
    S typ;
    cin >> val >> typ;
    mous[i] = {val, typ == "USB"};
  }
  sort(mous, mous + m);
  Lli cst = 0;
  I a_cnt = 0;
  I b_cnt = 0;
  I c_cnt = 0;
  for (I i = 0; i < m && (a_cnt < a || b_cnt < b || c_cnt < c); i++) {
    const auto [val, usb] = mous[i];
    if (usb) {
      if (a_cnt < a) {
        a_cnt++;
        cst += val;
      } else if (c_cnt < c) {
        c_cnt++;
        cst += val;
      }
    } else {
      if (b_cnt < b) {
        b_cnt++;
        cst += val;
      } else if (c_cnt < c) {
        c_cnt++;
        cst += val;
      }
    }
  }
  printf("%i %lli\n", a_cnt + b_cnt + c_cnt, cst);
  return 0;
}