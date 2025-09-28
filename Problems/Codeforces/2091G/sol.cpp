#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    i64 S;
    int K;
    cin >> S >> K;

    // S + 1 > lcm(K, K - 2) - K - (K - 2)
    // S + 1 > K * K - 4 * K - 2
    // S > K * K
    // K < sqrt(S)
    // S * (K - sqrt(S))

    if (S % K == 0) {
      cout << K << '\n';
      continue;
    }

    if (S > K * K) {
      cout << K - 2 << '\n';
      continue;
    }

    vector<bool> seen(S + 1, false);
    seen[0] = true;
    int dir = 1;
    for (; K > 1; K--) {
      vector<bool> seen_(S + 1, false);
      if (dir == 1) {
        for (int i = 0; i + K <= S; i++) {
          seen_[i + K] = seen_[i] or seen[i];
        }
      } else {
        for (int i = S; i - K >= 0; i--) {
          seen_[i - K] = seen_[i] or seen[i];
        }
      }
      if (seen_[S]) break;

      seen = seen_;
      dir = -dir;
    }
    cout << K << '\n';
  }
}