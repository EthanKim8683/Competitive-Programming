#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

using I = int;

queue<pair<I, I>> que;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I w, m;
  cin >> w >> m;
  que.push({m, 0});
  while (!que.empty()) {
    const auto [val, dep] = que.front();
    que.pop();
    if (val == 1) {
      printf("YES\n");
      return 0;
    }
    if (dep == 100)
      break;
    if ((val + 1) % w == 0)
      que.push({(val + 1) / w, dep + 1});
    if ((val - 1) % w == 0)
      que.push({(val - 1) / w, dep + 1});
    if (val % w == 0)
      que.push({val / w, dep + 1});
  }
  printf("NO\n");
  return 0;
}