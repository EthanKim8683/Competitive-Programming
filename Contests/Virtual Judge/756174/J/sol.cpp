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
typedef vector<int> vi;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // int N = 50, K = 6;

  // int M1 = N / (K + 1), M2 = (N + K) / (K + 1);

  // vc dp(N + 1, vi(K + 2, 0));
  // dp[0][0] = 1;
  // rep(i, 0, N) {
  //   rep(j, 0, K + 1) {
  //     rep(k, max(M1 - 2 * (K + 1), 0ll), min(M2 + 2, N - i + 1)) {
  //       dp[i + k][j + 1] += dp[i][j];
  //     }
  //   }
  // }
  // cerr << dp[N][K + 1] << '\n';
  //=> 26418

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    string S;
    cin >> S;

    for (auto &e : S) {
      e -= '0';
    }

    vi chunks(N);
    rep(i, 0, N - 18 + 1) {
      chunks[i] = 0;
      rep(j, i, i + 18) { chunks[i] = chunks[i] * 10 + S[j]; }
    }

    auto get = [&](int l, int r) -> vi {
      vi rv;
      for (int i = r; i >= l; i -= 18) {
        if (i - 18 >= l) {
          rv.pb(chunks[i - 18]);
        } else {
          int chunk = 0;
          rep(j, l, i) { chunk = chunk * 10 + S[j]; }
          rv.pb(chunk);
        }
      }
      return rv;
    };

    int M1 = N / (K + 1), M2 = (N + K) / (K + 1);

    vc dp1(N + 1, vc<vi>(K + 2));
    dp1[0][0].pb(-1);
    rep(i, 0, N) {
      rep(j, 0, K + 1) {
        if (dp1[i][j].empty()) continue;
        rep(k, max(M1 - (K + 1) * 2, 0ll), min(M2 + 2, N - i + 1)) {
          dp1[i + k][j + 1].pb(i);
        }
      }
    }

    vc dp2(N + 1, vc<vc<vi>>(K + 2));
    dp2[0][0].pb({});
    auto dfs = [&](auto self, int i, int j) -> vc<vi> {
      if (!dp2[i][j].empty()) return dp2[i][j];
      for (auto k : dp1[i][j]) {
        for (auto split : self(self, k, j - 1)) {
          split.pb(i - k);
          dp2[i][j].pb(split);
        }
      }
      return dp2[i][j];
    };
    auto splits = dfs(dfs, N, K + 1);

    auto add = [&](vi A, vi B) -> vi {
      if (sz(B) > sz(A)) {
        swap(A, B);
      }

      int carry = 0;
      rep(i, 0, sz(A)) {
        if (i < sz(B)) {
          A[i] += B[i];
        }
        A[i] += carry;
        carry = 0;
        if (A[i] >= (int) 1e18) {
          A[i] -= (int) 1e18;
          carry = 1;
        }
      }
      if (carry != 0) {
        A.pb(carry);
      }
      return A;
    };

    auto less = [&](vi A, vi B) -> bool {
      reverse(all(A));
      reverse(all(B));
      return pair{sz(A), A} < pair{sz(B), B};
    };

    auto str = [&](vi X) -> string {
      string rv;
      for (auto e : X) {
        rep(i, 0, 18) {
          rv += e % 10 + '0';
          e /= 10;
        }
      }
      while (rv.size() > 0 and rv.back() == '0') {
        rv.pop_back();
      }
      reverse(all(rv));
      if (rv.empty()) {
        rv = "0";
      }
      return rv;
    };

    vi ans;
    for (auto split : splits) {
      vi sum;
      int i = 0;
      for (auto e : split) {
        sum = add(sum, get(i, i + e));
        i += e;
      }
      if (ans.empty() or less(sum, ans)) {
        ans = sum;
      }
    }
    cout << str(ans) << '\n';
  }
}