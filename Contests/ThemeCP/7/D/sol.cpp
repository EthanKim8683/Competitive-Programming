#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"
#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;
using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#if 0 and defined(ETHANKIM8683)
  int N = 60;

  vector<pair<int, int>> queries(N);
  for (auto &[t, x] : queries) {
    static mt19937 rng(time(nullptr));
    t = rng() % 3 + 1;
    if (t == 1) {
      x = rng() % (int) 2e5 + 1;
    }
    if (t == 2) {
      x = rng() % 100 + 1;
    }
  }

  for (auto [t, x] : queries) {
    cout << t;
    if (t == 1 or t == 2) {
      cout << ' ' << x;
    }
    cout << '\n';
  }
#else
  int N;
  cin >> N;

  vector<pair<int, int>> queries(N);
  for (auto &[t, x] : queries) {
    cin >> t;
    if (t == 1 or t == 2) {
      cin >> x;
    }
  }
#endif

  int X = 2e5;
  vector<mint> by_health(3 * X + 1, 0);
  fenwick_tree<i64> ft(N + 1);
  int accum = 0, r = 0;
  for (int q = 0; q < N; q++) {
    auto [t, x] = queries[q];

    if (t == 1) {
      if (accum >= X) {
        ft.add(r, x);
        ft.add(r + 1, -x);
        r++;
        continue;
      }

      if (accum > 0) {
        by_health[accum + x]++;
      }
    }

    if (t == 2) {
      if (accum >= X) {
        ft.add(0, -x);
        ft.add(r, x);
        accum += x;
        accum = min(accum, 3 * X);
        continue;
      }

      if (accum == 0) {
        mint f = 1;
        for (int q_ = q - 1; q_ >= 0; q_--) {
          auto [t_, x_] = queries[q_];
          if (t_ == 1) {
            by_health[x_] += f;
          }
          if (t_ == 3) {
            f *= 2;
          }
        }
      }

      accum += x;
    }

    if (t == 3) {
      if (accum >= X) {
        continue;
      }

      if (accum > 0) {
        for (int i = 2 * X; i >= 0; i--) {
          by_health[i + accum] += by_health[i];
        }
      }

      accum *= 2;
    }
  }

  if (accum == 0) {
    mint f = 1;
    for (int q = N - 1; q >= 0; q--) {
      auto [t, x] = queries[q];
      if (t == 1) {
        by_health[x] += f;
      }
      if (t == 3) {
        f *= 2;
      }
    }
  }

  mint ans = 0;
  for (int i = accum + 1; i <= 3 * X; i++) {
    ans += by_health[i];
  }
  for (int i = 0; i < r; i++) {
    if (ft.sum(0, i + 1) > 0) {
      ans++;
    }
  }
  cout << ans.val() << '\n';

#ifdef ETHANKIM8683
  vector<i64> pigs;
  accum = 0;
  for (auto [t, x] : queries) {
    if (t == 1) {
      pigs.push_back(accum + x);
    }
    if (t == 2) {
      accum += x;
    }
    if (t == 3) {
      for (int i = pigs.size() - 1; i >= 0; i--) {
        pigs.push_back(pigs[i] + accum);
      }
      accum *= 2;
    }
  }
  mint ans_ = 0;
  for (auto e : pigs) {
    if (e - accum > 0) {
      ans_++;
    }
  }
  cout << (ans == ans_ ? "ok" : "wa") << " (" << ans_.val() << ")\n";
#endif
}
