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

const int K = 9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // brute??

  vi pows(K + 1);
  pows[0] = 1;
  rep(i, 1, K + 1) { pows[i] = pows[i - 1] * 10; }

  vc<pii> pows2;
  for (int i = 1;; i *= 2) {
    if (i > pows[K]) break;
    pows2.eb(i, pows[sz(to_string(i))]);
  }

  set<int> good;
  auto dfs = [&](auto self, int x) -> void {
    if (good.contains(x)) return;
    good.insert(x);
    for (auto [x2, b] : pows2) {
      int x3 = x * b + x2;
      if (x3 > pows[K]) break;
      self(self, x3);
    }
  };
  for (auto [x, b] : pows2) {
    dfs(dfs, x);
  }
  vi good2(all(good));

  int N;
  cin >> N;
  N--;

  cout << good2[N] << '\n';
}
