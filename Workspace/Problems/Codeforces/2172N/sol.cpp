#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  // make a tree based on B, try to meet K quota
  // add N - (B + 1) nodes in a loop
  // add edges between nodes in the loop
  //
  // K % 2 == 1 is impossible
  // N - (B + 1) == 2 and K > N - 2 is impossible
  // N - (B + 1) == 1 is impossible
  //
  // start with tree based on parity of B + 1
  // add nodes in pairs? increase odd by 0 or 2

  int T;
  if (argc > 1) {
    T = 100;
  } else {
    cin >> T;
  }

  while (T--) {
    int N, K, B;
    if (argc > 1) {
      N = rng() % (int) 1e5 + 1;
      K = rng() % (N + 1);
      B = rng() % N;
    } else {
      cin >> N >> K >> B;
    }

    bool ok = true;
    ok = ok and !(K % 2 == 1);
    ok = ok and !(N - (B + 1) == 2 and K > N - 2);  // rethink this case
    ok = ok and !(N - (B + 1) == 1);
    if (!ok) {
      if (argc > 1) {
      } else {
        cout << "No\n";
      }
      continue;
    }

    vector<vector<int>> adj = {{}};
    int n = 1, k = 0;
    auto add_edge = [&](int a, int b) -> void {
      k -= adj[a].size() % 2;
      k -= adj[b].size() % 2;
      adj[a].push_back(b);
      adj[b].push_back(a);
      k += adj[a].size() % 2;
      k += adj[b].size() % 2;
    };
    auto add_node = [&](int p) -> void {
      adj.emplace_back();
      add_edge(p, n);
      n++;
    };
    if ((B + 1) % 2 == 0) {
      add_node(n - 1);
    }
    while (n < B + 1) {
      if (k + 2 <= K) {
        int p = n - 1;
        add_node(p);
        add_node(p);
      } else {
        add_node(n - 1);
        add_node(n - 1);
      }
    }
    if (N - (B + 1) == 2) {
      add_node(n - 1);
      add_node(n - 1);
      add_edge(n - 3, n - 1);
    } else {
      int r = 0;
      for (int i = 0; i < n; i++) {
        if (adj[i].size() % 2 != 0) continue;
        r = i;
        break;
      }
      vector<int> loop;
      int p = r;
      while (n < N) {
        add_node(p);
        p = n - 1;
        loop.push_back(n - 1);
      }
      add_edge(p, r);
      if (adj[r].size() % 2 == 0) {
        loop.push_back(r);
      }
      int m = loop.size() / 2;
      for (int i = 0; i < m; i++) {
        if (k + 2 <= K) {
          add_edge(loop[i], loop[i + m]);
        }
      }
    }

    if (argc > 1) {
      assert(n == N);
      assert(k == K);
      vector<bool> seen(N, false);
      vector<int> tin(N), tmin(N);
      int t = 0, b = 0;
      auto dfs = [&](auto self, int a, int p) -> void {
        seen[a] = true;
        tin[a] = tmin[a] = t++;
        for (auto b : adj[a]) {
          if (b == p) continue;
          if (seen[b]) {
            tmin[a] = min(tmin[a], tin[b]);
          } else {
            self(self, b, a);
            tmin[a] = min(tmin[a], tmin[b]);
            if (tmin[b] > tin[a]) {
              b++;
            }
          }
        }
      };
      dfs(dfs, 0, -1);
      assert(b == B);
      assert(find(seen.begin(), seen.end(), false) == seen.end());
      for (int i = 0; i < N; i++) {
        sort(adj[i].begin(), adj[i].end());
        for (int j = 0; j + 1 < adj[i].size(); j++) {
          assert(adj[i][j] != adj[i][j + 1]);
        }
      }
    } else {
      cout << "Yes\n";
      for (int a = 0; a < N; a++) {
        for (auto b : adj[a]) {
          if (b < a) continue;
          cout << a + 1 << ' ' << b + 1 << '\n';
        }
      }
    }
  }
}
