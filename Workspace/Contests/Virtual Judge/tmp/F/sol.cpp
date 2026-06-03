#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
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

struct FT {
  vector<ll> s;
  FT(int n) : s(n) {}
  void update(int pos, ll dif) {  // a[pos] += dif
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) {  // sum of values in [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
  int lower_bound(ll sum) {  // min pos st sum of [0, pos] >= sum
    // Returns n if no sum is >= sum, or -1 if empty sum is.
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
        pos += pw, sum -= s[pos - 1];
    }
    return pos;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vc<pii> ranges(N);
  for (auto &[l, r] : ranges) {
    cin >> l >> r;
    l--;
  }

  vi cc;
  for (auto [l, r] : ranges) {
    cc.pb(l);
    cc.pb(r);
  }
  sort(all(cc));
  cc.erase(unique(all(cc)), cc.end());
  for (auto &[l, r] : ranges) {
    l = lower_bound(all(cc), l) - cc.begin();
    r = lower_bound(all(cc), r) - cc.begin();
  }

  int ans = 0;
  sort(all(ranges));

  FT ft(sz(cc) + 1);
  for (auto [l, r] : ranges) {
    ans += ft.query(sz(cc) + 1) - ft.query(l + 1);
    ft.update(r, 1);
  }
  cout << ans << '\n';
}
