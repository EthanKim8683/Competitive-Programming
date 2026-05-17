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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // query also gives amax in the range
  //
  // find max?
  //
  // try all multiples of max?
  //
  // find good prefix sums
  //
  // factor <= N/K

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    auto query = [&](int l, int x) -> int {
      cout << "? " << l + 1 << ' ' << x << endl;
      int p;
      cin >> p;
      if (p == -1) {
        exit(0);
      }
      return p;
    };

    auto answer = [&](int m) -> void {
      cout << "! " << m << endl;
      int v;
      cin >> v;
      if (v == -1) {
        exit(0);
      }
    };

    int amax = N;
    while (amax >= 1 and query(0, N * amax) == N + 1) {
      amax -= 1;
    }
    if (amax == 0) {
      answer(-1);
      continue;
    }

    int ans = -1;
    rep(i, 1, N / K + 1) {
      int l = 0, x = i * amax;
      rep(j, 0, K) {
        if (l == N) goto BAD;
        int r = query(l, x);
        if (r == N + 1) goto BAD;
        l = r;
      }
      if (l != N) goto BAD;
      ans = x;
    BAD:;
    }
    answer(ans);
  }
}
