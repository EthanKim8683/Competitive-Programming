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

  // same sum
  //
  // always possible?
  //
  // yes
  //
  // A[i] = C[i]+i
  //
  // A[i] = A[j]-1
  // C[i]+i = (C[j]+j)-1
  // C[i] = C[j]+(j-i)-1

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  vi B(N);
  for (auto &e : B) cin >> e;

  if (accumulate(all(A), 0ll) != accumulate(all(B), 0ll)) {
    cout << "No\n";
    exit(0);
  }

  if (N == 2) {
    if (A == B) {
      cout << "Yes\n0\n";
    } else if (B[0] == A[1] - 1 and B[1] == A[0] + 1) {
      cout << "Yes\n1\n1 2\n";
    } else {
      cout << "No\n";
    }
    exit(0);
  }

  vi C(N), D(N);
  rep(i, 0, N) {
    C[i] = A[i] - i;
    D[i] = B[i] - i;
  }

  vc<pii> ans;
  auto op = [&](int i, int j) -> void {
    assert(i < j);
    int d = (j - i) - 1;
    tie(C[i], C[j]) = pair{C[j] + d, C[i] - d};
    ans.eb(i, j);
  };

  rep(i, 0, N - 2) {
    while (C[i] < D[i]) {
      int d = min(N - 1 - i, D[i] - C[i] + 1);
      rep(j, 0, d) { op(i + j, i + (j + 1)); }
      op(i, i + d);
    }
    while (C[i] > D[i]) {
      int d = min(N - 1 - i, C[i] - D[i] + 1);
      op(i, i + d);
      rep(j, 0, d) { op((i + d) - (j + 1), (i + d) - j); }
    }
  }
  while (C[N - 2] < D[N - 2]) {
    op(N - 2, N - 1);
    op(N - 3, N - 2);
    op(N - 3, N - 1);
    op(N - 3, N - 2);
  }
  while (C[N - 2] > D[N - 2]) {
    op(N - 3, N - 2);
    op(N - 3, N - 1);
    op(N - 3, N - 2);
    op(N - 2, N - 1);
  }
  assert(C == D);

  cout << "Yes\n";
  cout << sz(ans) << '\n';
  for (auto [i, j] : ans) {
    cout << i + 1 << ' ' << j + 1 << '\n';
  }
}
