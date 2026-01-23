#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    auto solve = [&](int x) -> tuple<int, int, int, int> {
      vector<int> B;
      for (int i = 0; i < N; i++) {
        if (i == x) continue;
        B.push_back(A[i]);
      }
      int M = B.size();

      tuple<int, int, int, int> rv = {-INF, -1, -1, -1};
      deque<pair<int, int>> top;
      for (int i = 0; i < M; i++) {
        int Bi = B[i];

        if (top.size() == 2) {
          auto [Bj, j] = top[0];
          auto [Bk, k] = top[1];
          rv = max(rv, {Bi - Bk, i, j, k});
        }

        top.push_back({Bi, i});
        sort(top.begin(), top.end());
        if (top.size() > 2) {
          top.pop_back();
        }
      }
      top.clear();
      for (int i = M - 1; i >= 0; i--) {
        int Bi = B[i];

        if (top.size() == 2) {
          auto [Bj, j] = top[0];
          auto [Bk, k] = top[1];
          rv = max(rv, {Bj - Bi, i, j, k});
        }

        top.push_back({Bi, i});
        sort(top.begin(), top.end());
        if (top.size() > 2) {
          top.pop_front();
        }
      }

      vector<pair<int, int>> pm(M);
      pm[0] = {INF, -1};
      for (int i = 0; i + 1 < M; i++) {
        pm[i + 1] = min(pm[i], {B[i], i});
      }
      vector<pair<int, int>> sm(M);
      sm[M - 1] = {-INF, -1};
      for (int i = M - 1; i - 1 >= 0; i--) {
        sm[i - 1] = max(sm[i], {B[i], i});
      }
      for (int i = 1; i < M - 1; i++) {
        int Bi = B[i];
        auto [Bj, j] = pm[i];
        auto [Bk, k] = sm[i];
        rv = max(rv, {min(Bi - Bj, Bk - Bi), i, j, k});
      }

      return rv;
    };
    auto [w, i, j, k] = solve(-1);
    cout << min(get<0>(solve(i)), min(get<0>(solve(j)), get<0>(solve(k))))
         << '\n';
  }
}
