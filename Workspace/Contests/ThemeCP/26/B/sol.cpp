#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/string.hpp"
using namespace atcoder;

#include "ethankim8683/data_structures.hpp"
using namespace ethankim8683;

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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, L, R;
    cin >> N >> L >> R;

    string S;
    cin >> S;

    if (N == 1) {
      cout << "1\n";
      continue;
    }

    auto sa = suffix_array(S), la = lcp_array(S, sa);
    vi index(N);
    rep(i, 0, N) { index[sa[i]] = i; }
    using T = signed;
    auto op = [&](T a, T b) -> T { return min(a, b); };
    auto e = [&]() -> T { return INF; };
    sparse_table<T, op, e> st(la);
    auto lcp = [&](int i, int j) -> int {
      int l = index[i], r = index[j];
      if (l > r) {
        swap(l, r);
      }
      return st.prod(l, r);
    };

    vi memo(N + 1, -1), dp(N + 1);
    auto count = [&](int x) -> int {
      if (memo[x] != -1) return memo[x];
      fill(all(dp), -INF);
      dp[0] = 0;
      rep(i, 0, N) {
        chmax(dp[i + 1], dp[i]);
        if (lcp(0, i) >= x) {
          chmax(dp[i + x], dp[i] + 1);
        }
      }
      return memo[x] = dp[N];
    };
    vi ans(N + 1, 0);
    int l = 1;
    while (l <= N and l <= N / count(l)) {
      int r = N / count(l);
      while (l < r) {
        int m = l + (r - l + 1) / 2;
        count(m) == count(l) ? l = m : r = m - 1;
      }
      chmax(ans[count(l)], l);
      l += 1;
    }
    for (int i = N; i - 1 >= 0; i--) {
      chmax(ans[i - 1], ans[i]);
    }
    rep(i, L, R + 1) { cout << ans[i] << ' '; }
    cout << '\n';
  }
}
