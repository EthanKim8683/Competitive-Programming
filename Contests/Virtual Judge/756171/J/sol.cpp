#include <bits/stdc++.h>

using namespace std;

const int N = 9;
const int K = 3;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector M(N, vector<int>(N));
  for (auto &r : M) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  vector possible(N, vector<set<int>>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 1; k < 10; k++) {
        possible[i][j].insert(k);
      }
    }
  }

  auto update = [&](int i, int j, int v) -> void {
    possible[i][j].clear();
    M[i][j] = v;
    for (int k = 0; k < N; k++) {
      auto &S = possible[i][k];
      if (S.contains(v)) {
        S.erase(v);
      }
    }
    for (int k = 0; k < N; k++) {
      auto &S = possible[k][j];
      if (S.contains(v)) {
        S.erase(v);
      }
    }
    for (int k = 0; k < K; k++) {
      for (int l = 0; l < K; l++) {
        auto &S = possible[i / K * K + k][j / K * K + l];
        if (S.contains(v)) {
          S.erase(v);
        }
      }
    }
  };

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (M[i][j] != 0) {
        update(i, j, M[i][j]);
      }
    }
  }

  auto check = [&](int i, int j) -> bool {
    if (possible[i].size() == 0) return false;

    if (possible[i][j].size() == 1) {
      update(i, j, *possible[i][j].begin());
      return true;
    }

    for (auto e : possible[i][j]) {
      bool found = false;
      {
        int count = 0;
        for (int k = 0; k < N; k++) {
          count += possible[i][k].contains(e);
        }
        found = found or count == 1;
      }
      {
        int count = 0;
        for (int k = 0; k < N; k++) {
          count += possible[k][j].contains(e);
        }
        found = found or count == 1;
      }
      {
        int count = 0;
        for (int k = 0; k < K; k++) {
          for (int l = 0; l < K; l++) {
            count += possible[i / K * K + k][j / K * K + l].contains(e);
          }
        }
        found = found or count == 1;
      }
      if (found) {
        update(i, j, e);
        return true;
      }
    }
    return false;
  };

  while (true) {
    bool found = false;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        found = found or check(i, j);
      }
    }
    if (!found) break;
  }

  bool ok = true;
  for (auto r : M) {
    for (auto e : r) {
      ok = ok and e != 0;
    }
  }

  cout << (ok ? "Easy" : "Not easy") << '\n';
  for (auto r : M) {
    for (auto e : r) {
      if (e == 0) {
        cout << ". ";
      } else {
        cout << e << ' ';
      }
    }
    cout << '\n';
  }
}