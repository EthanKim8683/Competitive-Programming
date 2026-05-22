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

const int LOGA = 30;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // dp; ranges may merge but never split
  //
  // map of last occurrence of a bit w/ map of ending or-sum lengths
  //
  // could small-to-large merge

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  auto insert = [&](map<int, int> &m, pii x) -> void {
    auto it = m.upper_bound(x.fs);
    if (it != m.begin() and prev(it)->sd >= x.sd) return;
    for (auto it = m.lower_bound(x.fs); it != m.end(); it = m.erase(it)) {
      if (it->sd > x.sd) break;
    }
    m.insert(x);
  };
  auto merge = [&](map<int, int> &a, map<int, int> &b) -> void {
    if (sz(a) < sz(b)) {
      swap(a, b);
    }
    for (auto e : b) {
      insert(a, e);
    }
    b.clear();
  };
  map<int, pair<int, map<int, int>>> dp;
  dp.insert({0, {0, {{0, 0}}}});
  rep(i, 0, N) {
    map<int, int> dpi;
    for (auto it = dp.end(); it != dp.begin(); it--) {
      auto &[maskj, dpj] = prev(it)->sd;
      auto it2 = dpj.upper_bound(A[i] | maskj);
      if (it2 != dpj.begin()) {
        insert(dpi, {A[i] | maskj, prev(it2)->sd + 1});
      }
    }
    dp.insert({i + 1, {0, dpi}});
    for (auto it = prev(dp.end()); it != dp.begin();) {
      auto &[maskj, dpj] = prev(it)->sd;
      maskj |= A[i];
      if (maskj == it->sd.fs) {
        merge(it->sd.sd, dpj);
        dp.erase(prev(it));
      } else {
        it--;
      }
    }
  }
  cout << dp.rbegin()->sd.sd.rbegin()->sd << '\n';
}
