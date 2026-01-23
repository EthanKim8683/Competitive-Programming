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
    int N, K;
    cin >> N >> K;

    vi Q(N);
    for (auto &e : Q) cin >> e;

    vi R(N);
    for (auto &e : R) cin >> e;
    sort(all(R));
    reverse(all(R));

    multiset<int> S(all(Q));
    int ans = 0;
    for (auto e : R) {
      auto it = S.upper_bound((K - e) / (e + 1));
      if (it == S.begin()) continue;
      S.erase(prev(it));
      ans++;
    }
    cout << ans << '\n';
  }
}
