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

  int N;
  cin >> N;

  string S;
  cin >> S;

  auto sum = [&](int i, int n) -> int {
    return count(S.begin() + i, S.begin() + i + n, '1');
  };

  bool ok = true;
  rep(i, 0, N - 1) { ok = ok and sum(i, 2) < 2; }
  rep(i, 0, N - 2) { ok = ok and sum(i, 3) > 0; }
  ok = ok and sum(0, 2) > 0;
  ok = ok and sum(N - 2, 2) > 0;
  cout << (ok ? "Yes" : "No") << '\n';
}
