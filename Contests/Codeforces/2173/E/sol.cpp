#ifndef L
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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int T;
  if (argc > 1) {
    T = 1;
  } else {
    cin >> T;
  }

  while (T--) {
    int N;
    if (argc > 1) {
      N = rng() % 4000 + 1;
    } else {
      cin >> N;
    }

    vi P(N);
    if (argc > 1) {
      iota(all(P), 0);
      shuffle(all(P), rng);
    } else {
      for (auto &e : P) {
        cin >> e;
        e--;
      }
    }

    if (argc > 1) {
      // cerr << "input:\n";
      // cerr << N << '\n';
      // for (auto e : P) {
      //   cerr << e << ' ';
      // }
      // cerr << '\n';
    }

    // E1 = 0.5E0 + 0.5
    // E0 = E1 + 1
    // E1 = 0.5(E1 + 1) + 0.5
    // E1 = 2
    // E0 = 3

    int count = 0;
    auto query = [&](int x, int y) -> pii {
      if (argc > 1) {
        assert(x != y);
        // cerr << "query:\t" << x << ' ' << y << '\n';
        count++;
        assert(count <= (int) floor(2.5 * N + 800));
        if (rng() % 2 == 1) {
          x = N - 1 - x;
          y = N - 1 - y;
        }
        if (rng() % 2) {
          swap(x, y);
        }
        swap(P[x], P[y]);
        // cerr << "return:\t" << x << ' ' << y << '\n';
        // cerr << "P:\t";
        // for (auto e : P) {
        //   cerr << e << ' ';
        // }
        // cerr << '\n';
        return {x, y};
      } else {
        cout << "? " << x + 1 << ' ' << y + 1 << endl;
        int u;
        cin >> u;
        if (u == -1) exit(0);
        int v;
        cin >> v;
        if (v == -1) exit(0);
        u--, v--;
        swap(P[u], P[v]);
        return {u, v};
      }
    };

    auto answer = [&]() -> void {
      if (argc > 1) {
        cerr << "count:\t" << count << '\n';
        assert(is_sorted(all(P)));
      } else {
        cout << "!" << endl;
      }
    };

    if (N % 2 == 1) {
      while (P[N / 2] != N / 2) {
        // cerr << "middle:\n";
        query(N / 2, find(all(P), N / 2) - P.begin());
      }
    }

    for (int l = 0, r = N - 1; l < r; l++, r--) {
      int l2, r2;
      rep(i, l, r + 1) {
        if (P[i] == l) {
          l2 = i;
        }
        if (P[i] == r) {
          r2 = i;
        }
      }

      if (l2 == l and r2 == r) continue;
      if (l2 == r and r2 == l) {
        // cerr << "trivial " << l << ' ' << r << ":\n";
        query(l, r);
        continue;
      }

      // cerr << "preparing " << l << ' ' << r << ":\n";
      auto norm = [&](pii x) -> pii {
        auto [a, b] = x;
        if (a > b) {
          swap(a, b);
        }
        return {a, b};
      };
      if (l2 != N - 1 - r2) {
        if (norm(query(l2, N - 1 - r2)) == norm(pii{l2, N - 1 - r2})) {
          l2 = N - 1 - r2;
        } else {
          r2 = N - 1 - l2;
        }
      }

      // cerr << "fixing " << l << ' ' << r << ":\n";
      while (P[l] != l or P[r] != r) {
        query(l, l2);
      }
    }
    answer();
  }
}
