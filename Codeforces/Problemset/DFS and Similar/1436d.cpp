#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

vector<I> adjs[200000];
I citizens[200000];
Lli subtree_citizens[200000];
I subtree_leaves[200000];
Lli result = 0;

void dfs1(I a) {
  const auto& adj = adjs[a];
  Lli c = citizens[a];
  I l = !adj.size();
  for (const auto b : adj) {
    dfs1(b);
    c += subtree_citizens[b];
    l += subtree_leaves[b];
  }
  subtree_citizens[a] = c;
  subtree_leaves[a] = l;
  if (l == 1)
    result = max(result, c);
}

void dfs2(I a, I move = 0) {
  const auto c = subtree_citizens[a] + move;
  const auto l = subtree_leaves[a];
  Lli e = max(result, (c + l - 1) / l);
  result = e;
  const Lli t = citizens[a] + move;
  for (const auto b : adjs[a]) {
    const auto c = subtree_citizens[b];
    const auto l = subtree_leaves[b];
    const Lli move = min(t, c - e * l);
    if (move >= 0)
      dfs2(b, move);
  }
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("1436d.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I b = 1; b < n; b++) {
    I a;
    cin >> a;
    adjs[a - 1].push_back(b);
  }
  for (I i = 0; i < n; i++)
    cin >> citizens[i];
  dfs1(0);
  dfs2(0);
  printf("%lli\n", result);
  return 0;
}