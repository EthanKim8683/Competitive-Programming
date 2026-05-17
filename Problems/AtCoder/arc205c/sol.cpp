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

  vc<pii> ops(N);
  for (auto &[s, t] : ops) {
    cin >> s >> t;
  }

  vi order(N);
  iota(all(order), 0);
  sort(all(order), [&](int a, int b) -> bool { return ops[a] < ops[b]; });

  bool ok = true;
  rep(i, 1, N) { ok = ok and ops[order[i - 1]].sd < ops[order[i]].sd; }
  if (!ok) {
    cout << "No\n";
    exit(0);
  }

  vi ans;
  for (auto e : order) {
    auto [s, t] = ops[e];
    if (t >= s) continue;
    ans.pb(e);
  }
  reverse(all(order));
  for (auto e : order) {
    auto [s, t] = ops[e];
    if (t < s) continue;
    ans.pb(e);
  }

  cout << "Yes\n";
  for (auto e : ans) {
    cout << e + 1 << ' ';
  }
  cout << '\n';
}
