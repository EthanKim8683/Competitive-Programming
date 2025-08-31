#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, B, K1, K2;
    cin >> N >> B >> K1 >> K2;

    vector<int> A(N);
    for (auto &e : A) cin >> e;
    sort(A.begin(), A.end());

    // Choose splits for the first operation
    //
    // Then brute force the second operation
    //
    // Maybe it'll work?

    int M = N;
    for (; M > 0 and K1 > 0 and K2 > 0 and (A[M - 1] + 1) / 2 - B >= 0;
         M--, K1--, K2--) {
      A[M - 1] = (A[M - 1] + 1) / 2 - B;
    }

    i64 ans = INF;
    for (int i = 0; i <= K1; i++) {
      vector A_ = A;
      for (int j = 0; j < i; j++) {
        A_[M - 1 - j] = (A_[M - 1 - j] + 1) / 2;
      }
      for (int j = 0; j < K1 - i; j++) {
        A_[j] = (A_[j] + 1) / 2;
      }
      sort(A_.begin(), A_.begin() + M);
      for (int j = 0; j < K2; j++) {
        A_[M - 1 - j] = max(A_[M - 1 - j] - B, 0);
      }
      i64 sum = 0;
      for (auto e : A_) {
        sum += e;
      }
      ans = min(ans, sum);
    }
    cout << ans << '\n';
  }
}
