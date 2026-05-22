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
    int N;
    cin >> N;

    string S;
    cin >> S;

    int sum = 1;
    rep(i, 0, N - 1) {
      if (S[i] == S[i + 1]) continue;
      sum += 1;
    }

    int ans = sum;
    rep(i, 0, N) {
      if (S[i] != S[(i + 1) % N]) {
        sum -= 1;
      }
      if (S[(i + N - 1) % N] != S[(i + N) % N]) {
        sum += 1;
      }
      chmax(ans, sum);
    }
    cout << ans << '\n';
  }
}
