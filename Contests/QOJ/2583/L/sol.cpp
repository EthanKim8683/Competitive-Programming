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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vc<pii> problems(N);
  for (auto &[i, t] : problems) {
    cin >> i >> t;
  }

  auto check = [&](int a0, int b0) -> bool {
    int da = 0, db = 0;
    rep(i, 0, N) {
      auto [a, b] = problems[i];
      da = max(da, a - a0);
      db = max(db, b - b0);
      if (da + db > i) return false;
    }
    return true;
  };

  auto find_a = [&](int b) -> int {
    int l = 0, r = INF;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m, b) ? r = m : l = m + 1;
    }
    return l;
  };

  auto find_b = [&](int a) -> int {
    int l = 0, r = INF;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(a, m) ? r = m : l = m + 1;
    }
    return l;
  };

  int l = find_a(INF), r = find_a(find_b(INF)), ans = INF + INF;
  rep(i, l, r + 1) { chmin(ans, i + find_b(i)); }
  cout << ans;
}
