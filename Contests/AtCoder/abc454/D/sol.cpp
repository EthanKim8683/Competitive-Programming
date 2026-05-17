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

  int T;
  cin >> T;

  while (T--) {
    string A;
    cin >> A;

    string B;
    cin >> B;

    auto key = [&](string s) -> string {
      vc<pair<char, int>> segments;
      for (int i = 0, j; i < sz(s); i = j) {
        for (j = i; j < sz(s) and s[j] == s[i]; j++);
        segments.eb(s[i], j - i);
      }
      rep(i, 1, sz(segments) - 1) {
        if (segments[i - 1].fs == '(' and segments[i].fs == 'x' and
            segments[i].sd == 2 and segments[i + 1].fs == ')') {
          int d = min(segments[i - 1].sd, segments[i + 1].sd);
          segments[i - 1].sd -= d;
          segments[i + 1].sd -= d;
        }
      }
      string rv = "";
      for (auto [c, n] : segments) {
        rv += string(n, c);
      }
      return rv;
    };
    cout << (key(A) == key(B) ? "Yes" : "No") << '\n';
  }
}
