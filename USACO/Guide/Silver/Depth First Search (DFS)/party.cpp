#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

using U = unsigned;
using B = bool;

pair<U, U> pairs[5000];
B adjs[100][100];
B visited[100];
U p;

U dfs(U a) {
  if (visited[a])
    return 0;
  visited[a] = true;
  U sum = 1;
  auto& a_adjs = adjs[a];
  for (U b = p; b--;)
    if (a_adjs[b])
      sum += dfs(b);
  return sum;
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("party.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  while (true) {
    U c;
    cin >> p >> c;
    if (!p && !c)
      break;
    for (U i = p; i--;)
      memset(adjs[i], false, p * sizeof(B));
    for (U i = c; i--;) {
      auto& [a, b] = pairs[i];
      cin >> a >> b;
      adjs[a][b] = true;
      adjs[b][a] = true;
    }
    B result = true;
    for (U i = c; i--;) {
      const auto [a, b] = pairs[i];
      adjs[a][b] = false;
      adjs[a][b] = false;
      memset(visited, false, p * sizeof(B));
      if (dfs(a) != p) {
        result = false;
        break;
      }
      adjs[a][b] = true;
      adjs[b][a] = true;
    }
    if (result)
      printf("NO\n");
    else
      printf("YES\n");
  }
  return 0;
}

// #include <iostream>
// #include <cstdio>
// #include <cstring>
// #include <vector>

// using namespace std;

// using U = unsigned;
// using B = bool;

// vector<U> adjs[100];
// B visited[100];

// B dfs(U a, U p) {
//   if (visited[a])
//     return false;
//   visited[a] = true;
//   B leaf = true;
//   for (const auto b : adjs[a]) {
//     if (b != p) {
//       if (dfs(b, a))
//         return true;
//       leaf = false;
//     }
//   }
//   return leaf;
// }

// int main(void) {
// #if defined(ETHANKIM8683)
//   freopen("party.in", "r", stdin);
// #endif // defined(ETHANKIM8683)
//   cin.tie(0)->sync_with_stdio(0);
//   while (true) {
//     U p, c;
//     cin >> p >> c;
//     if (!p && !c)
//       break;
//     for (U i = p; i--;)
//       adjs[i].clear();
//     memset(visited, false, p * sizeof(B));
//     while (c--) {
//       U a, b;
//       cin >> a >> b;
//       adjs[a].push_back(b);
//       adjs[b].push_back(a);
//     }
//     if (adjs[0].size() == 1 || dfs(0, 0))
//       printf("YES\n");
//     else
//       printf("NO\n");
//   }
//   return 0;
// }