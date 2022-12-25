#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

using U = unsigned;
using B = bool;

vector<U> adjs[20];
B visited[20];
B cycle[20];

B dfs(U a, U r) {
  if (visited[a])
    return false;
  visited[a] = true;
  for (const auto b : adjs[a]) {
    if (b == r || dfs(b, r)) {
      cycle[b] = true;
      return true;
    }
  }
  return false;
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("rank.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, k;
  cin >> n >> k;
  while (k--) {
    U a, b, a_s, b_s;
    cin >> a >> b >> a_s >> b_s;
    if (a_s > b_s)
      adjs[b - 1].push_back(a - 1);
    else
      adjs[a - 1].push_back(b - 1);
  }
  for (U r = n; r--;) {
    memset(visited, false, n * sizeof(B));
    dfs(r, r);
  }
  U result = 0;
  for (U i = n; i--;)
    result += cycle[i];
  printf("%u\n", result);
  return 0;
}

// #include <iostream>
// #include <cstdio>
// #include <vector>

// using namespace std;

// using U = unsigned;
// using I = int;
// using B = bool;

// vector<U> adjs[20];
// B visited[20];
// U depths[20];
// U depth = 0;
// U result = 0;

// U dfs(U a) {
//   auto& a_depth = depths[a];
//   if (a_depth)
//     return a_depth;
//   if (visited[a])
//     return -1;
//   visited[a] = true;
//   depth++;
//   a_depth = depth;
//   U b_depth = -1;
//   for (const auto b : adjs[a])
//     b_depth = min(b_depth, dfs(b));
//   result += b_depth <= depth;
//   depth--;
//   a_depth = 0;
//   return b_depth;
// }

// int main(void) {
// #if defined(ETHANKIM8683)
//   freopen("rank.in", "r", stdin);
// #endif // defined(ETHANKIM8683)
//   cin.tie(0)->sync_with_stdio(0);
//   U n, k;
//   cin >> n >> k;
//   while (k--) {
//     U a, b, a_s, b_s;
//     cin >> a >> b >> a_s >> b_s;
//     if (a_s > b_s)
//       adjs[b - 1].push_back(a - 1);
//     else
//       adjs[a - 1].push_back(b - 1);
//   }
//   for (U i = n; i--;)
//     dfs(i);
//   printf("%u\n", result);
//   return 0;
// }