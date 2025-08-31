#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 BASE = 6969;
const i64 MOD = (1ll << 31) - 1;
const int INF = 2e9 + 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector A(N, vector<int>(M));
  vector<int> W(N);
  for (int i = 0; i < N; i++) {
    for (auto &e : A[i]) {
      cin >> e;
    }
    sort(A[i].begin(), A[i].end());
    cin >> W[i];
  }

  vector<int> order(N);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int a, int b) { return W[a] < W[b]; });

  vector<int> index(N);
  for (int i = 0; i < N; i++) {
    index[order[i]] = i;
  }

  vector hashes(N, vector<i64>(1 << M));
  vector<i64> keys;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < (1 << M); j++) {
      i64 hash = 0;
      for (int k = j; k != 0; k -= k & -k) {
        int l = __lg(k & -k);
        hash = (hash * BASE + A[i][l]) % MOD;
      }
      hashes[i][j] = hash;
      keys.push_back(hash * N + index[i]);
    }
  }
  sort(keys.begin(), keys.end());

  int ans = INF;
  for (int i = 0; i < N; i++) {
    vector<array<vector<i64>::iterator, 2>> ranges(1 << M);
    for (int j = 0; j < (1 << M); j++) {
      ranges[j] = {lower_bound(keys.begin(), keys.end(), hashes[i][j] * N),
                   upper_bound(keys.begin(), keys.end(), hashes[i][j] * N + N)};
    }

    auto count = [&](int n) -> int {
      int rv = 0;
      for (int j = 0; j < (1 << M); j++) {
        auto [l, r] = ranges[j];
        rv += (__builtin_popcount(j) % 2 == 0 ? 1 : -1) *
              (upper_bound(l, r, hashes[i][j] * N + n) - l);
      }
      return rv;
    };

    int l = 0, r = index[i];
    while (l < r) {
      int m = l + (r - l) / 2;
      count(m) > 0 ? r = m : l = m + 1;
    }
    if (l < index[i]) {
      ans = min(ans, W[i] + W[order[l]]);
    }
  }
  cout << (ans == INF ? -1 : ans);
}
