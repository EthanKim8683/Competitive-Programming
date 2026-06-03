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
    rng = mt19937(atoi(argv[1]));
  }

  // try to split

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;
    if (N == -1) {
      exit(0);
    }

    vi A;
    if (argc > 1) {
      rep(i, 0, N) {
        A.pb(i);
        A.pb(i);
      }
      shuffle(all(A), rng);
      A.pop_back();
    }

    auto query = [&](int x, vi S) -> int {
      if (argc > 1) {
        for (auto e : S) {
          if (A[e] == x) return true;
        }
        return false;
      } else {
        cout << "? " << x << ' ' << sz(S);
        for (auto e : S) {
          cout << ' ' << e + 1;
        }
        cout << endl;
        int rv;
        cin >> rv;
        if (rv == -1) {
          exit(0);
        }
        return rv;
      }
    };

    auto answer = [&](int y) -> void {
      if (argc > 1) {
        assert(count(all(A), y) == 1);
      } else {
        cout << "! " << y << endl;
      }
    };
  }
}
