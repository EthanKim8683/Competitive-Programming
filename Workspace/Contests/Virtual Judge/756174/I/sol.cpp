#include <bits/stdc++.h>

#include <algorithm>
using namespace std;

#define int long long
#define float long double
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
typedef pair<float, float> vec;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, M, K;
    cin >> N >> M >> K;

    vi F(N);
    for (auto &e : F) {
      cin >> e;
      e--;
    }

    vc<bool> in_F(K, false);
    for (auto e : F) {
      in_F[e] = true;
    }

    int ans0 = 0;
    vc<map<int, int>> adj(K);
    rep(i, 0, M) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a][b]++;
      if (a != b) {
        adj[b][a]++;
      }
      if (in_F[a] and in_F[b]) {
        ans0++;
      }
    }

    vi Fc;
    rep(i, 0, K) {
      if (in_F[i]) continue;
      Fc.pb(i);
    }

    vi add(K, 0);
    for (auto a : Fc) {
      for (auto [b, count] : adj[a]) {
        if (!(in_F[b] or a == b)) continue;
        add[a] += count;
      }
    }

    sort(all(Fc), [&](int a, int b) -> bool { return add[a] > add[b]; });

    auto chmax = [&](int &a, int b) -> void { a = max(a, b); };

    int ans = ans0;
    for (auto a : Fc) {
      chmax(ans, ans0 + add[a]);

      for (auto [b, count] : adj[a]) {
        if (a == b or in_F[b]) continue;
        chmax(ans, ans0 + add[a] + add[b] + count);
      }

      for (auto b : Fc) {
        if (a == b or adj[a].contains(b)) continue;
        chmax(ans, ans0 + add[a] + add[b]);
        break;
      }
    }
    cout << ans << '\n';
  }
}