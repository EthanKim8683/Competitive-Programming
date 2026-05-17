#include <vector>
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

const int LOGN = 60;
const int SQRTN = 1e6;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vc<vi> divisors(LOGN + 1);
  rep(i, 1, LOGN + 1) {
    for (int j = i; j <= LOGN; j += i) {
      divisors[j].pb(i);
    }
  }

  vi special;
  rep(i, 0, SQRTN + 1) { special.pb(i * (i + 1)); }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    int ans = 0;
    for (int i = 2; i * i * i <= N; i++) {
      vi pows = {1};
      for (int j = N; j != 0; j /= i) {
        pows.pb(pows.back() * i);
      }
      int n = sz(pows) - 1;
      for (auto e : divisors[n]) {
        if (e < 2) continue;
        int r = (pows[e] - 1) / (i - 1);
        rep(j, 0, n / e) {
          if (N / pows[j * e] % pows[e] % r != 0) goto SKIP;
        }
        ans += 1;
      SKIP:;
      }
    }
    for (int i = 1; i * (i + 1) * (i + 1) + i * (i + 1) + i <= N; i++) {
      if ((N - i) % i != 0) continue;
      int y = (N - i) / i, x = lower_bound(all(special), y) - special.begin();
      if (x * (x + 1) != y or x <= i) continue;
      ans += 1;
    }
    for (int i = 1; i * (i + 1) + i <= N; i++) {
      if ((N - i) % i != 0) continue;
      if ((N - i) / i <= i) continue;
      ans += 1;
    }
    cout << ans << '\n';
  }
}
