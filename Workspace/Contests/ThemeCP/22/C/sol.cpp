#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int R, C, X;
  cin >> R >> C >> X;

  // If it's not invalid, there's a potential function

  vector<string> H(R);
  for (auto &e : H) cin >> e;

  auto pow = [&](int x, int y) -> i64 {
    i64 rv = 1;
    for (; y; y >>= 1, x *= x) {
      if (y & 1) {
        rv *= x;
      }
    }
    return rv;
  };

  auto is_inside = [&](int r, int c) -> bool {
    return r >= 0 and r < R and c >= 0 and c < C;
  };

  vector seen(R, vector<bool>(C, false));
  vector U(R, vector<i64>(C, -1));
  queue<pair<int, int>> q;
  bool invalid = false;
  auto visit = [&](int r, int c, i64 u) -> void {
    if (seen[r][c]) {
      if (u != U[r][c]) {
        invalid = true;
      }
      return;
    }
    seen[r][c] = true;
    U[r][c] = u;
    q.push({r, c});
  };
  visit(0, 0, 0);
  while (q.size() > 0) {
    auto [r, c] = q.front();
    q.pop();
    for (auto [dr, dc] :
         (pair<int, int>[]) {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
      if (!is_inside(r + dr, c + dc)) continue;
      visit(r + dr, c + dc, U[r][c] + pow(H[r][c] - H[r + dr][c + dc], X));
    }
  }

  int Q;
  cin >> Q;

  while (Q--) {
    int Rs, Cs, Rf, Cf;
    cin >> Rs >> Cs >> Rf >> Cf;
    Rs--, Cs--, Rf--, Cf--;

    if (invalid) {
      cout << "INVALID\n";
    } else {
      cout << U[Rf][Cf] - U[Rs][Cs] << '\n';
    }
  }
}