#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

// My first DMOJ contest! Hope I do alright!
int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector S(N, vector<int>(M));
  for (auto &r : S) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  vector ps(N, vector<i64>(M + 1));
  for (int i = 0; i < N; i++) {
    ps[i][0] = 0;
    for (int j = 0; j < M; j++) {
      ps[i][j + 1] = ps[i][j] + S[i][j];
    }
  }

  int ans = 0;
  for (int i = 0; i < M; i++) {
    for (int j = 2; i + j <= M; j += 2) {
      map<i64, int> seen;
      i64 psl = 0, psr = 0;
      for (int k = 0; k < N; k++) {
        if (!seen.contains(psl - psr)) {
          seen.insert({psl - psr, k});
        }

        psl += ps[k][i + j / 2] - ps[k][i];
        psr += ps[k][i + j] - ps[k][i + j / 2];
        if (seen.contains(psl - psr)) {
          ans = max(ans, (k + 1 - seen[psl - psr]) * j);
        }
      }
    }
  }
  cout << ans;
}
