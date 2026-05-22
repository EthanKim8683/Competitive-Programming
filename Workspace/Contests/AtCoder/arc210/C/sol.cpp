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

const int LOGA = 9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // 10 coins of type i -> 1 coin of type i + 1
  //
  // if there are not enough coins of type i + 1 for everyone, upgrade enough
  // coins of type i
  //
  // give at most 10 - 1 coins of each type i to each person
  //
  // if we can't give at least 10 coins of type i to each person, trying to
  // upgrade to coins of type i + 1 will give, in value, at least 10 coins of
  // type i
  //
  // so, if A[i] >= (ceil((A[i + 1] + 1) / M) * M - A[i + 1]) * 10, it is always
  // optimal to upgrade

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vi A(N);
    for (auto &e : A) cin >> e;
    A.resize(N + LOGA, 0);

    vi carry(N + LOGA, 0);
    rep(i, 0, N + LOGA - 1) {
      carry[i] = A[i] / 10;
      A[i + 1] += carry[i];
      A[i] -= carry[i] * 10;
    }
    for (int i = N + LOGA - 2; i >= 0; i--) {
      int delta = min(A[i + 1] - A[i + 1] / M * M, carry[i]);
      A[i + 1] -= delta;
      A[i] += delta * 10;
    }

    string ans = string(N + LOGA, '0');
    rep(i, 0, N + LOGA) { ans[i] = (char) (A[i] / M + '0'); }
    while (sz(ans) > 1 and ans.back() == '0') {
      ans.pop_back();
    }
    reverse(all(ans));
    cout << ans << '\n';
  }
}
