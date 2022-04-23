#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;

U adjs[200000];
U days[200000];

U dfs(U a, U root, U day) {
  const auto b = adjs[a];
  if (b != root)
    day = dfs(b, root, day + 1);
  days[a] = day;
  return day;
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("1249b2.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U q;
  cin >> q;
  while (q--) {
    U n;
    cin >> n;
    fill_n(days, n, 0);
    for (U i = 0; i < n; i++) {
      U a;
      cin >> a;
      adjs[i] = a - 1;
    }
    for (U a = 0; a < n; a++) {
      if (days[a])
        printf("%u ", days[a]);
      else
        printf("%u ", dfs(a, a, 1));
    }
    printf("\n");
  }
  return 0;
}