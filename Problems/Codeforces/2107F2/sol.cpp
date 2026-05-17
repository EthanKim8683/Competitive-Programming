#include <bits/stdc++.h>

#include "ethankim8683/data_structures.hpp"

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<i64> ps(N + 1);
    ps[0] = 0;
    for (int i = 0; i < N; i++) {
      ps[i + 1] = ps[i] + A[i] + 1;
    }

    line_container<i64> lc1, lc2;
    lc1.insert(INF, INF);
    lc2.insert(0, -1);
    for (int i = 0; i < N; i++) {
      i64 ans = INF;
      ans = min(ans, lc1.get(i + 1));
      ans = min(ans, lc2.get(A[i] + 1) + (i64) (A[i] + 1) * (i + 1));
      cout << ans << ' ';
      lc1.insert(A[i] + 2, ans + (i64) (A[i] + 2) * -(i + 1));
      lc2.insert(-(i + 1), ans - 1);
    }
    cout << '\n';
  }
}
