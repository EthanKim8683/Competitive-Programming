#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    i64 K;
    cin >> N >> K;
    K--;

    // looked constructive so I figured I'd give it a try

    if (N <= 60 - 1 and K >= (1ll << (N - 1))) {
      cout << -1 << '\n';
      continue;
    }

    list<int> ans = {1};
    auto it = ans.begin();
    for (int i = 2; i <= N; i++) {
      if (N - i <= 60 and (K >> (N - i) & 1)) {
        it = ans.insert(it, i);
      } else {
        it = ans.insert(next(it), i);
      }
    }
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
