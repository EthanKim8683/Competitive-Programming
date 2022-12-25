#include <iostream>
#include <cstdio>
#include <set>
#include <unordered_set>
#include <algorithm>
 
using namespace std;
 
using U = unsigned;
 
unordered_set<U> adjs[200000];
set<U> unvisited;
U result[200000];
 
U dfs(U a) {
  auto& adj = adjs[a];
  U result = 1;
  auto it = unvisited.begin();
  while (it != unvisited.end()) {
    const auto b = *it;
    if (adj.find(b) == adj.end()) {
      unvisited.erase(it);
      result += dfs(b);
      it = unvisited.upper_bound(b);
    } else
      it++;
  }
  return result;
}
 
int main(void) {
#if defined(ETHANKIM8683)
  freopen("toss.in", "r", stdin);
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
  U k = 0;
  auto it = unvisited.begin();
  while (it != unvisited.end()) {
    const auto a = *it;
    unvisited.erase(it);
    result[k] = dfs(a);
    k++;
    it = unvisited.upper_bound(a);
  }
  sort(result, result + k);
  printf("%u\n", k);
  for (U i = 0; i < k; i++)
    printf("%u ", result[i]);
  return 0;
}