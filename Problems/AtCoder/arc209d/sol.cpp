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

  // each A[i] = -1 should satisfy one of the following after assignment:
  // - A[i] = 1
  // - A[A[i]] = 1, A[i] should be minimal among all A[A[i]] = 1
  //
  // if A[i] != -1 and A[A[i]] = -1,
  //   if A[i] < i,
  //     A[A[i]] = minimal i s.t. A[i] = 1
  //     basically if there doesn't exist an A[i] = 1 yet, for the next i s.t.
  //     A[i] = -1, set A[i] = 1
  //   else,
  //     A[A[i]] = 1

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) {
      cin >> e;
      if (e != -1) {
        e--;
      }
    }

    if (A[0] == -1) {
      A[0] = 0;
    }

    int j = N;
    rep(i, 0, N) {
      if (A[i] == -1) continue;
      if (A[i] == 0) {
        chmin(j, i);
      } else {
        if (A[A[i]] != -1) continue;
        if (A[i] < i) {
          if (j == N) {
            j = find(A.begin() + i, A.end(), -1) - A.begin();
          }
        } else {
          A[A[i]] = 0;
        }
      }
    }
    int n = count(all(A), -1);
    if (n == 1) {
      j = find(all(A), -1) - A.begin();
      pii best = {j, j};
      rep(i, 0, N) {
        if (i == j) continue;
        chmin(best, pii{A[i], i});
      }
      A[j] = best.sd;
    } else if (n > 1) {
      if (j == N) {
        j = 0;
        rep(i, 0, N) {
          if (A[i] != -1) continue;
          chmax(j, i);
        }
      }
      A[j] = 0;
      for (auto &e : A) {
        if (e != -1) continue;
        e = j;
      }
    }

    vi B(N);
    rep(i, 0, N) { B[i] = A[A[i]]; }

    for (auto e : B) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
