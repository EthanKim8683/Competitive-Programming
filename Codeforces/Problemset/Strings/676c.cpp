#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using C = char;

const I N = 100000;

vector<I> inds[2];
C s[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  cin >> s;
  for (I i = 0; i < n; i++)
    inds[s[i] - 'a'].push_back(i);
  I res = 0;
  I a_cnt = 0;
  I b_cnt = 0;
  for (I i = 0; i < n; i++) {
    if (s[i] == 'a') {
      res = max(res, b_cnt);
      a_cnt++;
      b_cnt = 0;
    } else {
      res = max(res, a_cnt);
      b_cnt++;
      a_cnt = 0;
    }
  }
  res = max(res, a_cnt);
  res = max(res, b_cnt);
  for (I i = 0; i < 2; i++) {
    for (I j = 0; j < inds[i].size(); j++) {
      const auto beg = j - 1 < 0 ? 0 : inds[i][j - 1] + 1;
      const auto end = j + k >= inds[i].size() ? n - 1 : inds[i][j + k] - 1;
      res = max(res, end - beg + 1);
    }
  }
  printf("%i\n", res);
  return 0;
}