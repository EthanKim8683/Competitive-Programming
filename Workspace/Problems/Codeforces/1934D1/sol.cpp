#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifdef ETHANKIM8683
  int T = 100;
  while (T--) {
    static mt19937_64 rng(time(nullptr));
    i64 N = rng() % (i64) 1e18 + 1, M = rng() % (N - 1) + 1;
#else
  int T;
  cin >> T;

  while (T--) {
    i64 N, M;
    cin >> N >> M;
#endif

    // 2**k <= y < x, where 2**k is the greatest power of two greater than x
    // x^y retains some bit, excluding the highest, of x. this bit becomes the
    // new highest bit. also beyond this bit, it's allowed to set any bits
    //
    // m < 2**l, where l is x's second highest bit, we can find a solution in
    // two operations: keep the second highest bit while making everything else
    // match, then remove the second highest bit
    //
    // 2**l <= m < 2**(l+1), we can find a solution in one operation: keep the
    // second highest bit and make everything else match
    //
    // 2**(l+1) <= m < 2**k is impossible to satisfy because we can't set a bit
    // ahead of l
    //
    // 2**k <= m < x is trivial

    int k = __lg(N);
    if (N == (1ll << k)) {
      cout << -1 << '\n';
      continue;
    }
    int l = __lg(N ^ (1ll << k));

    vector<i64> ans;
    if (M < (1ll << l)) {
      ans = {N, 1ll << l ^ M, M};
    } else if (M < (1ll << (l + 1))) {
      ans = {N, M};
    } else if (M < (1ll << k)) {
      cout << -1 << '\n';
      continue;
    } else {
      ans = {N, M};
    }

    cout << ans.size() - 1 << '\n';
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';

#ifdef ETHANKIM8683
    i64 x = ans[0];
    bool ok = true;
    for (int i = 1; i < ans.size(); i++) {
      i64 y = ans[i];
      ok = ok and y < x and (y ^ x) < x;
      x = y;
    }
    cerr << (ok ? "ok" : "wa") << '\n';
#endif
  }
}
