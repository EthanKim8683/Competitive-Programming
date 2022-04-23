#include <iostream>
#include <cstdio>
#include <unordered_set>

using namespace std;

using U = unsigned;

U as[1000];
U dp[1000];
unordered_set<U> adjs[1000];

U dfs(U a, U p) {
  const auto& adj = adjs[a];
  if (adj.find(p) != adj.end())
    return 0;
  auto& result = dp[a];
  if (result)
    return result;
  for (const auto b : adjs[a])
    result = max(result, dfs(b, a));
  result++;
  return result;
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("463d.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, k;
  cin >> n >> k;
  while (k--) {
    for (U i = 0; i < n; i++) {
      U a;
      cin >> a;
      as[i] = a - 1;
    }
    for (U a = 0; a + 1 < n; a++) {
      auto& adj = adjs[as[a]];
      for (U b = a + 1; b < n; b++)
        adj.insert(as[b]);
    }
  }
  U result = 0;
  for (U i = n; i--;)
    result = max(result, dfs(i, -1));
  printf("%u\n", result);
  return 0;
}