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

const int MAXX = 100;
const int MAXQ = 20;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  auto query = [&](int x) -> bool {
    cout << x << endl;
    string yn;
    cin >> yn;
    return yn == "yes";
  };

  auto answer = [&](bool y) -> void {
    cout << (y ? "prime" : "composite") << endl;
    exit(0);
  };

  vc<bool> is_prime(MAXX + 1, true);
  rep(i, 2, MAXX + 1) {
    for (int j = 2 * i; j <= MAXX; j += i) {
      is_prime[j] = false;
    }
  }

  int q = 0, n = 0;
  rep(i, 2, MAXX + 1) {
    if (!is_prime[i]) continue;
    int p = i;
    while (q < MAXQ and n < 2 and p <= MAXX) {
      q += 1;
      if (!query(p)) break;
      n += 1;
      p *= i;
    }
    if (n >= 2) answer(false);
  }
  answer(true);
}
