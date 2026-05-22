#include <bits/stdc++.h>

using namespace std;

const int M = 9;
const int B = 10;
const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector binom(2 * M + B, vector<int>(2 * M + B));
  for (int i = 0; i < 2 * M + B; i++) {
    for (int j = 0; j <= i; j++) {
      if (j == 0 or j == i) {
        binom[i][j] = 1;
      } else {
        binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j];
      }
    }
  }

  auto sum = [&](vector<int> counts) -> int {
    return accumulate(counts.begin(), counts.end(), 0);
  };

  auto encode = [&](vector<int> counts) -> int {
    int rv = 0, s = sum(counts), b = B - 1;
    while (s > 0) {
      while (counts[b] == 0) {
        rv += binom[s - 1 + b][b];
        b--;
      }

      counts[b]--;
      s--;
    }
    return rv;
  };

  vector<int> pows(M);
  pows[0] = 1;
  for (int i = 1; i < M; i++) {
    pows[i] = pows[i - 1] * 10;
  }

  auto chmin = [&](int &a, int b) -> void { a = min(a, b); };

  vector X(2 * M + 1, vector<int>(binom[2 * M + B - 1][B - 1], INF));
  for (int i = 1; i <= M; i++) {
    for (int j = 0; j + 1 <= 9; j++) {
      int x = (j + 1) * pows[i - 1] - 1;
      {
        vector<int> counts(B, 0);
        counts[0] = counts[9] = i - 1;
        counts[j + 1]++;
        if (j != 0) {
          counts[j]++;
        }

        if (x != 0) {
          chmin(X[sum(counts)][encode(counts)], x);
        }
      }
      {
        vector<int> counts(B, 0);
        counts[0] = counts[9] = i - 1;
        counts[j]++;
        counts[j + 1]++;

        auto dfs = [&](auto self, int m, int b, int x) -> void {
          if (m > M) return;
          if (b == -1) {
            if (m < M) {
              for (int i = 1; i <= 9; i++) {
                counts[i] += 2;
                chmin(X[sum(counts)][encode(counts)], x + i * pows[m]);
                counts[i] -= 2;
              }
            }
            return;
          }

          counts[b] += 2;
          self(self, m + 1, b, x + b * pows[m]);
          counts[b] -= 2;
          self(self, m, b - 1, x);
        };
        dfs(dfs, i, B - 1, x);
      }
    }
  }
  vector<int> S;
  for (auto r : X) {
    for (auto e : r) {
      if (e == INF) continue;
      S.push_back(e);
    }
  }
  sort(S.begin(), S.end());

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    cout << upper_bound(S.begin(), S.end(), N) - S.begin() << '\n';
  }
}
