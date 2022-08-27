#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using C = char;
using B = bool;

const I N = 3e5;

C s[N + 1];
I ps[3][N + 1];
I typs[N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("1404a.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n, k;
    cin >> n >> k;
    cin >> s;
    fill_n(typs, n, 0);
    for (I i = 0; i < 2; i++)
      fill_n(ps[i], n + 1, 0);
    for (I i = 0; i < n; i++) {
      ps[0][i + 1] += ps[0][i] + (s[i] == '0');
      ps[1][i + 1] += ps[1][i] + (s[i] == '1');
    }
    I end = 0;
    for (I i = 0; i + k <= n; i++) {
      const auto a_cnt = ps[0][i + k] - ps[0][i];
      const auto b_cnt = ps[1][i + k] - ps[1][i];
      if (a_cnt != b_cnt) {
        if (a_cnt == k / 2) {
          const I beg = max(end, i);
          end = max(end, i + k);
          fill(typs + beg, typs + end, 2);
        }
        if (b_cnt == k / 2) {
          const I beg = max(end, i);
          end = max(end, i + k);
          fill(typs + beg, typs + end, 1);
        }
      }
    }
    for (I i = 0; i < n; i++) {
      if (s[i] == '?') {
        if (typs[i] == 1)
          s[i] = '0';
        if (typs[i] == 2)
          s[i] = '1';
      }
    }
    for (I i = 0; i < 3; i++)
      fill_n(ps[i], n + 1, 0);
    for (I i = 0; i < n; i++) {
      ps[0][i + 1] += ps[0][i] + (s[i] == '0');
      ps[1][i + 1] += ps[1][i] + (s[i] == '1');
      ps[2][i + 1] += ps[2][i] + (s[i] == '?');
    }
    B res = true;
    for (I i = 0; i + k <= n; i++) {
      const auto a_cnt = ps[0][i + k] - ps[0][i];
      const auto b_cnt = ps[1][i + k] - ps[1][i];
      const auto c_cnt = ps[2][i + k] - ps[2][i];
      if (abs(a_cnt - b_cnt) > c_cnt)
        res = false;
    }
    if (res)
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}