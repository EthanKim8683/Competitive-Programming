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
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(N);
    for (auto &e : B) cin >> e;

    vi C(N);
    for (auto &e : C) cin >> e;

    int count1 = 0, count2 = 0;
    rep(i, 0, N) {
      bool ok1 = true, ok2 = true;
      rep(j, 0, N) {
        ok1 = ok1 and A[j] < B[(j + i) % N];
        ok2 = ok2 and B[j] < C[(j + i) % N];
      }
      if (ok1) {
        count1 += 1;
      }
      if (ok2) {
        count2 += 1;
      }
    }
    cout << N * count1 * count2 << '\n';
  }
}
