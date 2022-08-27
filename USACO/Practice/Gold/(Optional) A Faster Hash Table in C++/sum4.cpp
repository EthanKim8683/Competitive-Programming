#include <iostream>
#include <cstdio>
#include <tuple>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using I = int;
using Lli = long long int;

const I N = 1000;

I a_arr[N];
gp_hash_table<Lli, pair<I, I>> viss;
vector<pair<Lli, I>> rigs[N];
vector<pair<Lli, I>> lefs[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, x;
  cin >> n >> x;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < n; i++) {
    for (I j = i + 1; j < n; j++) {
      Lli sum = (Lli) a_arr[i] + a_arr[j];
      lefs[i].push_back({sum, j});
      rigs[j].push_back({sum, i});
    }
  }
  for (I i = 0; i < n; i++) {
    for (const auto [sum, j] : lefs[i]) {
      const auto it = viss.find(x - sum);
      if (it != viss.end()) {
        const auto [k, l] = it->second;
        printf("%i %i %i %i\n", i + 1, j + 1, k + 1, l + 1);
        return 0;
      }
    }
    for (const auto [sum, j] : rigs[i])
      viss.insert({sum, {i, j}});
  }
  printf("IMPOSSIBLE\n");
  return 0;
}