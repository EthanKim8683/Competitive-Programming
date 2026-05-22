#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    if (K == 0) {
      cout << -1 << '\n';
      continue;
    }

    if (K == 1) {
      if (N == 1) {
        cout << 1 << '\n';
      } else if (N >= 5) {
        cout << "2 5 3 1 4";
        for (int i = 5; i < N; i++) {
          cout << ' ' << i + 1;
        }
        cout << '\n';
      } else {
        cout << -1 << '\n';
      }
      continue;
    }

    int M = N - K;
    for (int i = 0; i < K; i++) {
      cout << M + i + 1 << ' ';
    }
    for (int i = M - 1; i >= 0; i--) {
      cout << i + 1 << ' ';
    }
    cout << '\n';
  }
}