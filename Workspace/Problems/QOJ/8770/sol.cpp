#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
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
typedef vc<int> vi;

const int MAXK = 10;

using T = bitset<4>;
struct parser {
  const string &token;
  int pos;
  parser(const string &token, int pos) : token{token}, pos{pos} {};

  int priority(char x) {
    if (x == '^') return 3;
    if (x == '|') return 2;
    if (x == '&') return 1;
    if (x == '=') return 0;
    return -1;
  }

  T comb(T left, T right, char op) {
    T ret{};
    rep(q, 0, sz(left)) {
      bool a = left[q];
      bool b = right[q];
      bool x;
      if (op == '=')
        x = a == b;
      else if (op == '|')
        x = a || b;
      else if (op == '&')
        x = a && b;
      else if (op == '^')
        x = a ^ b;
      else
        x = 0;
      ret[q] = x;
    }
    return ret;
  }

  T parse_expr(int limit = 100) {
    T curr = parse_unary();
    // we can only do stuff that are of strictly "higher" priority
    while (pos < sz(token) && token[pos] != ')' &&
           priority(token[pos]) < limit) {
      char op = token[pos++];
      T right = parse_expr(priority(op));
      curr = comb(curr, right, op);
    }
    return curr;
  }

  T parse_unary() {
    char f = token[pos++];
    if (f == '0') {
      T ret{};
      return ret;
    } else if (f == '1') {
      T ret{};
      ret.set();
      return ret;
    } else if (f == 'x') {
      T ret{};
      rep(q, 0, sz(ret)) ret[q] = q % 2;
      return ret;
    } else if (f == 'y') {
      T ret{};
      rep(q, 0, sz(ret)) ret[q] = q / 2;
      return ret;
    } else if (f == '!') {
      auto ret = parse_unary();
      rep(q, 0, sz(ret)) ret[q] = !ret[q];
      return ret;
    } else if (f == '(') {
      auto ret = parse_expr();
      char partner = token[pos++];
      assert(partner == ')');
      return ret;
    } else {
      cerr << " F = " << f << endl;
      assert(0ll);
    }
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // every pair only has to find the earliest out of 10 * 10 statements
  //
  // transitivity can be checked by xoring two bitsets

  int N, K;
  cin >> N >> K;

  vc<tuple<int, int, string, int>> statements(N);
  for (auto &[a, b, expr, r] : statements) {
    cin >> a >> b >> expr >> r;
    a--, b--;
  }

  int R;
  cin >> R;

  vc is_seen(K, vc(2, vc(K, vc<bool>(2, false))));
  vc<bitset<1 << MAXK>> is_set(1 << K), f(1 << K);
  if (R == 1) {
    for (auto &e : f) {
      e.set();
    }
  }
  auto insert = [&](int a, int xa, int b, int yb, int r) -> void {
    if (is_seen[a][xa][b][yb]) return;
    is_seen[a][xa][b][yb] = true;

    auto next = [&](int x, int i, int xi) -> int {
      x |= 1 << i;
      x += 1;
      x &= ~(1 << i);
      x |= xi << i;
      return x;
    };

    for (int x = xa << a; x < (1 << K); x = next(x, a, xa)) {
      for (int y = yb << b; y < (1 << K); y = next(y, b, yb)) {
        if (is_set[x][y]) continue;
        is_set[x][y] = true;
        f[x][y] = r;
      }
    }
  };
  for (auto [a, b, expr, r] : statements) {
    auto table = parser(expr, 0).parse_expr();
    rep(yb, 0, 2) {
      rep(xa, 0, 2) {
        if (!table[yb * 2 + xa]) continue;
        insert(a, xa, b, yb, r);
      }
    }
  }

  vi ans(3, 0);

  rep(x, 0, 1 << K) {
    if (f[x][x] == 0) continue;
    ans[0] += 1;
  }

  rep(x, 0, 1 << K) {
    rep(y, 0, 1 << K) {
      if (f[x][y] == 0 or f[y][x] == 0) continue;
      ans[1] += 1;
    }
  }

  rep(x, 0, 1 << K) {
    rep(y, 0, 1 << K) {
      if (f[x][y] == 0) continue;
      ans[2] += (~f[x] & f[y]).count();
    }
  }

  for (auto e : ans) {
    cout << e << ' ';
  }
}
