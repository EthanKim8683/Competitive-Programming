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

const int MAXG = 2e5;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 8:15
  // thinking done: 8:27
  // target impl time:
  // initial impl done: 8:53

  // the difference in the sums of G's must be divisible by the gcd sum of R's

  int N;
  cin >> N;

  vc<pii> blueprints(N);
  for (auto &[G, R] : blueprints) {
    cin >> G >> R;
  }

  int g = 0;
  for (auto [G, R] : blueprints) {
    g = gcd(g, R);
  }

  int sum = 0;
  vi counts(2 * MAXG + 1, 0);
  bool has_zero = false;
  for (auto [G, R] : blueprints) {
    sum += G;
    counts[2 * G] += 1;
    has_zero = has_zero or G == 0;
  }
  bitset<2 * MAXG + 1> bs;
  bs[MAXG - sum] = 1;
  rep(i, 0, 2 * MAXG + 1) {
    if (counts[i] == 0) continue;

    if (counts[i] % 2 == 0) {
      bs |= bs << i;
      bs |= bs << i;
      counts[2 * i] += (counts[i] - 2) / 2;
    } else {
      bs |= bs << i;
      counts[2 * i] += (counts[i] - 1) / 2;
    }
  }
  int r = has_zero ? sum : sum - 1;
  rep(i, MAXG - r, MAXG + r + 1) {
    if (!bs[i]) continue;
    if ((i - MAXG) % g == 0) {
      cout << "Y\n";
      exit(0);
    }
  }
  cout << "N\n";
}
