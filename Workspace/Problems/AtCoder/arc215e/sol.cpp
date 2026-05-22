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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // make everything 1 when possible
  //
  // do the same from B? if they're equal there is a solution?

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string A;
    cin >> A;

    string B;
    cin >> B;

    int M;
    cin >> M;

    vc<pii> ops(M);
    for (auto &[x, y] : ops) {
      cin >> x >> y;
      x--, y--;
    }

    vi self_loops(N, -1);
    rep(i, 0, M) {
      auto [a, b] = ops[i];
      if (a != b) continue;
      self_loops[a] = i;
    }

    auto norm = [&](string S) -> pair<string, vi> {
      vc<vc<pii>> adj(N);
      rep(i, 0, M) {
        auto [a, b] = ops[i];
        adj[a].eb(b, i);
      }

      queue<int> q;
      rep(i, 0, N) {
        if (S[i] != '1') continue;
        q.push(i);
      }
      vi C;
      while (sz(q) > 0) {
        int a = q.front();
        q.pop();
        for (auto [b, i] : adj[a]) {
          if (S[b] != '0') continue;
          C.pb(i);
          S[b] = '1';
          q.push(b);
        }
      }
      return {S, C};
    };

    auto [A2, C1] = norm(A);

    auto B2 = B;
    rep(i, 0, N) {
      if (A2[i] != '1') continue;
      if (self_loops[i] == -1) continue;
      B2[i] = '1';
    }
    auto [B3, C2] = norm(B2);
    vi C3;
    rep(i, 0, N) {
      if (B[i] != '0') continue;
      if (B2[i] != '1') continue;
      C3.pb(self_loops[i]);
    }

    if (A2 != B3) {
      cout << "-1\n";
      continue;
    }

    reverse(all(C2));
    vi C;
    C.insert(C.end(), all(C1));
    C.insert(C.end(), all(C2));
    C.insert(C.end(), all(C3));

    cout << sz(C) << '\n';
    for (auto e : C) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
