#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // degree 2
  //
  // vertical degree
  // horizontal degree

  int N;
  cin >> N;

  vector grid(1 << N, vector<int>(1 << N));
  for (auto &r : grid) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  int count = 0;
  for (auto r : grid) {
    for (auto e : r) {
      if (e != 0) continue;
      count++;
    }
  }
  if (count != 1) {
    cout << "0\n";
    exit(0);
  }

  auto is_inside = [&](int i, int j) -> bool {
    return 0 <= i and i < (1 << N) and 0 <= j and j < (1 << N);
  };

  int deltas[] = {-1, 1};

  vector<bool> seen(((1 << (2 * N)) - 1) / 3 + 1, false);
  for (int i = 0; i < (1 << N); i++) {
    for (int j = 0; j < (1 << N); j++) {
      int count1 = 0, count2 = 0;
      for (auto di : deltas) {
        if (!is_inside(i + di, j)) continue;
        if (grid[i + di][j] != grid[i][j]) continue;
        count1++;
      }
      for (auto dj : deltas) {
        if (!is_inside(i, j + dj)) continue;
        if (grid[i][j + dj] != grid[i][j]) continue;
        count2++;
      }
      if (count1 > 1 or count2 > 1) {
        cout << "0\n";
        exit(0);
      }
      if (count1 + count2 == 2) {
        if (seen[grid[i][j]]) {
          cout << "0\n";
          exit(0);
        }
        seen[grid[i][j]] = true;
      }
    }
  }
  for (int i = 1; i < ((1 << (2 * N)) - 1) / 3 + 1; i++) {
    if (!seen[i]) {
      cout << "0\n";
      exit(0);
    }
  }

  cout << "1\n";
}
