#pragma GCC optimize("Ofast,unroll-loops")
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

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(2 * N);
    for (auto &e : A) {
      cin >> e;
      e--;
    }

    vi totals(2 * N, 0);
    for (auto e : A) {
      totals[e]++;
    }

    int case1 = 0, case2 = 0, case3 = 0;
    for (auto e : totals) {
      if (e == 0) continue;
      if (e % 2 == 1) {
        case1++;
      } else {
        if (e / 2 % 2 == 0) {
          case2++;
        } else {
          case3++;
        }
      }
    }
    if (case1 >= 1) {
      cout << case1 + case2 * 2 + case3 * 2 << '\n';
    } else {
      cout << case2 / 2 * 4 + case3 * 2 << '\n';
    }
  }
}
