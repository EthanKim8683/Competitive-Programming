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

  int N, X, K;
  cin >> N >> X >> K;

  vi A(N);
  for (auto &e : A) cin >> e;

  vc<bool> discount(N, false);
  for (int i = X; i < N; i += X + 1) {
    discount[i] = true;
  }

  multiset<int> s;
  int ans = 0;
  for (int i = N - 1, j = N - 1; i >= 0; i--) {
    for (; j >= 0 and j + K >= i; j--) {
      s.insert(A[j]);
    }

    int e;
    if (discount[i]) {
      e = *s.rbegin();
      ans += e / 2;
    } else {
      e = *s.begin();
    }
    s.erase(s.find(e));
  }
  cout << ans << '\n';
}
