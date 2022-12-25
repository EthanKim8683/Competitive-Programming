#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

using U = unsigned;
using I = int;
using B = bool;

pair<pair<U, U>, U> cows[200];
B visited[200];
U n;

U dfs(U a_x, U a_y, U pp) {
  U sum = 1;
  for (U b = n; b--;) {
    if (!visited[b]) {
      const auto& cow = cows[b];
      const auto [b_x, b_y] = cow.first;
      const I dx = a_x - b_x;
      const I dy = a_y - b_y;
      if (dx * dx + dy * dy <= pp) {
        visited[b] = true;
        sum += dfs(b_x, b_y, cow.second);
      }
    }
  }
  return sum;
}

int main(void) {
  freopen("moocast.in", "r", stdin);
#if !defined(ETHANKIM8683)
  freopen("moocast.out", "w", stdout);
#endif // !defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (U i = n; i--;) {
    auto& cow = cows[i];
    auto& [x, y] = cow.first;
    U p;
    cin >> x >> y >> p;
    cow.second = p * p;
  }
  U result = 0;
  for (U i = n; i--;) {
    memset(visited, false, n * sizeof(B));
    visited[i] = true;
    auto& cow = cows[i];
    const auto [x, y] = cow.first;
    result = max(result, dfs(x, y, cow.second));
  }
  printf("%u\n", result);
  return 0;
}