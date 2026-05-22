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

  // all strings have at least one non-RBS child
  //
  // if N-K is odd, Taro wins
  //
  // if K is odd, Taro wins

  int T;
  cin >> T;

  while (T--) {
    string S;
    cin >> S;

    int K;
    cin >> K;

    int N = sz(S);

    auto is_rbs = [&](string S) -> bool {
      int h = 0;
      for (auto e : S) {
        if (e == '(') {
          h += 1;
        } else {
          h -= 1;
        }
        if (h < 0) return false;
      }
      return h == 0;
    };

    auto is_alternating_rbs = [&](string S) -> bool {
      rep(i, 0, sz(S)) {
        if (S[i] != "()"[i % 2]) return false;
      }
      return true;
    };

    if ((N - K) % 2 == 1) {
      cout << "First";
    } else if (K % 2 == 1) {
      cout << "First";
    } else {
      int n = N;
      while (n > K) {
        if (!(S.substr((N - n) / 2, 2) == "((" and
              S.substr((N - n) / 2 + n - 2, 2) == "))"))
          break;
        n -= 2;
      }
      if (is_alternating_rbs(S.substr((N - n) / 2, n - K)) and
          is_rbs(S.substr((N - n) / 2 + n - K, K)) and
          is_rbs(S.substr((N - n) / 2, K)) and
          is_alternating_rbs(S.substr((N - n) / 2 + K, n - K))) {
        cout << "Second";
      } else {
        cout << "First";
      }
    }
    cout << '\n';
  }
}
