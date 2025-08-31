#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    if (M <= N) {
      cout << "YES\n";
      for (int i = 0; i < 2 * N; i++) {
        for (int j = 0; j < M; j++) {
          cout << j + 1 << ' ';
        }
        cout << '\n';
      }
      continue;
    }

    cout << "NO\n";
  }
}
