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
typedef vector<int> vi;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  auto count = [&](vc<vi> adj) -> int {
    vi indegree1(N, 0);
    for (auto r : adj) {
      for (auto e : r) {
        indegree1[e]++;
      }
    }

    vi dp(1 << N, 0);
    dp[0] = 1;
    rep(i, 0, 1 << N) {
      auto indegree2 = indegree1;
      rep(j, 0, N) {
        if (~i >> j & 1) continue;
        for (auto e : adj[j]) {
          indegree2[e]--;
        }
      }

      rep(j, 0, N) {
        if (i >> j & 1) continue;
        if (indegree2[j] != 0) continue;
        dp[i | 1 << j] += dp[i];
      }
    }
    return dp[(1 << N) - 1];
  };

  auto boundary = [&](vc<vi> adj) -> pair<vi, vi> {
    auto toposort = [&](auto cmp) -> vi {
      vi indegree(N, 0);
      for (auto r : adj) {
        for (auto e : r) {
          indegree[e]++;
        }
      }

      priority_queue<int, vi, decltype(cmp)> pq(cmp);
      auto nudge = [&](int a) -> void {
        if (indegree[a] != 0) return;
        indegree[a] = -1;
        pq.push(a);
      };
      rep(i, 0, N) { nudge(i); }
      vi rv;
      while (sz(pq) > 0) {
        int a = pq.top();
        pq.pop();
        rv.pb(a);
        for (auto b : adj[a]) {
          indegree[b]--;
          nudge(b);
        }
      }
      return rv;
    };
    return {toposort([&](int a, int b) -> bool { return a < b; }),
            toposort([&](int a, int b) -> bool { return a > b; })};
  };

  vc<vi> adj1(N);
  int count1 = 1;
  for (int i = 1; i <= N; i++) {
    count1 *= i;
  }
  while (true) {
    char t;
    cin >> t;

    if (t == '?') {
      int i, j;
      cin >> i >> j;
      i--, j--;

      auto adj2 = adj1;
      adj2[i].pb(j);
      int count2 = count(adj2);
      if (count2 > count1 - count2) {
        cout << '<' << endl;
        adj1[i].pb(j);
        count1 = count2;
      } else {
        cout << '>' << endl;
        adj1[j].pb(i);
        count1 = count1 - count2;
      }
    } else {
      vi ord(N);
      for (auto &e : ord) {
        cin >> e;
        e--;
      }

      auto [p1, p2] = boundary(adj1);
      cout << "! ";
      for (auto e : (p1 == ord ? p2 : p1)) {
        cout << e + 1 << ' ';
      }
      cout << endl;
      exit(0);
    }
  }
}
