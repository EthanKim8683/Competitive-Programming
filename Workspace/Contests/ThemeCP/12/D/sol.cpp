#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // I was so close... I immediately observed Gray code and I thought about
  // collating the Gray codes together (I even observed that I needed to use the
  // higher powers less), but got distracted.

  auto gray_code = [&](int i) -> int { return i ^ i >> 1; };
  auto collate = [&](int x, int y) -> int {
    int rv = 0;
    for (int i = 5 - 1; i >= 0; i--) {
      rv = rv << 1 | x >> i & 1;
      rv = rv << 1 | y >> i & 1;
    }
    return rv;
  };
  auto get_key = [&](int i, int j) -> int {
    return collate(gray_code(i), gray_code(j));
  };

  vector X(32, vector<int>(32));
  map<int, pair<int, int>> M;
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 32; j++) {
      X[i][j] = get_key(i, j);
      M[X[i][j]] = {i, j};
    }
  }

  int N, K;
  cin >> N >> K;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j + 1 < N; j++) {
      cout << (X[i][j] ^ X[i][j + 1]) << ' ';
    }
    cout << '\n';
  }
  for (int i = 0; i + 1 < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << (X[i + 1][j] ^ X[i][j]) << ' ';
    }
    cout << '\n';
  }
  cout.flush();

  int accum = 0;
  while (K--) {
    int X;
    cin >> X;

    accum ^= X;
    auto [i, j] = M[accum];
    cout << i + 1 << ' ' << j + 1 << endl;
  }
}
