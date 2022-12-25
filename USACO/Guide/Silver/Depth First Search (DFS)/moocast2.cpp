#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

using U = unsigned;
using I = int;
using B = bool;

pair<U, U> cows[1000];
B visited[1000];
U n;
U x;

U dfs(U a_x, U a_y) {
  U sum = 1;
  for (U b = n; b--;) {
    if (!visited[b]) {
      const auto [b_x, b_y] = cows[b];
      const I dx = a_x - b_x;
      const I dy = a_y - b_y;
      if (dx * dx + dy * dy <= x) {
        visited[b] = true;
        sum += dfs(b_x, b_y);
      }
    }
  }
  return sum;
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("moocast2.in", "r", stdin);
#else
  freopen("moocast.in", "r", stdin);
  freopen("moocast.out", "w", stdout);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (U i = n; i--;) {
    auto& [x, y] = cows[i];
    cin >> x >> y;
  }
  const auto [a_x, a_y] = cows[0];
  visited[0] = true;
  U l = 0;
  U r = 1250000000;
  while (l < r) {
    memset(visited + 1, false, (n - 1) * sizeof(B));
    x = l + (r - l) / 2;
    if (dfs(a_x, a_y) == n)
      r = x;
    else
      l = x + 1;
  }
  printf("%u\n", r);
  return 0;
}