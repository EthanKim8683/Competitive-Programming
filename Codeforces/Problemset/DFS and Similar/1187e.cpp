#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

vector<I> adjs[N];
I n;

tuple<I, Lli, Lli> dfs(I a, I p = -1) {
  I cnt = 1;
  Lli in = 0;
  Lli out = 0;
  for (const auto b : adjs[a]) {
    if (b != p) {
      const auto [b_cnt, b_in, b_out] = dfs(b, a);
      cnt += b_cnt;
      in += b_in;
      if (b_out - b_in - b_cnt >= out)
        out = b_out - b_in - b_cnt;
    }
  }
  in += cnt;
  out += in + n - cnt;
  return {cnt, in, out};
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("1187e.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = n; --i;) {
    I u, v;
    cin >> u >> v;
    u--;
    v--;
    adjs[u].emplace_back(v);
    adjs[v].emplace_back(u);
  }
  printf("%lli\n", get<2>(dfs(0)));
  return 0;
}