#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int INF = 2e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<int> X(N + 2);
  X[0] = 0;
  X[N + 1] = INF;
  for (int i = 1; i <= N; i++) {
    cin >> X[i];
  }

  int logN = __lg(2 * (N + 2) - 1);

  vector lift1(N + 2, vector<pair<int, i64>>(logN + 1)), lift2 = lift1;
  for (int i = 0; i <= N + 1; i++) {
    int j = lower_bound(X.begin(), X.end(), (i64) X[i] + K) - X.begin();
    j = clamp(j, 0, N + 1);
    lift1[i][0] = {j, j};

    j = prev(upper_bound(X.begin(), X.end(), (i64) X[i] - K)) - X.begin();
    j = clamp(j, 0, N + 1);
    lift2[i][0] = {j, j + 1};
  }
  auto combine = [&](pair<int, i64> a, pair<int, i64> l) -> pair<int, i64> {
    return {l.first, a.second + l.second};
  };

  for (int i = 1; i <= logN; i++) {
    for (int j = 0; j <= N + 1; j++) {
      lift1[j][i] =
          combine(lift1[j][i - 1], lift1[lift1[j][i - 1].first][i - 1]);
      lift2[j][i] =
          combine(lift2[j][i - 1], lift2[lift2[j][i - 1].first][i - 1]);
    }
  }

  int Q;
  cin >> Q;

  while (Q--) {
    int l, r;
    cin >> l >> r;

    pair<int, i64> l2 = {l, l}, r2 = {r, r + 1};
    for (int i = logN; i >= 0; i--) {
      if (lift1[l2.first][i].first <= r) {
        l2 = combine(l2, lift1[l2.first][i]);
      }
    }
    for (int i = logN; i >= 0; i--) {
      if (lift2[r2.first][i].first >= l) {
        r2 = combine(r2, lift2[r2.first][i]);
      }
    }

    cout << r2.second - l2.second << '\n';
  }
}
