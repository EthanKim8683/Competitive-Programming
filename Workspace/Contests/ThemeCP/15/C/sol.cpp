#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector A(N, vector<int>(M));
    for (auto &r : A) {
      for (auto &e : r) {
        cin >> e;
      }
    }

    vector B(N, vector<int>(M));
    for (auto &r : B) {
      for (auto &e : r) {
        cin >> e;
      }
    }

    vector want_0(N, vector<int>(30, 0)), want_1(M, vector<int>(30, 0));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        for (int k = 0; k < 30; k++) {
          if (B[i][j] >> k & 1) {
            want_1[j][k]++;
          } else {
            want_0[i][k]++;
          }
        }
      }
    }

    queue<tuple<int, int, int>> q;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < 30; j++) {
        if (want_0[i][j] == M) {
          q.push({0, i, j});
        }
      }
    }
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < 30; j++) {
        if (want_1[i][j] == N) {
          q.push({1, i, j});
        }
      }
    }
    while (q.size() > 0) {
      auto [t, i, j] = q.front();
      q.pop();

      if (t == 0) {
        for (int k = 0; k < M; k++) {
          want_1[k][j]++;
          if (want_1[k][j] == N) {
            q.push({1, k, j});
          }
        }
      } else {
        for (int k = 0; k < N; k++) {
          want_0[k][j]++;
          if (want_0[k][j] == M) {
            q.push({0, k, j});
          }
        }
      }
    }

    bool ans = true;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        for (int k = 0; k < 30; k++) {
          int b1 = A[i][j] >> k & 1, b2 = B[i][j] >> k & 1;
          ans = ans and (b1 == b2 or want_0[i][k] >= M or want_1[j][k] >= N);
        }
      }
    }
    cout << (ans ? "Yes" : "No") << '\n';
  }
}
