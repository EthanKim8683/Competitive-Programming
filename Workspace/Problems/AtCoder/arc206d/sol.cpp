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

    if (K == 0) {
      if (N >= 8) {
        cout << "3 4 " << N << ' ' << N - 1 << " 2 1 ";
        rep(i, 4, N - 2) { cout << i + 1 << ' '; }
        cout << '\n';
      } else {
        cout << "-1\n";
      }
      continue;
    }

    if (K == 1) {
      if (N >= 5) {
        cout << "2 " << N << " 3 1 ";
        rep(i, 3, N - 1) { cout << i + 1 << ' '; }
        cout << '\n';
      } else if (N == 1) {
        cout << "1\n";
      } else {
        cout << "-1\n";
      }
      continue;
    }

    rep(i, 0, K) { cout << N - K + i + 1 << ' '; }
    rep(i, K, N) { cout << N - 1 - i + 1 << ' '; }
    cout << '\n';
  }
}
