#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    auto build = [&](int a0) -> vector<int> {
      vector<int> A(N);
      A[0] = a0;
      int sum = 0;
      for (int i = 1; i < N; i++) {
        int d = min(A[i - 1] - 1, K - sum);
        A[i] = A[i - 1] + d;
        sum += d;
      }
      return A;
    };

    auto check = [&](int a0) -> bool {
      auto A = build(a0);
      int sum = 0;
      for (int i = 0; i + 1 < N; i++) {
        sum += A[i + 1] % A[i];
      }
      return sum == K;
    };

    int l = 2, r = K + 1;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    for (auto e : build(l)) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}