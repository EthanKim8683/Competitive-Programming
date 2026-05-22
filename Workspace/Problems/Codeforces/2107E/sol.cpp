#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int MAXN = 1e5;

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  mt19937_64 rng;
  if (argc > 1) {
    rng = mt19937_64(atoi(argv[1]));
  }

  int T;
  if (argc > 1) {
    T = 1;
  } else {
    cin >> T;
  }

  while (T--) {
    int N;
    i64 K;
    if (argc > 1) {
      N = rng() % (MAXN - 1) + 2;
      K = rng() % ((i64) N * (N - 1) * (N - 2) / 6 + 2);
    } else {
      cin >> N >> K;
    }

    if (argc > 1) {
      cerr << N << ' ' << K << '\n';
    }

    if ((i64) N * (N - 1) * (N - 2) / 6 < K - 1) {
      assert(!(argc > 1));
      cout << "No\n";
      continue;
    }

    auto triangle = [&](int x) -> i64 { return (i64) x * (x - 1) / 2; };

    vector<int> layers;
    i64 K2 = K;
    while (K2 > 1) {
      auto check = [&](int x) -> bool { return triangle(x) <= K2 + 1; };
      int l = 0, r = layers.empty() ? N - 1 : layers.back() - 1;
      while (l < r) {
        int m = l + (r - l + 1) / 2;
        check(m) ? l = m : r = m - 1;
      }
      layers.push_back(l);
      K2 -= triangle(l);
    }
    reverse(layers.begin(), layers.end());

    vector<pair<int, int>> edges;
    int n = 1, r = 0;
    for (auto e : layers) {
      while (n < e) {
        edges.emplace_back(r, n);
        n++;
      }
      edges.emplace_back(n, r);
      r = n;
      n++;
    }
    while (n < N) {
      edges.emplace_back(r, n);
      n++;
    }

    auto reroot = [&](int a) -> int {
      if (a == 0) return r;
      if (a == r) return 0;
      return a;
    };
    for (auto &[a, b] : edges) {
      a = reroot(a);
      b = reroot(b);
    }

    if (argc > 1) {
      assert(edges.size() == N - 1);
      vector<vector<int>> adj(N);
      for (auto [a, b] : edges) {
        adj[a].push_back(b);
        adj[b].push_back(a);
      }

      i64 weight = 0;
      auto dfs = [&](auto self, int a, int p, int d) -> int {
        int rv = 1;
        for (auto b : adj[a]) {
          if (b == p) continue;
          int s = self(self, b, a, d + 1);
          weight += (i64) d * rv * s;
          rv += s;
        }
        return rv;
      };
      dfs(dfs, 0, -1, 0);

      assert(abs(weight - K) <= 1);
    } else {
      cout << "Yes\n";
      for (auto [a, b] : edges) {
        cout << a + 1 << ' ' << b + 1 << '\n';
      }
    }
  }
}
