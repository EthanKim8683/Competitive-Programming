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

  int N, M;
  cin >> N >> M;

  vi F(N);
  for (auto &e : F) {
    cin >> e;
    e--;
  }

  vi counts(M, 0);
  for (auto e : F) {
    counts[e] += 1;
  }

  bool ans1 = true, ans2 = true;
  for (auto e : counts) {
    ans1 = ans1 and e <= 1;
    ans2 = ans2 and e >= 1;
  }
  cout << (ans1 ? "Yes" : "No") << '\n';
  cout << (ans2 ? "Yes" : "No") << '\n';
}
