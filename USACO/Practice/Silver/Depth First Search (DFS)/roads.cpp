#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using U = unsigned;
using B = bool;

vector<U> adjs[100000];
B visited[100000];
U build[99999];

void dfs(U a) {
  if (visited[a])
    return;
  visited[a] = true;
  for (const auto b : adjs[a])
    dfs(b);
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("roads.in", "r", stdin);
#endif // defined(ETHANKIM8683)
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
  U k = 0;
  U a = n - 1;
  while (true) {
    dfs(a);
    while (a--)
      if (!visited[a])
        break;
    if (a == -1)
      break;
    build[k] = a;
    k++;
  }
  printf("%u\n", k);
  while (k--)
    printf("%u %u\n", n, build[k] + 1);
  return 0;
}