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

  // if no two adjacent characters are equal, there are no bad substrings
  //
  // if no character appears > N/2 times, we can construct a string with no bad
  // substrings
  //
  // otherwise, we want to minimize the length of each chunk of the dominating
  // character
  //
  // count[dominator]/(count[others]+1)

  int T;
  cin >> T;

  while (T--) {
    string S;
    cin >> S;

    int N = sz(S);

    vi counts(26, 0);
    for (auto e : S) {
      counts[e - 'a'] += 1;
    }

    int d = -1;
    rep(i, 0, 26) {
      if (2 * counts[i] >= N) {
        d = i;
        break;
      }
    }
    vi ans;
    if (d == -1) {
      ans.resize(N);
      int k = 0;
      rep(i, 0, 26) {
        rep(j, 0, counts[i]) {
          ans[k] = i;
          k += 2;
          if (k >= N) {
            k = 1;
          }
        }
      }
    } else {
      vi delimiters;
      rep(i, 0, 26) {
        if (i == d) continue;
        rep(j, 0, counts[i]) { delimiters.pb(i); }
      }

      vi chunks;
      rep(i, 0, sz(delimiters) + 1) {
        int n = counts[d] / (sz(delimiters) + 1);
        if (i < counts[d] % (sz(delimiters) + 1)) {
          n += 1;
        }
        chunks.pb(n);
      }
      sort(all(chunks), [&](int a, int b) -> bool {
        auto key = [&](int x) -> int { return x % 2 == 0 ? 1 : 0; };
        return key(a) < key(b);
      });

      int f = -1;
      rep(i, 0, sz(chunks)) {
        if (chunks[i] % 2 != 0) continue;
        if (f == -1) {
          f = i;
        } else {
          chunks[f] += 1;
          chunks[i] -= 1;
          f = -1;
        }
      }

      rep(i, 0, sz(chunks)) {
        rep(j, 0, chunks[i]) { ans.pb(d); }
        if (i < sz(delimiters)) {
          ans.pb(delimiters[i]);
        }
      }
    }
    for (auto e : ans) {
      cout << (char) (e + 'a');
    }
    cout << '\n';
  }
}
