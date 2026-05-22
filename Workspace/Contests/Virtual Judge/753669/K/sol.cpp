#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<string> A(N);
  for (auto &e : A) cin >> e;

  vector<vector<pair<int, int>>> adj = {
    {{2, 0}, {4, 2}, {3, 0}, {1, 2}}, {{3, 3}, {5, 0}, {2, 1}, {0, 2}},
    {{5, 0}, {4, 1}, {0, 0}, {1, 3}}, {{0, 0}, {4, 3}, {5, 0}, {1, 1}},
    {{3, 1}, {0, 2}, {2, 3}, {5, 0}}, {{3, 0}, {4, 0}, {2, 0}, {1, 0}},
  };

  vector seen(N, vector(M, vector(6, vector<tuple<int, int, int, int>>(
                                         4, {-1, -1, -1, -1}))));
  queue<tuple<int, int, int, int>> q;
  auto push = [&](int i, int j, int k, int l, int pi, int pj, int pk,
                  int pl) -> void {
    if (i < 0 or i >= N or j < 0 or j >= M) return;
    if (A[i][j] == 'x') return;
    if (seen[i][j][k][l] != make_tuple(-1, -1, -1, -1)) return;
    seen[i][j][k][l] = {pi, pj, pk, pl};
    q.push({i, j, k, l});
  };
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (A[i][j] == 's') {
        push(i, j, 5, 0, -2, -2, -2, -2);
      }
    }
  }
  while (q.size() > 0) {
    auto [i, j, k, l] = q.front();
    q.pop();
    pair<int, int> dij[] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    for (int m = 0; m < 4; m++) {
      auto [k_, dl] = adj[k][m];
      auto [di, dj] = dij[(l + m) % 4];
      int l_ = (l + dl) % 4, i_ = i + di, j_ = j + dj;
      push(i_, j_, k_, l_, i, j, k, l);
    }
  }
  int ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if ('1' <= A[i][j] and A[i][j] <= '6') {
        int k = A[i][j] - '1', l_ = -1;
        for (int l = 0; l < 4; l++) {
          if (seen[i][j][k][l] != make_tuple(-1, -1, -1, -1)) {
            l_ = l;
            break;
          }
        }
        ans += l_ != -1;

        // if (l_ != -1) {
        //   vector<tuple<int, int, int, int>> path;
        //   int i_ = i, j_ = j, k_ = k;
        //   while (i_ != -2) {
        //     auto [pi, pj, pk, pl] = seen[i_][j_][k_][l_];
        //     path.push_back({i_, j_, k_, l_});
        //     tie(i_, j_, k_, l_) = make_tuple(pi, pj, pk, pl);
        //   }
        //   reverse(path.begin(), path.end());
        //   cerr << i << ' ' << j << ":\n";
        //   for (auto [i_, j_, k_, l_] : path) {
        //     cerr << i_ << ' ' << j_ << ' ' << k_ << ' ' << l_ << '\n';
        //   }
        //   cerr << '\n';
        // }
      }
    }
  }
  cout << ans;
}