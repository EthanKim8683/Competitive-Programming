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

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(N);
    for (auto &e : B) cin >> e;

    vi C(N);
    for (auto &e : C) cin >> e;

    auto count_deltas = [&](vi A, vi B) -> int {
      int rv = 0;
      for (int i = 0; i < N; i++) {
        bool ok = true;
        for (int j = 0; j < N; j++) {
          ok = ok and A[j] < B[(j + i) % N];
        }
        if (ok) {
          rv++;
        }
      }
      return rv;
    };
    cout << N * count_deltas(A, B) * count_deltas(B, C) << '\n';
  }
}
