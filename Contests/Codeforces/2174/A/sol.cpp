#ifndef L
// #pragma GCC optimize("Ofast,unroll-loops")
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
    string S;
    cin >> S;

    string T;
    cin >> T;

    vi counts(26, 0);
    for (auto e : T) {
      counts[e - 'a']++;
    }

    vi mins(26, 0);
    for (auto e : S) {
      mins[e - 'a']++;
    }

    bool ok = true;
    rep(i, 0, 26) { ok = ok and counts[i] >= mins[i]; }
    if (!ok) {
      cout << "Impossible\n";
      continue;
    }

    string ans = "";
    int k = 0;
    rep(i, 0, sz(T)) {
      int l = k < sz(S) ? S[k] - 'a' : 26;
      bool found = false;
      rep(j, 0, l) {
        if (counts[j] > mins[j]) {
          ans += (char) (j + 'a');
          counts[j]--;
          found = true;
          break;
        }
      }
      if (!found) {
        ans += (char) (l + 'a');
        counts[l]--;
        mins[l]--;
        k++;
      }
    }
    cout << ans << '\n';
  }
}
