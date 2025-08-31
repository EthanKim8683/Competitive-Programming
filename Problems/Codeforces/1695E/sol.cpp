#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<pair<int, int>> dominos(N);
  for (auto &[x, y] : dominos) {
    cin >> x >> y;
    x--, y--;
  }

  vector<multiset<int>> adj(2 * N);
  for (auto [x, y] : dominos) {
    adj[x].insert(y);
    if (x != y) {
      adj[y].insert(x);
    }
  }

  vector<bool> seen(2 * N, false);
  auto dfs = [&](auto self, int a) -> int {
    if (seen[a]) return 0;
    seen[a] = true;
    int rv = 0;
    for (auto b : adj[a]) {
      if (a <= b) {
        rv++;
      }
      rv += self(self, b);
    }
    return rv;
  };
  for (int i = 0; i < 2 * N; i++) {
    if (dfs(dfs, i) == 1) {
      cout << -1;
      exit(0);
    }
  }

  vector<vector<int>> A(2);
  vector<string> B(2), C(2);
  auto append = [&](vector<int> a1, vector<int> a2, string b1, string b2,
                    string c1, string c2) -> void {
    for (auto e : a1) {
      A[0].push_back(e);
    }
    for (auto e : a2) {
      A[1].push_back(e);
    }
    B[0] += b1;
    B[1] += b2;
    C[0] += c1;
    C[1] += c2;
  };
  for (int a = 0; a < 2 * N; a++) {
    if (adj[a].size() == 1) continue;
    while (adj[a].size() >= 2) {
      auto erase = [&](int a, int b) -> void {
        adj[a].erase(adj[a].find(b));
        if (a != b) {
          adj[b].erase(adj[b].find(a));
        }
      };
      int b = *adj[a].begin();
      erase(a, b);
      int c = *adj[a].begin();
      erase(a, c);
      vector<int> S = {a, b, c};
      bool m = false;
      if (adj[a].size() == 1) {
        int d = *adj[a].begin();
        if (adj[d].size() == 1) {
          m = true;
          erase(a, d);
          S.push_back(d);
        }
      }
      bool l = false;
      if (adj[b].size() == 1) {
        int d = *adj[b].begin();
        if (adj[d].size() == 1) {
          l = true;
          erase(b, d);
          S.push_back(d);
        }
      }
      bool r = false;
      if (adj[c].size() == 1) {
        int d = *adj[c].begin();
        if (adj[d].size() == 1) {
          r = true;
          erase(c, d);
          S.push_back(d);
        }
      }
      if (m) {
        if (l and r) {
          append({S[4], S[1], S[0], S[2], S[5]}, {S[1], S[0], S[3], S[0], S[2]},
                 "ULRUU", "DLRDD", "LRULR", "LRDLR");
        } else if (l) {
          append({S[0], S[3], S[0], S[1]}, {S[2], S[0], S[1], S[4]}, "LRLR",
                 "LRLR", "UUUU", "DDDD");
        } else if (r) {
          append({S[0], S[3], S[0], S[2]}, {S[1], S[0], S[2], S[4]}, "LRLR",
                 "LRLR", "UUUU", "DDDD");
        } else {
          append({S[0], S[3], S[0]}, {S[1], S[0], S[2]}, "LRU", "LRD", "ULR",
                 "DLR");
        }
      } else {
        if (l and r) {
          append({S[3], S[1], S[0], S[2]}, {S[1], S[0], S[2], S[4]}, "ULRU",
                 "DLRD", "LRLR", "LRLR");
        } else if (l) {
          append({S[3], S[1], S[0]}, {S[1], S[0], S[2]}, "ULR", "DLR", "LRU",
                 "LRD");
        } else if (r) {
          append({S[1], S[0], S[2]}, {S[0], S[2], S[3]}, "ULR", "DLR", "LRU",
                 "LRD");
        } else {
          append({S[1], S[0]}, {S[0], S[2]}, "LR", "LR", "UU", "DD");
        }
      }
    }
  }
  cout << 2 << ' ' << A[0].size() << '\n';
  for (auto r : A) {
    for (auto e : r) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
  for (auto e : B) {
    cout << e << '\n';
  }
  for (auto e : C) {
    cout << e << '\n';
  }
}
