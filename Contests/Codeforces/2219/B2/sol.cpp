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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[0]));
  }

  int T;
  if (argc > 1) {
    T = 100;
  } else {
    cin >> T;
  }

  while (T--) {
    int N;
    if (argc > 1) {
      N = 100;
    } else {
      cin >> N;
    }

    vi A;
    if (argc > 1) {
      rep(i, 1, N + 1) {
        A.pb(i);
        A.pb(i);
      }
      A.pb(rng() % N + 1);
      shuffle(all(A), rng);
    }

    auto query = [&](vi S) -> int {
      if (argc > 1) {
        map<int, int> counts;
        for (auto e : S) {
          counts[A[e]] += 1;
        }
        int rv = 0;
        for (auto [k, count] : counts) {
          if (count != 1) continue;
          rv += 1;
        }
        return rv;
      } else {
        cout << "? " << sz(S);
        for (auto e : S) {
          cout << ' ' << e + 1;
        }
        cout << endl;
        int rv;
        cin >> rv;
        return rv;
      }
    };

    auto answer = [&](vi ans) -> void {
      if (argc > 1) {
        for (auto e : ans) {
          assert(A[e] == A[ans[0]]);
        }
      } else {
        assert(sz(ans) == 3);
        cout << '!';
        for (auto e : ans) {
          cout << ' ' << e + 1;
        }
        cout << endl;
      }
    };

    auto check = [&](int z) -> bool {
      vi S(z + 1);
      iota(all(S), 0);
      return query(S) % 2 != sz(S) % 2;
    };
    int l = 0, r = 2 * N;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    int z = l;

    auto check2 = [&](int y) -> bool {
      vi S(y + 1);
      iota(all(S), 0);
      S.pb(z);
      return query(S) % 2 != sz(S) % 2;
    };
    l = 0;
    r = z - 1;
    while (l < r) {
      int m = l + (r - l) / 2;
      check2(m) ? r = m : l = m + 1;
    }
    int y = l;

    auto check3 = [&](int x) -> bool {
      vi S(x + 1);
      iota(all(S), 0);
      S.pb(y);
      S.pb(z);
      return query(S) % 2 != sz(S) % 2;
    };
    l = 0;
    r = y - 1;
    while (l < r) {
      int m = l + (r - l) / 2;
      check3(m) ? r = m : l = m + 1;
    }
    int x = l;

    answer({x, y, z});
  }
}
