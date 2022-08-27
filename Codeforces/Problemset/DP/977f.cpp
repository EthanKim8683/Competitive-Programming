#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

using I = int;

const I N = 2e5;

I a_arr[N];
vector<I> cpss;
vector<I> vals[N];
pair<I, I> dp[N];
I ress[N];

I cps(I i) {
  return lower_bound(cpss.begin(), cpss.end(), i) - cpss.begin();
}

I exp(I i) {
  return cpss[i];
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(dp, n, pair<I, I>{1, -1});
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < n; i++)
    cpss.push_back(a_arr[i]);
  sort(cpss.begin(), cpss.end());
  cpss.erase(unique(cpss.begin(), cpss.end()), cpss.end());
  for (I i = n - 1; i >= 0; i--)
    vals[cps(a_arr[i])].push_back(i);
  for (I i = 0; i < n; i++) {
    const auto a = a_arr[i];
    vals[cps(a)].pop_back();
    const auto b = cps(a + 1);
    if (exp(b) == a + 1 && !vals[b].empty()) {
      const auto j = vals[b].back();
      if (dp[i].first + 1 > dp[j].first)
        dp[j] = {dp[i].first + 1, i};
    }
  }
  I len = 0;
  I ind = 0;
  for (I i = 0; i < n; i++) {
    if (dp[i].first > len) {
      len = dp[i].first;
      ind = i;
    }
  }
  for (I i = len - 1; i >= 0; i--) {
    ress[i] = ind;
    ind = dp[ind].second;
  }
  printf("%i\n", len);
  for (I i = 0; i < len; i++)
    printf("%i ", ress[i] + 1);
  return 0;
}