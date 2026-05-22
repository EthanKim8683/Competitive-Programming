#pragma GCC optimize("Ofast,unroll-loops")
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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    vi A(N);
    for (auto &e : A) cin >> e;

    vc<tuple<int, int, int>> queries(Q);
    for (auto &[t, v1, v2] : queries) {
      cin >> t;
      if (t == 1) {
        cin >> v1 >> v2;
        v1--;
      } else {
        cin >> v1;
      }
    }

    auto case1 = [&]() -> bool {
      for (auto [t, v1, v2] : queries) {
        if (t == 1) {
          int i = v1, x = v2;
          A[i] = x;
        } else {
          int X = v1, ps = 0;
          map<int, int> S;
          S[0] = 0;
          pii ans = {-1, -1};
          rep(i, 0, N) {
            ps += A[i];
            if (S.contains(ps - X)) {
              ans = {S[ps - X], i + 1};
            }
            S[ps] = i + 1;
          }
          if (ans == pii{-1, -1}) {
            cout << "NO\n";
          } else {
            auto [l, r] = ans;
            cout << "YES\n";
            cout << l + 1 << ' ' << r << '\n';
          }
        }
      }
      return true;
    };

    auto case3 = [&]() -> bool {
      bool ok = true;
      for (auto e : A) {
        ok = ok and 0 <= e and e <= 2;
      }
      for (auto [t, v1, v2] : queries) {
        if (t != 1) continue;
        ok = ok and 0 <= v1 and v1 <= 2;
      }
    };

    case3() || case1();
  }
}
