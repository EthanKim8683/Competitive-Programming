#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define float long double
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef pair<float, float> pff;
typedef vc<int> vi;

const int MOD = 1e9 + 7;

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 12:01
  // thinking done: 12:15
  // target impl time: 20min
  // initial impl done: 12:46

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int N, K;
  if (argc > 1) {
    N = 1000;
    K = rng() % N;
  } else {
    cin >> N >> K;
  }

  vi B(N);
  if (argc > 1) {
    vi A(N);
    for (auto &e : A) {
      int p0 = 1, p1 = 50, p2 = 50;

      int x = rng() % (p0 + p1 + p2);
      if (x < p0) {
        e = 0;
      } else if (x < p0 + p1) {
        e = 1;
      } else {
        e = 2;
      }
    }

    rep(i, 0, N) {
      if (i + K >= N) {
        B[i] = 0;
      } else {
        B[i] = 1;
        rep(j, 0, K + 1) { (B[i] *= A[i + j]) %= MOD; }
      }
    }
  } else {
    for (auto &e : B) cin >> e;
  }

  vi pows(N + 1);
  pows[0] = 1;
  rep(i, 1, N + 1) { pows[i] = pows[i - 1] * 2 % MOD; }

  auto impossible = [&]() -> void {
    assert(!(argc > 1));
    cout << -1;
    exit(0);
  };

  auto answer = [&](vi A) -> void {
    vi ps0(N + 1), ps2(N + 1);
    int s0 = 0, s2 = 0;
    rep(i, 0, N + 1) {
      ps0[i] = s0;
      ps2[i] = s2;

      if (i < N) {
        if (A[i] == 0) {
          s0++;
        } else if (A[i] == 2) {
          s2++;
        }
      }
    }

    rep(i, 0, N) {
      int b;
      if (i + K >= N) {
        b = 0;
      } else if (ps0[i + K + 1] - ps0[i] > 0) {
        b = 0;
      } else {
        b = pows[ps2[i + K + 1] - ps2[i]];
      }
      if (B[i] != b) {
        impossible();
      }
    }

    for (auto e : A) {
      cout << e << ' ';
    }
    cout << '\n';
    exit(0);
  };

  vc<pii> ranges;
  rep(i, 0, N) {
    if (B[i] == 0) continue;
    if (ranges.empty() or ranges.back().sd != i) {
      ranges.eb(i, i + 1);
    }
    ranges.back().sd = i + 1;
  }

  if (ranges.empty()) {
    answer(vi(N, 0));
  }

  rep(i, 0, sz(ranges) - 1) {
    if (ranges[i + 1].fs - ranges[i].sd < K + 1) {
      impossible();
    }
  }
  if (N - ranges.back().sd < K) {
    impossible();
  }

  map<int, int> logs;
  rep(i, 0, N + 1) { logs[pows[i]] = i; }

  vi logB(N);
  rep(i, 0, N) {
    if (B[i] == 0) {
      logB[i] = -1;
    } else {
      if (!logs.contains(B[i])) {
        impossible();
      }
      logB[i] = logs[B[i]];
    }
  }

  vi ans(N, -1);
  for (auto [l, r] : ranges) {
    int base = 0;
    vi margin;
    rep(i, l, l + K + 1) {
      if (i < r - 1) {
        int d = 0, d_min = 0, d_max = 0;
        for (int j = i; j < r - 1; j += K + 1) {
          d += logB[j + 1] - logB[j];
          d_min = min(d_min, d);
          d_max = max(d_max, d);
        }
        if (d_max - d_min > 1) {
          impossible();
        }

        if (d_min == -1) {
          ans[i] = 1;
          base++;
        } else {
          ans[i] = 0;
        }

        if (d_min == 0 and d_max == 0) {
          margin.pb(i);
        }
      } else {
        ans[i] = 0;
        margin.pb(i);
      }
    }

    if (logB[l] < base or base + sz(margin) < logB[l]) {
      impossible();
    }

    rep(i, 0, logB[l] - base) { ans[margin[i]]++; }

    rep(i, l, min(l + K + 1, r)) {
      for (int j = i; j < r - 1; j += K + 1) {
        ans[j + K + 1] = ans[j] + logB[j + 1] - logB[j];
      }
    }
  }

  for (auto &e : ans) {
    if (e == -1) {
      e = 0;
    } else {
      e = pows[e];
    }
  }
  answer(ans);
}
