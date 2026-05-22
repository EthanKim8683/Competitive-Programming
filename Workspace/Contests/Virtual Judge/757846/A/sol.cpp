#pragma GCC optimize("trapv")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vector<int> vi;

const int INF = 1e9;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int C, R, E;
  cin >> C >> R >> E;

  char dirs_chars[] = "NESW";

  auto encode_dir_char = [&](char dir_char) -> int {
    return find(all(dirs_chars), dir_char) - begin(dirs_chars);
  };

  int C1, R1;
  char D1;
  int C2, R2;
  char D2;
  cin >> C1 >> R1 >> D1 >> C2 >> R2 >> D2;
  int d1 = encode_dir_char(D1), d2 = encode_dir_char(D2),
      dd = (d2 - d1 + 4) % 4;

  vc movable(C + 2, vc(R + 2, vc(C + 2, vc<bool>(R + 2, true))));
  rep(i, 1, R + 1) {
    movable[0][i][1][i] = false;
    movable[1][i][0][i] = false;
    movable[C][i][C + 1][i] = false;
    movable[C + 1][i][C][i] = false;
  }
  rep(i, 1, C + 1) {
    if (i != E) {
      movable[i][0][i][1] = false;
      movable[i][1][i][0] = false;
    }
    movable[i][R][i][R + 1] = false;
    movable[i][R + 1][i][R] = false;
  }

  int N1;
  cin >> N1;
  rep(_i, 0, N1) {
    int c, r;
    cin >> c >> r;
    movable[c][r][c][r + 1] = false;
    movable[c][r + 1][c][r] = false;
  }

  int N2;
  cin >> N2;
  rep(_i, 0, N2) {
    int c, r;
    cin >> c >> r;
    movable[c][r][c + 1][r] = false;
    movable[c + 1][r][c][r] = false;
  }

  pii dirs[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  vc dist(C + 2, vc(R + 2, vc(C + 2, vc<pii>(R + 2, {INF, INF}))));
  queue<tuple<int, int, int, int>> c;
  auto push = [&](int c1, int r1, int c2, int r2, pii d) -> void {
    if (d >= dist[c1][r1][c2][r2]) return;
    dist[c1][r1][c2][r2] = d;
    c.push({c1, r1, c2, r2});
  };
  push(C1, R1, C2, R2, {0, 0});
  while (c.size() > 0) {
    auto [c1, r1, c2, r2] = c.front();
    c.pop();
    auto [moves0, bumps0] = dist[c1][r1][c2][r2];

    rep(i, 0, 4) {
      int moves = moves0, bumps = bumps0;
      moves++;

      auto [dc1, dr1] = dirs[i];
      auto [dc2, dr2] = dirs[(i + dd) % 4];

      int c1_ = c1 + dc1, r1_ = r1 + dr1;
      int c2_ = c2 + dc2, r2_ = r2 + dr2;

      if (r1 == 0) {
        c1_ = c1;
        r1_ = r1;
      }
      if (r2 == 0) {
        c2_ = c2;
        r2_ = r2;
      }

      if (!movable[c1][r1][c1_][r1_]) {
        c1_ = c1;
        r1_ = r1;
        bumps++;
      }
      if (!movable[c2][r2][c2_][r2_]) {
        c2_ = c2;
        r2_ = r2;
        bumps++;
      }

      if (r1_ != 0 and c1_ == c2_ and r1_ == r2_) continue;

      push(c1_, r1_, c2_, r2_, {moves, bumps});
    }
  }
  auto [moves, bumps] = dist[E][0][E][0];
  cout << moves << ' ' << bumps << '\n';
}