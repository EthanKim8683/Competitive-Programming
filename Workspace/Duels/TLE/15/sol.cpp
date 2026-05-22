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

const int MAXD = 1000;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vi K(N);
  for (auto &e : K) cin >> e;

  vc<pii> offers(M);
  for (auto &[d, t] : offers) {
    cin >> d >> t;
    d--, t--;
  }

  vc<set<int>> by_day(MAXD);
  for (auto [d, t] : offers) {
    by_day[d].insert(t);
  }

  auto check = [&](int x) -> bool {
    vi savings = K;
    int cost = 2 * accumulate(all(K), 0ll), save = 0;
    for (int i = x - 1; i >= 0; i--) {
      for (auto e : by_day[i]) {
        int delta = min(i + 1 - save, savings[e]);
        save += delta;
        cost -= delta;
        savings[e] = 0;
      }
      if (cost <= i + 1) return true;
      save -= 1;
      cost -= 1;
    }
    return false;
  };
  int l = 0, r = MAXD;
  while (l < r) {
    int m = l + (r - l) / 2;
    check(m) ? r = m : l = m + 1;
  }
  cout << l << '\n';
}
