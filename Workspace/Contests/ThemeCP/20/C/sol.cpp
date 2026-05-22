#include <bits/stdc++.h>

#include "ethankim8683/data_structures.hpp"

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<i64> ps(N + 1);
  ps[0] = 0;
  for (int i = 0; i < N; i++) {
    ps[i + 1] = ps[i] + A[i];
  }

  ordered_set<pair<i64, int>> os;
  i64 ans = 0;
  for (int i = 0; i < ps.size(); i++) {
    ans += os.size() - os.order_of_key({ps[i], ps.size()});
    os.insert({ps[i], i});
  }

  sort(ps.begin() + 1, ps.end() - 1);
  if (!is_sorted(ps.begin(), ps.end())) {
    cout << -1;
  } else {
    cout << ans;
  }
}
