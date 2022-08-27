#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

using I = int;
using C = char;

const I N = 1000;
const I M = 1000;

C cels[N][M];
I begs[M];
stack<pair<I, I>> stk;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < n; i++)
    cin >> cels[i];
  I res = 0;
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < m; j++)
      if (cels[i][j] == '*')
        begs[j] = i + 1;
    for (I j = 0; j < m; j++) {
      const I cur = i + 1 - begs[j];
      I ind = j;
      while (!stk.empty() && stk.top().first >= cur) {
        const auto [len, beg] = stk.top();
        stk.pop();
        ind = beg;
        res = max(res, len * (j - beg));
      }
      stk.push({cur, ind});
    }
    while (!stk.empty()) {
      const auto [len, beg] = stk.top();
      stk.pop();
      res = max(res, len * (m - beg));
    }
  }
  printf("%i\n", res);
  return 0;
}