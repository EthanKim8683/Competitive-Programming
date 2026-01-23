#include <bits/stdc++.h>

using namespace std;

const int LOGA = 20;
const int INF = 1e9;

vector<int> A;
struct xor_basis {
  int r;
  vector<pair<int, int>> b;

  xor_basis() : r(0), b(LOGA, {0, -1}) {}

  bool insert(int e) {
    int x = A[e];
    for (int i = LOGA - 1; i >= 0; i--) {
      if (~x >> i & 1) continue;
      if (b[i].first == 0) {
        for (int j = 0; j < i; j++) {
          if (~x >> j & 1) continue;
          x ^= b[j].first;
        }
        b[i] = {x, e};
        r++;
        for (int j = i + 1; j < LOGA; j++) {
          if (~b[j].first >> i & 1) continue;
          b[j].first ^= x;
        }
        return true;
      }
      x ^= b[i].first;
    }
    return false;
  }

  void clear() {
    r = 0;
    fill(b.begin(), b.end(), pair{0, -1});
  }

  vector<int> basis() {
    vector<int> rv;
    for (int i = 0; i < LOGA; i++) {
      if (b[i].first == 0) continue;
      rv.push_back(b[i].second);
    }
    sort(rv.begin(), rv.end());
    return rv;
  }

  int size() { return r; }

  int order_of_key(int x) {
    int x2 = 0, j = r - 1, rv = 0;
    for (int i = LOGA - 1; i >= 0; i--) {
      int x3 = b[i].first;
      if (x3 == 0) continue;
      if ((x2 ^ x3) <= x) {
        x2 ^= x3;
        rv += 1 << j;
      }
      j--;
    }
    return rv;
  }

  int find_by_order(int k) {
    int k2 = 0, j = r - 1, rv = 0;
    for (int i = LOGA - 1; i >= 0; i--) {
      int x3 = b[i].first;
      if (x3 == 0) continue;
      if (k2 + (1 << j) <= k) {
        k2 += 1 << j;
        rv ^= x3;
      }
      j--;
    }
    return rv;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // any prefix subset
  // find the earliest independent vectors
  // find the range possible after each independent vector
  // segtree?

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    A.resize(N);
    for (auto &e : A) cin >> e;

    vector<pair<int, int>> queries(Q);
    for (auto &[l, r] : queries) {
      cin >> l >> r;
      l--;
    }

    vector<vector<int>> by_l(N);
    for (int i = 0; i < Q; i++) {
      auto [l, r] = queries[i];
      by_l[l].push_back(i);
    }

    vector<bool> ans(Q);
    xor_basis xb;
    map<int, pair<int, int>> dp;
    for (int i = N - 1; i >= 0; i--) {
      auto basis = xb.basis();
      int j = i, k = 0;
      xb.clear();
      xb.insert(j);
      dp.clear();
      dp[j] = {k, xb.size()};
      for (auto j2 : basis) {
        if (k != INF) {
          k += (j2 - 1) - j;
          if (k >= (1 << xb.size())) {
            k = INF;
          }
        }

        int x;
        if (k != INF) {
          x = xb.find_by_order(k);
        }

        xb.insert(j2);

        if (k != INF) {
          k = xb.order_of_key(x) + 1;
          if (k >= (1 << xb.size())) {
            k = INF;
          }
        }

        j = j2;
        dp[j] = {k, xb.size()};
      }

      for (auto e : by_l[i]) {
        auto [l, r] = queries[e];

        auto [j, data] = *prev(dp.lower_bound(r));
        auto [k, size] = data;
        k += (r - 1) - j;

        ans[e] = k < (1 << size);
      }
    }

    for (auto e : ans) {
      cout << (e ? "YES" : "NO") << '\n';
    }
  }
}
