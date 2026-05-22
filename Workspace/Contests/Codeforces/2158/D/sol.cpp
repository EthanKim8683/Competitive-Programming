#pragma GCC optimize("Ofast,unroll-loops")
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

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string S;
    cin >> S;

    string T;
    cin >> T;

    auto clear = [&](string S) -> vc<pii> {
      vc<pii> rv;

      bool ok = false;
      rep(i, 0, sz(S) - 1) { ok = ok or S[i] == S[i + 1]; }
      if (!ok) {
        int l = 1 + sz(S) % 2, r = sz(S);
        rv.eb(l, r);
        rep(i, l, r) { S[i] ^= 1; }
      }

      int l, r;
      for (int i = 0, j = 0; i < sz(S); i = j) {
        for (; j < sz(S) and S[j] == S[i]; j++);
        if (j - i >= 2) {
          l = i;
          r = j;
          break;
        }
      }

      char c = S[l];
      while (0 < l or r < sz(S)) {
        rv.eb(l, r);
        for (; l > 0 and S[l - 1] != c; l--);
        for (; r < sz(S) and S[r] != c; r++);
        c ^= 1;
      }
      if (c == '1') {
        rv.eb(0, sz(S));
      }
      return rv;
    };

    auto ops1 = clear(S), ops2 = clear(T);
    reverse(all(ops2));

    vc<pii> ans;
    ans.insert(ans.end(), all(ops1));
    ans.insert(ans.end(), all(ops2));

    cout << sz(ans) << '\n';
    for (auto [l, r] : ans) {
      cout << l + 1 << ' ' << r << '\n';
    }
  }
}
