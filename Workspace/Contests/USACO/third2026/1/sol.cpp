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

struct FT {
  vi s;
  FT(int n) : s(n) {}
  void update(int pos, int dif) {
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  int query(int pos) {
    int res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
  int lower_bound(int sum) {
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    }
    return pos;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // number of inversions

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi P(N);
    for (auto &e : P) {
      cin >> e;
      e--;
    }

    FT ft(N);
    int count = 0;
    rep(i, 0, N) {
      count += i - ft.query(P[i] + 1);
      ft.update(P[i], 1);
    }

    vi ps(2 * N + 2, 0), ps2(2 * N + 2, 0);
    rep(i, 0, N) {
      ps2[N - i] += P[i];
      ps2[N - i + N] += -(N - P[i]);
      ps[N - i + 1] += -1;
      ps[N - i + P[i] + 1] += 2;
      ps[N - i + N + 1] += -1;
    }
    rep(i, 0, 2 * N) {
      ps[i + 1] += ps[i];
      ps2[i] += ps[i];
      ps2[i + 1] += ps2[i];
    }

    vi ans;
    rep(i, 0, N) {
      if (2 * count <= ps2[i] + ps2[i + N]) {
        ans.pb(i);
      }
      count += 2 * P[N - 1 - i] - (N - 1);
    }
    cout << sz(ans) << '\n';
    rep(i, 0, sz(ans)) {
      if (i > 0) {
        cout << ' ';
      }
      cout << ans[i];
    }
    cout << '\n';
  }
}
