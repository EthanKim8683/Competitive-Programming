#pragma GCC optimize("trapv")
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
typedef vector<int> vi;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M, A, C, X0;
  cin >> N >> M >> A >> C >> X0;

  vi S(N);
  int X = X0;
  for (int i = 0; i < N; i++) {
    X = (A * X + C) % M;
    S[i] = X;
  }

  int ans = 0;
  for (auto e : S) {
    bool found = false;
    int l = 0, r = N - 1;
    while (l <= r) {
      int m = (l + r) / 2;
      if (S[m] < e) {
        l = m + 1;
      } else if (S[m] > e) {
        r = m - 1;
      } else {
        found = true;
        break;
      }
    }
    if (found) {
      ans++;
    }
  }
  cout << ans;
}