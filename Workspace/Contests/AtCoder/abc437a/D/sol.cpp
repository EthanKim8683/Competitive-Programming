#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<int> B(M);
  for (auto &e : B) cin >> e;

  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  int n = 0;
  mint lt = 0, ge = accumulate(A.begin(), A.end(), 0ll), ans = 0;
  for (int i = 0; i < M; i++) {
    while (n < N and A[n] < B[i]) {
      lt += A[n];
      ge -= A[n];
      n++;
    }

    ans += (mint) B[i] * n - lt + ge - (mint) B[i] * (N - n);
  }
  cout << ans.val() << '\n';
}
