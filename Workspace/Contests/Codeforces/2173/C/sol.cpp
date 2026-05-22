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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    set<int> S(all(A)), T = S, P;
    bool ok = true;
    while (sz(T) > 0) {
      int p = *T.begin();
      T.erase(p);
      P.insert(p);

      for (int i = p; i <= K; i += p) {
        if (!S.contains(i)) {
          ok = false;
          goto SKIP;
        }
        if (T.contains(i)) {
          T.erase(i);
        }
      }
    }
  SKIP:
    if (!ok) {
      cout << -1 << '\n';
      continue;
    }

    cout << sz(P) << '\n';
    for (auto e : P) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
