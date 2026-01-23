#include <bits/stdc++.h>

using namespace std;

const int MAXA = 1e6;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<int> indices(MAXA + 1);

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

    auto inside = [&](int i, int j) -> bool {
      return i >= 0 and i < N and j >= 0 and j < M;
    };

    vector<int> divisors;
    for (int i = 1; i * i <= A[0][0]; i++) {
      divisors.push_back(i);
      divisors.push_back(A[0][0] / i);
    }
    sort(divisors.begin(), divisors.end());
    divisors.erase(unique(divisors.begin(), divisors.end()), divisors.end());
    for (int i = 0; i < divisors.size(); i++) {
      indices[divisors[i]] = i;
    }

    vector good(N, vector(M, vector<bool>(divisors.size(), false)));
    queue<tuple<int, int, int>> q;
    auto push = [&](int i, int j, int k) -> void {
      if (good[i][j][k]) return;
      good[i][j][k] = true;
      q.push({i, j, k});
    };
    push(0, 0, indices[A[0][0]]);
    while (q.size() > 0) {
      auto [i, j, k] = q.front();
      q.pop();
      for (auto [di, dj] : (pair<int, int>[]) {{0, 1}, {1, 0}}) {
        int i_ = i + di, j_ = j + dj;
        if (!inside(i_, j_)) continue;
        push(i_, j_, indices[gcd(divisors[k], A[i_][j_])]);
      }
    }
    int ans = 1;
    for (int i = 0; i < divisors.size(); i++) {
      if (good[N - 1][M - 1][i]) {
        ans = max(ans, divisors[i]);
      }
    }
    cout << ans << '\n';
  }
}