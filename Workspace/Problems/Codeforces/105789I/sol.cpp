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

const int MAXA = 1e6;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vi P(N);
  for (auto &e : P) cin >> e;

  list<int> P2(all(P));

  vc<list<int>::iterator> its(MAXA + 1, P2.end());
  for (auto it = P2.begin(); it != P2.end(); it++) {
    its[*it] = it;
  }

  int E;
  cin >> E;

  while (E--) {
    char t;
    cin >> t;

    if (t == '-') {
      int X;
      cin >> X;

      P2.erase(its[X]);
      its[X] = P2.end();
    } else if (t == '+') {
      int Y, Z;
      cin >> Y >> Z;

      its[Y] = P2.insert(its[Z], Y);
    } else {
      int K;
      cin >> K;

      vi A(K);
      for (auto &e : A) cin >> e;

      int ans = 0, n = 0;
      rep(i, 0, K) {
        n--;
        if (n > 0) continue;

        auto it = its[A[i]];
        if (it == P2.end()) continue;

        n = 1;
        while (n <= sz(A)) {
          if (next(it) == P2.end()) {
            it = P2.begin();
          } else {
            it++;
          }

          if (*it != A[(i + n) % sz(A)]) break;
          n++;
        }
        chmax(ans, n);
      }
      if (ans > sz(A)) {
        cout << "*\n";
      } else {
        cout << ans << '\n';
      }
    }
  }
}
