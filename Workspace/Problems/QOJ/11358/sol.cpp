#include <ostream>
#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vi pows(9 + 1);
  pows[0] = 1;
  rep(i, 1, 9 + 1) { pows[i] = pows[i - 1] * 3; }

  // 0 => cannot be; empty
  // 1 => can be
  // 2 => full
  //
  // try splits of can be's
  //
  // find a split of can be's s.t. there is a move that wins
  //
  // for all masks: 3^9
  //   is win = False
  //   try splits of can be's: 2^9
  //     # split 1
  //     ok1 = False
  //     for all moves: 9
  //       ok1 = ok1 or resulting mask is a win
  //     # split 2
  //     ok2 = False
  //     for all moves: 9
  //			 ok2 = ok2 or resulting mask is a win
  //		 is win = is win or (ok1 and ok2)

  auto expand = [&](int mask) -> pii {
    int ones = 0, twos = 0;
    rep(i, 0, 9) {
      int d = mask / pows[i] % 3;
      if (d == 1) {
        ones |= 1 << i;
      } else if (d == 2) {
        twos |= 1 << i;
      }
    }
    return {ones, twos};
  };

  auto compress = [&](int ones, int twos) -> int {
    int rv = 0;
    rep(i, 0, 9) {
      if (twos >> i & 1) {
        rv += 2 * pows[i];
      } else if (ones >> i & 1) {
        rv += 1 * pows[i];
      }
    }
    return rv;
  };

  auto encode = [&](int r, int c) -> int { return r * 3 + c; };

  auto decode = [&](int x) -> pii { return {x / 3, x % 3}; };

  vi spreads(9, 0);
  rep(i, 0, 9) {
    rep(j, 0, 9) {
      auto [r1, c1] = decode(i);
      auto [r2, c2] = decode(j);
      if (abs(r2 - r1) + abs(c2 - c1) == 1) {
        spreads[i] |= 1 << j;
      }
    }
  }

  auto spread = [&](int ones) -> int {
    int rv = 0;
    rep(i, 0, 9) {
      if (~ones >> i & 1) continue;
      rv |= spreads[i];
    }
    return rv;
  };

  vi order(pows[9]);
  iota(all(order), 0);
  sort(all(order), [&](int a, int b) -> bool {
    auto key = [&](int x) -> int {
      auto [ones, twos] = expand(x);
      return -twos;
    };
    return key(a) < key(b);
  });

  vc<tuple<int, int, int, int>> dp(pows[9], {INF, 0, 0, 0});
  for (auto e : order) {
    auto [ones, twos] = expand(e);
    if (ones == 0) {
      dp[e] = {0, 0, 0, 0};
      continue;
    }

    for (int i = ones; i > 0; i = (i - 1) & ones) {
      pii best1 = {INF, -1};
      rep(j, 0, 9) {
        if (twos >> j & 1) continue;
        chmin(best1,
              make_pair(get<0>(dp[compress(spread(ones & i), twos | 1 << j)]),
                        j));
      }

      pii best2 = {INF, -1};
      rep(j, 0, 9) {
        if (twos >> j & 1) continue;
        chmin(best2,
              make_pair(get<0>(dp[compress(spread(ones & ~i), twos | 1 << j)]),
                        j));
      }

      auto [d1, move1] = best1;
      auto [d2, move2] = best2;
      if (move1 != -1 and move2 != -1) {
        chmin(dp[e], make_tuple(max(d1, d2) + 1, i, move1, move2));
      }
    }
  }

  int R, U;
  cin >> R >> U;

  vi S(U);
  for (auto &e : S) {
    cin >> e;
    e--;
  }

  int twos = 0;
  for (auto e : S) {
    twos |= 1 << e;
  }
  int ones = (1 << 9) - 1 - twos;
  int d = get<0>(dp[compress(ones, twos)]);

  auto choose = [&](string player) -> void { cout << player << endl; };

  if (d <= R) {
    choose("Trapper");

    auto ask = [&](vi squares) -> bool {
      cout << sz(squares) << '\n';
      for (auto e : squares) {
        cout << e + 1 << ' ';
      }
      cout << endl;
      string R;
      cin >> R;
      return R == "Yes";
    };

    auto mark = [&](int i) -> bool {
      cout << i + 1 << endl;
      string R;
      cin >> R;
      return R == "Trapped";
    };

    rep(t, 0, R) {
      auto [d, split, move1, move2] = dp[compress(ones, twos)];
      vi squares;
      rep(i, 0, 9) {
        if (~split >> i & 1) continue;
        squares.pb(i);
      }
      if (ask(squares)) {
        if (mark(move1)) break;
        ones = spread(ones & split);
        twos |= 1 << move1;
      } else {
        if (mark(move2)) break;
        ones = spread(ones & ~split);
        twos |= 1 << move2;
      }
      ones &= ~twos;
    }
  } else {
    choose("Runner");

    auto answer = [&](bool yes) -> void {
      cout << (yes ? "Yes" : "No") << endl;
    };

    auto move = [&](bool trapped) -> void {
      cout << (trapped ? "Trapped" : "Free") << endl;
      assert(!trapped);
    };

    auto show = [&](vi moves) -> void {
      for (auto e : moves) {
        cout << e + 1 << ' ';
      }
      cout << endl;
    };

    vi masks;
    rep(t, 0, R) {
      int N;
      cin >> N;

      vi squares(N);
      for (auto &e : squares) {
        cin >> e;
        e--;
      }

      int split = 0;
      for (auto e : squares) {
        split |= 1 << e;
      }

      int d1 = INF;
      rep(i, 0, 9) {
        if (twos >> i & 1) continue;
        chmin(d1, get<0>(dp[compress(spread(ones & split), twos | 1 << i)]));
      }

      int d2 = INF;
      rep(i, 0, 9) {
        if (twos >> i & 1) continue;
        chmin(d2, get<0>(dp[compress(spread(ones & ~split), twos | 1 << i)]));
      }

      if (d1 > d2) {
        ones &= split;
        answer(true);
      } else {
        ones &= ~split;
        answer(false);
      }
      masks.pb(ones);
      ones = spread(ones);

      int i;
      cin >> i;
      i--;

      twos |= 1 << i;
      ones &= ~twos;

      move(ones == 0);
    }
    masks.pb(ones);

    int a = __lg(masks.back());
    vi ans = {a};
    for (int i = sz(masks) - 2; i >= 0; i--) {
      a = __lg(spread(1 << a) & masks[i]);
      ans.pb(a);
    }
    reverse(all(ans));
    show(ans);
  }
}
