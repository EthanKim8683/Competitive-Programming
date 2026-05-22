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

  // one allele from each parent

  int N;
  cin >> N;

  vc<tuple<int, int, char>> creatures(N);
  for (auto &[p1, p2, c] : creatures) {
    cin >> p1 >> p2 >> c;
    p1--, p2--;
  }

  string ans = "-1";
  rep(i, 0, 1 << N) {
    vc<char> recessive(N);
    vc<string> colors(N);
    for (int j = N - 1; j >= 0; j--) {
      auto [p1, p2, c] = creatures[j];
      chmax(recessive[j], c);
      if (p1 < 0) continue;
      if (i >> j & 1) {
        swap(p1, p2);
      }
      chmax(recessive[p1], c);
      chmax(recessive[p2], recessive[j]);
    }
    bool ok = true;
    rep(j, 0, N) {
      auto [p1, p2, c1] = creatures[j];
      char c2 = recessive[j];
      if (p1 < 0) {
        colors[j] = {c1, c2};
        continue;
      }
      if (i >> j & 1) {
        swap(p1, p2);
      }
      ok = ok and find(all(colors[p1]), c1) != colors[p1].end();
      if (colors[p2][0] < recessive[j]) {
        c2 = colors[p2][1];
      } else {
        c2 = colors[p2][0];
      }
      colors[j] = {c1, c2};
    }
    if (!ok) continue;
    string s = "";
    for (auto r : colors) {
      for (auto e : r) {
        s += e;
      }
    }
    if (ans == "-1" or s < ans) {
      ans = s;
    }
  }
  rep(i, 0, sz(ans) / 2) { cout << ans.substr(2 * i, 2) << '\n'; }
}
