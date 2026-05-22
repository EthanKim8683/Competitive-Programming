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

const int MAXA = 8;
const int K = 3;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 6:03
  // thinking done: 6:13
  // target impl time: 20 min
  // initial impl done: 7:00

  vi pows(MAXA + 1);
  pows[0] = 1;
  rep(i, 1, MAXA + 1) { pows[i] = pows[i - 1] * K; }

  auto encode = [&](vi &counts) -> int {
    int rv = 0;
    rep(i, 0, MAXA) { rv += counts[i] % K * pows[i]; }
    return rv;
  };

  vc<vi> limits;
  vi counts(MAXA, 0);
  auto dfs = [&](auto self, int i) -> void {
    if (i + K > MAXA) {
      limits.pb(counts);
      return;
    }

    rep(j, 0, K) {
      rep(k, i, i + K) { counts[k] += j; }
      self(self, i + 1);
      rep(k, i, i + K) { counts[k] -= j; }
    }
  };
  dfs(dfs, 0);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int T;
  if (argc > 1) {
    T = 1;
  } else {
    cin >> T;
  }

  while (T--) {
    int N;
    if (argc > 1) {
      N = 1e5;
    } else {
      cin >> N;
    }

    vi A(N);
    if (argc > 1) {
      for (auto &e : A) {
        e = rng() % MAXA;
      }
    } else {
      for (auto &e : A) {
        cin >> e;
        e--;
      }
    }

    vi counts(MAXA, 0);
    vc<vi> indices(MAXA), indices2(pows[MAXA]);
    indices2[encode(counts)].pb(0);
    int ans = 0;
    rep(i, 0, N) {
      counts[A[i]]++;
      indices[A[i]].pb(i);
      indices2[encode(counts)].pb(i + 1);

      for (auto &limit : limits) {
        int i2 = i + 1;
        rep(j, 0, MAXA) {
          if (limit[j] == 0) continue;
          if (limit[j] > sz(indices[j])) {
            i2 = 0;
            break;
          }
          chmin(i2, indices[j].end()[-limit[j]] + 1);
        }

        if (i2 > 0) {
          auto counts2 = counts;
          rep(j, 0, MAXA) { counts2[j] -= limit[j]; }
          int j = encode(counts2);

          ans += lower_bound(all(indices2[j]), i2) - indices2[j].begin();
        }
      }
    }
    cout << ans << '\n';
  }
}
