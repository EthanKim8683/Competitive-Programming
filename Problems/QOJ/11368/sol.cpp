#ifndef U
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

const int LOGV = 60;
const int INF = 2e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, K;
  cin >> N >> K;

  vi V(N);
  for (auto &e : V) cin >> e;

  auto trim = [&](vi V) -> vi {
    vi rv;
    for (auto e : V) {
      if (e == 0) continue;
      rv.pb(e);
    }
    return rv;
  };

  auto brute = [&](vi V) -> vi {
    sort(all(V));
    rep(i, 0, sz(V) - 1) { V[i + 1] -= V[i]; }
    return trim(V);
  };

  int k = 0;
  for (; k < K and sz(V) > LOGV; k++) {
    V = brute(V);
  }

  auto skip = [&](vi V, int k) -> vi {
    if (k == 0) return V;

    auto binom = [&](int n, int k) -> int {
      __int128 rv = 1;
      rep(i, n - k + 1, n + 1) { rv *= i; }
      rep(i, 1, k + 1) { rv /= i; }
      return rv;
    };

    sort(all(V));
    auto rv = V;
    rep(i, 0, sz(V)) {
      rep(j, i + 1, sz(V)) {
        int sign = (j - i) % 2 == 0 ? 1 : -1;
        rv[j] += V[i] * binom(k - 1 + j - i, j - i) * sign;
      }
    }
    return rv;
  };

  auto safe = [&](vi V) -> int {
    int d = INF;
    rep(i, 0, sz(V) - 1) {
      if (V[i] == 0) continue;
      chmin(d, V[i + 1] / V[i]);
    }
    if (d == INF) return INF;

    auto check = [&](vi V) -> bool {
      bool ok = true;
      rep(i, 0, sz(V) - 1) { ok = ok and V[i] <= V[i + 1]; }
      return ok;
    };
    int l = 0, r = d;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      check(skip(V, m)) ? l = m : r = m - 1;
    }
    return l + 1;
  };

  while (k < K) {
    int dk = min(safe(V), K - k);
    V = skip(V, dk);
    k += dk;
  }

  rep(i, 0, N - sz(V)) { cout << "0 "; }
  for (auto e : V) {
    cout << e << ' ';
  }
  cout << '\n';
}
