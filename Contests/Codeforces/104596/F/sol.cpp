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

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vi K(N);
  for (auto &e : K) cin >> e;

  vi bit(N + 1, 0);
  auto add = [&](int i, int v) -> void {
    for (i += 1; i <= N; i += i & -i) {
      bit[i] += v;
    }
  };
  auto sum = [&](int i) -> int {
    int rv = 0;
    for (; i > 0; i -= i & -i) {
      rv += bit[i];
    }
    return rv;
  };

  auto ith = [&](int i) -> int {
    int l = 0, r = N;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      sum(m) <= i ? l = m : r = m - 1;
    }
    return l;
  };

  rep(i, 0, N) { add(i, 1); }
  int f = 0;
  rep(i, 0, N - 1) {
    int j = ith(f);
    // cout << "Start at " << j << " (f = " << f << ")" << endl;
    (f += K[j] - 1) %= sum(N);
    int k = ith(f);
    // cout << " Kill " << k << endl;
    add(k, -1);
    // deleted the last one
    if (f == sum(N)) {
      f = 0;
    } else {
      // no need to do f++ since it's automatically moved up one
      // f++;
    }
  }
  assert(f == 0);
  cout << ith(0) + 1;
}