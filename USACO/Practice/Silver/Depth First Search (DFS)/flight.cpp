#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
 
using namespace std;

using U = unsigned;
using B = bool;
 
vector<U> tos[100000];
vector<U> froms[100000];
B visited[100000];
 
void dfs_to(U i) {
  visited[i] = true;
  auto& to = tos[i];
  for (const auto o : to)
    if (!visited[o])
      dfs_to(o);
}
 
void dfs_from(U i) {
  visited[i] = true;
  auto& from = froms[i];
  for (const auto o : from)
    if (!visited[o])
      dfs_from(o);
}
 
int main(void) {
#if defined(ETHANKIM8683)
  freopen("flight.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, m;
  cin >> n >> m;
  while (m--) {
    U a, b;
    cin >> a >> b;
    a--;
    b--;
    tos[a].push_back(b);
    froms[b].push_back(a);
  }
  dfs_to(0);
  for (U i = n; i--;) {
    if (!visited[i]) {
      printf("NO\n%u %u\n", 1, i + 1);
      return 0;
    }
  }
  memset(visited, false, n * sizeof(B));
  dfs_from(0);
  for (U i = n; i--;) {
    if (!visited[i]) {
      printf("NO\n%u %u\n", i + 1, 1);
      return 0;
    }
  }
  printf("YES\n");
  return 0;
}