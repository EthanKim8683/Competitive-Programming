#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<vector<int>> divs(4e5 + 1);
  for (int i = 1; i <= 4e5; i++) {
    for (int j = i; j <= 4e5; j += i) {
      divs[j].push_back(i);
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<int> B(N);
    for (auto &e : B) cin >> e;

    vector<vector<int>> by_A(N + 1);
    for (int i = 0; i < N; i++) {
      by_A[A[i]].push_back(B[i]);
    }
    for (int i = 1; i <= N; i++) {
      sort(by_A[i].begin(), by_A[i].end());
    }

    i64 ans = 0;
    for (int i = 1; i <= 2 * N; i++) {
      for (auto j : divs[i]) {
        if (j < i / j or j > N or i / j > N) continue;
        for (int k = 0; k < by_A[j].size(); k++) {
          auto e = by_A[i / j].end();
          if (j == i / j) {
            e = by_A[i / j].begin() + k;
          }
          ans += upper_bound(by_A[i / j].begin(), e, i - by_A[j][k]) -
                 lower_bound(by_A[i / j].begin(), e, i - by_A[j][k]);
        }
      }
    }
    cout << ans << '\n';
  }
}
