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

  // bitset

  int N, M, L;
  cin >> N >> M >> L;

  vi A(N);
  for (auto &e : A) cin >> e;

  vi B(M);
  for (auto &e : B) cin >> e;

  vi C(L);
  for (auto &e : C) cin >> e;

  vc<pii> cc;
  for (auto e : A) {
    cc.eb(e, 0);
  }
  for (auto e : B) {
    cc.eb(e, 1);
  }
  for (auto e : C) {
    cc.eb(e, 2);
  }
  sort(all(cc));

  vi pows(sz(cc) + 1);
  pows[0] = 1;
  rep(i, 0, sz(cc)) { pows[i + 1] = pows[i] * 3; }

  auto get = [&](int mask, int i) -> int { return mask / pows[i] % 3; };

  auto set = [&](int mask, int i, int x) -> int {
    return mask - get(mask, i) * pows[i] + x * pows[i];
  };

  int mask = 0;
  rep(i, 0, sz(cc)) { mask = set(mask, i, cc[i].sd); }

  vc dp(pows[sz(cc)], vi(2, -1));
  auto dfs = [&](auto self, int mask, int turn) -> int {
    if (dp[mask][turn] != -1) return dp[mask][turn];
    int rv = turn ^ 1;
    rep(i, 0, sz(cc)) {
      if (get(mask, i) != turn) continue;
      if (self(self, set(mask, i, 2), turn ^ 1) == turn) {
        rv = turn;
      }
      rep(j, 0, sz(cc)) {
        if (get(mask, j) != 2) continue;
        if (cc[j].fs >= cc[i].fs) continue;
        if (self(self, set(set(mask, i, 2), j, turn), turn ^ 1) == turn) {
          rv = turn;
        }
      }
    }
    return dp[mask][turn] = rv;
  };
  cout << (string[]) {"Takahashi", "Aoki"}[dfs(dfs, mask, 0)] << '\n';
}
