#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vector<int> V(N);
    for (auto &e : V) cin >> e;

    vector<int> V2(N);
    for (int i = 0; i < N; i++) {
      V2[i] = V[(i + N - K) % N];
    }

    mint ans = 1;
    for (int i = 0; i < N; i++) {
      if (V2[i] == 0) {
        ans *= min(i, K) + 1;
      } else if (V2[i] == -1) {
        ans *= i + 1;
      } else {
        ans *= V2[i] + K <= i;
      }
    }
    cout << ans.val() << '\n';
  }
}
