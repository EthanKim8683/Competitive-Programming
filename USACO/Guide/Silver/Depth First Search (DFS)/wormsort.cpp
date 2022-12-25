#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

using U = unsigned;
using B = bool;

vector<pair<U, U>> adjs[100000];
B unsorted[100000];
U widths[100000];
B visited[100000];
U m;
U t;

U dfs(U a) {
  if (visited[a])
    return 0;
  visited[a] = true;
  U sum = unsorted[a];
  for (const auto [w, b] : adjs[a])
    if (w >= t)
      sum += dfs(b);
  return sum;
}

int main(void) {
  freopen("wormsort.in", "r", stdin);
#if !defined(ETHANKIM8683)
  freopen("wormsort.out", "w", stdout);
#endif // !defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n >> m;
  U total = 0;
  U a;
  for (U i = 0; i < n; i++) {
    U p;
    cin >> p;
    p--;
    if (p != i) {
      a = i;
      unsorted[i] = true;
      total++;
    }
  }
  if (!total) {
    printf("-1\n");
    return 0;
  }
  for (U i = m; i--;) {
    U a, b, w;
    cin >> a >> b >> w;
    widths[i] = w;
    a--;
    b--;
    adjs[a].push_back({w, b});
    adjs[b].push_back({w, a});
  }
  sort(widths, widths + m);
  U l = 0;
  U r = m - 1;
  while (l < r) {
    memset(visited, false, n * sizeof(B));
    const U m = l + (r - l + 1) / 2;
    t = widths[m];
    const U x = dfs(a);
    if (x == total)
      l = m;
    else
      r = m - 1;
  }
  printf("%u\n", widths[l]);
  return 0;
}