#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    int ans = 0, k = 0;
    for (int i = 0; i < N; i++) {
      if (A[i] >= 2 * k) {
        for (int j = 0; j < i; j++) {
          ans = max(ans, A[j] % A[i] + A[i] % A[j]);
        }
      } else if (A[i] > k) {
        ans = A[i];
      } else {
        ans = max(ans, k % A[i] + A[i] % k);
      }
      k = max(k, A[i]);
      cout << ans << ' ';
    }
    cout << '\n';
  }
}