#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  auto use = [&](int t) -> i64 {
    vector<i64> A2(A.begin(), A.end());
    i64 rv = 0;
    for (int i = 0; i < N; i++) {
      if (i % 2 == t) {
        i64 b = -INF;
        if (i - 1 >= 0) {
          b = max(b, A2[i - 1]);
        }
        if (i + 1 < N) {
          b = max(b, A2[i + 1]);
        }
        i64 d = max(b + 1 - A2[i], 0ll);
        A2[i + 1] -= d;
        rv += d;
      } else {
        i64 b = INF;
        if (i - 1 >= 0) {
          b = min(b, A2[i - 1]);
        }
        if (i + 1 < N) {
          b = min(b, A2[i + 1]);
        }
        i64 d = max(A2[i] - (b - 1), 0ll);
        A2[i + 1] += d;
        rv += d;
      }
    }
    return rv;
  };
  i64 ans = min(use(0), use(1));
  cout << (ans > 1 ? -1 : ans);
}
