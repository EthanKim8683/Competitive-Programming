#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    auto query = [&](int y) -> int {
      cout << y << endl;
      int rv;
      cin >> rv;
      if (rv == -1) exit(0);
      return rv;
    };

    if (query(0) == 1) continue;
    query(1);
    for (int i = N; i >= 3; i--) {
      if (query(i) == 1) {
        break;
      }
    }
  }
}
