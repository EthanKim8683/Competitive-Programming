#ifndef L
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

const int K = 1000;
const int MAXA = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 8:07
  // thinking done: 8:17
  // target impl time: 30 min
  // initial impl done:

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int N, Q;
  if (argc > 1) {
    N = 2e5;
    Q = 2e5;
  } else {
    cin >> N >> Q;
  }

  vi A(N);
  if (argc > 1) {
    for (auto &e : A) {
      e = rng() % MAXA + 1;
    }
  } else {
    for (auto &e : A) cin >> e;
  }

  int M = (N + K - 1) / K;

  auto get_range = [&](int i) -> pii {
    return {i * K, min((i + 1) * K, sz(A))};
  };

  vi pm(N), sm(N), lazy(M, 0);
  vc<vi> pm_ps(M), sm_ps(M);
  rep(i, 0, M) {
    auto [l, r] = get_range(i);
    pm_ps[i] = sm_ps[i] = vi(r - l + 1, 0);
  }
  auto apply_lazy = [&](int i) -> void {
    auto [l, r] = get_range(i);
    rep(j, l, r) { A[j] += lazy[i]; }
    lazy[i] = 0;
  };
  auto refresh = [&](int i) -> void {
    auto [l, r] = get_range(i);

    rep(j, l, r) { pm[j] = sm[j] = A[j]; }

    for (int j = l; j + 1 < r; j++) {
      chmax(pm[j + 1], pm[j]);
    }
    for (int j = r - 1; j - 1 >= l; j--) {
      chmax(sm[j - 1], sm[j]);
    }

    pm_ps[i][0] = sm_ps[i][0] = 0;
    rep(j, l, r) {
      pm_ps[i][j - l + 1] = pm_ps[i][j - l] + pm[j];
      sm_ps[i][j - l + 1] = sm_ps[i][j - l] + sm[j];
    }
  };
  auto get_pm = [&](int i, int j) -> int { return pm[j] + lazy[i]; };
  auto get_sm = [&](int i, int j) -> int { return sm[j] + lazy[i]; };
  auto find_first_greater = [&](int i, int x) -> int {
    auto [l, r] = get_range(i);
    return upper_bound(pm.begin() + l, pm.begin() + r, x - lazy[i]) -
           pm.begin();
  };
  auto find_last_greater = [&](int i, int x) -> int {
    auto [l, r] = get_range(i);
    return lower_bound(sm.begin() + l, sm.begin() + r, x - lazy[i],
                       greater<int>()) -
           sm.begin() - 1;
  };
  auto get_pm_sum = [&](int i, int l, int r) -> int {
    int l2 = get_range(i).fs;
    return (pm_ps[i][r - l2] - pm_ps[i][l - l2]) + lazy[i] * (r - l);
  };
  auto get_sm_sum = [&](int i, int l, int r) -> int {
    int l2 = get_range(i).fs;
    return (sm_ps[i][r - l2] - sm_ps[i][l - l2]) + lazy[i] * (r - l);
  };
  rep(i, 0, M) { refresh(i); }

  int sum = accumulate(all(A), 0ll);
  auto solve = [&]() -> int {
    pii best = {0, -1};
    rep(i, 0, M) {
      int r = get_range(i).sd;
      chmax(best, pii{get_pm(i, r - 1), i});
    }
    int m = best.sd;

    int rv = 0;

    int pm2 = 0;
    rep(i, 0, m) {
      auto [l, r] = get_range(i);
      int j = find_first_greater(i, pm2);
      rv += (j - l) * pm2 + get_pm_sum(i, j, r);
      chmax(pm2, get_pm(i, r - 1));
    }

    int sm2 = 0;
    for (int i = M - 1; i > m; i--) {
      auto [l, r] = get_range(i);
      int j = find_last_greater(i, sm2) + 1;
      rv += get_sm_sum(i, l, j) + (r - j) * sm2;
      chmax(sm2, get_sm(i, l));
    }

    auto [l, r] = get_range(m);
    rep(i, l, r) { rv += min(max(pm2, get_pm(m, i)), max(sm2, get_sm(m, i))); }

    rv -= sum;

    return rv;
  };

  if (argc > 1) {
  } else {
    cout << solve() << '\n';
  }

  while (Q--) {
    int l, r;
    if (argc > 1) {
      do {
        l = rng() % (N + 1);
        r = rng() % (N + 1);
        if (l > r) {
          swap(l, r);
        }
      } while (l == r);
    } else {
      cin >> l >> r;
    }
    l--;

    sum += r - l;

    int l2 = l / K, r2 = (r - 1) / K;
    if (l2 == r2) {
      apply_lazy(l2);
      rep(i, l, r) { A[i]++; }
      refresh(l2);
    } else {
      rep(i, l2 + 1, r2) { lazy[i]++; }

      apply_lazy(l2);
      rep(i, l, (l2 + 1) * K) { A[i]++; }
      refresh(l2);

      apply_lazy(r2);
      rep(i, r2 * K, r) { A[i]++; }
      refresh(r2);
    }

    if (argc > 1) {
    } else {
      cout << solve() << '\n';
    }
  }
}
