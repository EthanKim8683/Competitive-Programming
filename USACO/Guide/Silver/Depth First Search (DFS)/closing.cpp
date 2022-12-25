#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

using U = unsigned;
using B = bool;

vector<U> adjs[3000];
B visited[3000];
B closed[3000];

U dfs(U a) {
  if (visited[a])
    return 0;
  visited[a] = true;
  U sum = 1;
  for (const auto b : adjs[a])
    sum += dfs(b);
  return sum;
}

int main(void) {
  freopen("closing.in", "r", stdin);
#if !defined(ETHANKIM8683)
  freopen("closing.out", "w", stdout);
#endif // !defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, m;
  cin >> n >> m;
  while (m--) {
    U a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  printf("%s\n", dfs(0) == n ? "YES" : "NO");
  U s = 0;
  for (U i = n; --i;) {
    U x;
    cin >> x;
    x--;
    closed[x] = true;
    memcpy(visited, closed, n);
    if (s == x) {
      s = n;
      while (closed[--s]);
    }
    printf("%s\n", dfs(s) == i ? "YES" : "NO");
  }
  return 0;
}