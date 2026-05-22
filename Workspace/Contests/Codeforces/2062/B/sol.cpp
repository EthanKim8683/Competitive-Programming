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

    bool ok = true;
    for (int i = 0; i < N; i++) {
      ok = ok and A[i] > 2 * max(i, N - 1 - i);
    }
    cout << (ok ? "YES" : "NO") << '\n';
  }
}
/*
2 3 4 5 6 7

[0, 0], [0, 1], etc.
*/
