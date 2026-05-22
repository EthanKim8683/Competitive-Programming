#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> X(N);
    for (auto &e : X) cin >> e, e--;

    auto query = [&](int i, int j) -> int {
      cout << "? " << i + 1 << ' ' << j + 1 << endl;
      int rv;
      cin >> rv;
      if (rv == -1) exit(0);
      return rv;
    };

    vector<bool> seen(N, false);
    for (auto e : X) {
      seen[e] = true;
    }
    char ans = 0;
    for (int i = 0; i < N; i++) {
      if (!seen[i]) {
        ans = query(i, i == 0 ? 1 : 0) == 0 ? 'A' : 'B';
        break;
      }
    }

    if (!ans) {
      int a, b;
      for (int i = 0; i < N; i++) {
        if (X[i] == 0) a = i;
        if (X[i] == N - 1) b = i;
      }
      int q1 = query(a, b);
      if (q1 > N - 1) {
        ans = 'B';
      } else if (q1 < N - 1) {
        ans = 'A';
      } else {
        if (query(b, a) != N - 1) {
          ans = 'A';
        } else {
          ans = 'B';
        }
      }
    }

    cout << "! " << ans << endl;
  }
}
