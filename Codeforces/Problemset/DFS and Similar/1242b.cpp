#include <iostream>
#include <cstdio>
#include <set>
#include <unordered_set>

using namespace std;

using U = unsigned;

unordered_set<U> adjs[100000];
set<U> unvisited;

void dfs(U a) {
  auto& adj = adjs[a];
  auto it = unvisited.begin();
  while (it != unvisited.end()) {
    const auto b = *it;
    if (adj.find(b) == adj.end()) {
      unvisited.erase(it);
      dfs(b);
      it = unvisited.upper_bound(b);
    } else
      it++;
  }
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("1242b.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, m;
  cin >> n >> m;
  for (U i = n; i--;)
    unvisited.insert(i);
  while (m--) {
    U a, b;
    cin >> a >> b;
    a--;
    b--;
    adjs[a].insert(b);
    adjs[b].insert(a);
  }
  U result = 0;
  auto it = unvisited.begin();
  while (it != unvisited.end()) {
    const auto a = *it;
    unvisited.erase(it);
    dfs(a);
    it = unvisited.upper_bound(a);
    result++;
  }
  printf("%u\n", result - 1);
  return 0;
}