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

const int MAXN = 25;
const int MOD = 998244353;
const int K = 2;
const __int128 INF = 1e38;
const string NIL = "";

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // pick a size and offset
  //
  // could brute force on last two digits

  vi pows(K + 1);
  pows[0] = 1;
  rep(i, 1, K + 1) { pows[i] = pows[i - 1] * 10; }

  int T;
  cin >> T;

  while (T--) {
    string S;
    cin >> S;

    auto ceil_div = [&](int x, int y) -> int {
      int rv = x / y;
      if (x % y != 0 and (x < 0) == (y < 0)) {
        rv += 1;
      }
      return rv;
    };

    auto stolll = [&](string s) -> __int128 {
      __int128 rv = 0;
      for (auto e : s) {
        rv = rv * 10 + e - '0';
      }
      return rv;
    };

    auto merge = [&](string a, string b) -> string {
      if (sz(a) != sz(b)) return NIL;
      string rv(sz(a), '?');
      rep(i, 0, sz(a)) {
        if (a[i] == '?' and b[i] == '?') {
          rv[i] = '?';
        } else if (a[i] == '?') {
          rv[i] = b[i];
        } else if (b[i] == '?') {
          rv[i] = a[i];
        } else {
          if (a[i] != b[i]) return NIL;
          rv[i] = a[i];
        }
      }
      return rv;
    };

    auto substr = [&](int l, int r) -> string {
      int l2 = max(l, 0ll), r2 = min(r, sz(S));
      return string(l2 - l, '?') + S.substr(l2, r2 - l2) + string(r - r2, '?');
    };

    auto tail = [&](int x, int n) -> string {
      string s = to_string(x);
      while (sz(s) < n) {
        s = "0" + s;
      }
      return s;
    };

    auto find_infix = [&](int l, int r) -> string {
      int n = r - l;
      string rv = NIL;
      rep(i, 0, pows[K]) {
        bool ok = true;
        string s = string(n - K, '?');
        rep(j, -ceil_div(l, n), ceil_div(sz(S) - l, n)) {
          string t = substr(l + j * n, r + j * n);
          ok = ok and (s = merge(s, t.substr(0, n - K))) != NIL;
          ok = ok and 0 <= i + j and i + j < pows[K];
          ok = ok and merge(t.substr(n - K), tail(i + j, K)) != NIL;
        }
        if (!ok) continue;

        if (s[0] == '0') continue;
        if (s[0] == '?') {
          s[0] = '1';
        }
        for (auto &e : s) {
          if (e != '?') continue;
          e = '0';
        }
        s += tail(i, K);

        if (rv == NIL or s < rv) {
          rv = s;
        }
      }
      return rv;
    };

    auto count_lt = [&](__int128 x) -> __int128 {
      __int128 lb = 0, rv = 0;
      for (__int128 ub = 1, n = 0; lb < x; lb = ub, ub *= 10, n += 1) {
        rv += (min(ub, x) - lb) * n;
      }
      return rv;
    };

    __int128 ans = INF;
    string T = "";
    rep(i, 1, pows[K] + 1) { T += to_string(i); }
    rep(i, 0, sz(T) - sz(S)) {
      if (merge(T.substr(i, sz(S)), S) == NIL) continue;
      ans = i;
      break;
    }
    rep(n, K + 1, sz(S) + 1) {
      rep(i, 0, sz(S)) {
        string infix = find_infix(i, i + n);
        if (infix == NIL) continue;
        chmin(ans, count_lt(stolll(infix)) - i);
      }
    }
    cout << (int) ((ans + 1) % MOD) << '\n';
  }
}
