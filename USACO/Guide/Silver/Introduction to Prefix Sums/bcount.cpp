#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

U ps[3][100001] = { 0 };

int main(void) {
  freopen("bcount.in", "r", stdin);
#if !defined(ETHANKIM8683)
  freopen("bcount.out", "w", stdout);
#endif // !defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, q;
  cin >> n >> q;
  for (U i = 1; i <= n; i++) {
    U t;
    cin >> t;
    ps[t - 1][i] = 1;
  }
  auto& [h_ps, g_ps, j_ps] = ps;
  U h_sum = 0;
  U g_sum = 0;
  U j_sum = 0;
  for (U i = 1; i <= n; i++) {
    h_ps[i] = h_sum += h_ps[i];
    g_ps[i] = g_sum += g_ps[i];
    j_ps[i] = j_sum += j_ps[i];
  }
  while (q--) {
    U a, b;
    cin >> a >> b;
    a--;
    const auto h_sum = h_ps[b] - h_ps[a];
    const auto g_sum = g_ps[b] - g_ps[a];
    const auto j_sum = j_ps[b] - j_ps[a];
    printf("%u %u %u\n", h_sum, g_sum, j_sum);
  }
  return 0;
}