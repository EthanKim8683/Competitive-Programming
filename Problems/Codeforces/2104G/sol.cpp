#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // if k % 3 == 0, ans = 0
  // if k % 3 == 1, ans = 1
  // if k % 3 == 2, ans = n % 2 == 0 ? 1 : 2
  // link-cut tree?

  // read editorial. missing knowledge

  int N, Q;
  cin >> N >> Q;

  vector<int> G(N);
  for (auto &e : G) {
    cin >> e;
    e--;
  }

  while (Q--) {
    int X, Y, K;
    cin >> X >> Y >> K;
    X--, Y--;

    G[X] = Y;

    if (K % 3 == 0) {
      cout << "0\n";
    } else if (K % 3 == 1) {
      cout << "1\n";
    } else {
      cout << "1 or 2\n";
    }

    // vector<bool> seen(N, false);
    // int n = N;
    // for (int i = 0; i < N; i++) {
    //   vector<int> stack;
    //   int a = i;
    //   while (true) {
    //     if (seen[a]) {
    //       auto it = find(stack.begin(), stack.end(), a);
    //       if (it != stack.end()) {
    //         n -= stack.end() - it - 1;
    //       }
    //       break;
    //     }

    //     seen[a] = true;
    //     stack.push_back(a);

    //     a = G[a];
    //   }
    // }
    // int ans = 1;
    // for (int i = 0; i < n; i++) {
    //   (ans *= k) %= 3;
    // }
    // cout << ans << '\n';
  }
}
