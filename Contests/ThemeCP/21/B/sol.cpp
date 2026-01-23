#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> S(N);
  for (auto &e : S) cin >> e;

  // they can only be applied at most once. I'm stupid
  //
  // make prefixes:
  //  - cost to make prefix
  //  - cost to sort the rest

  vector<int> order(N);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int a, int b) -> bool {
    return make_pair(S[a], a) < make_pair(S[b], b);
  });

  vector<int> ps(N + 1, 0);
  for (int i = 0; i < N; i++) {
    ps[i + 1] = ps[i] + (i != order[i]);
  }

  i64 ans = INF;
  int j = 0;
  for (int i = 0; i <= N; i++) {
    i64 cost = (i64) j * j;
    int l = i, r = N;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      ps[m] - ps[i] == 0 ? l = m : r = m - 1;
    }
    cost += (i64) (N - l) * (N - l);
    ans = min(ans, cost);
    if (i < N) {
      j = max(j, order[i] + 1);
    }
  }
  j = 0;
  for (int i = N; i >= 0; i--) {
    if (i < N) {
      j = max(j, N - order[i]);
    }
    i64 cost = (i64) j * j;
    int l = 0, r = i;
    while (l < r) {
      int m = l + (r - l) / 2;
      ps[i] - ps[m] == 0 ? r = m : l = m + 1;
    }
    cost += (i64) l * l;
    ans = min(ans, cost);
  }
  cout << ans;
}