#ifndef L
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
    int N;
    cin >> N;

    string S;
    cin >> S;

    auto contains = [&](string s, string t) -> bool {
      for (int i = 0; i + t.size() <= s.size(); i++) {
        if (s.substr(i, t.size()) == t) return true;
      }
      return false;
    };
    if (contains(S, "2026")) {
      cout << "0\n";
    } else if (!contains(S, "2025")) {
      cout << "0\n";
    } else {
      cout << "1\n";
    }
  }
}
