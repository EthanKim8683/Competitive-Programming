#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string S;
    cin >> S;

    vector<int> ones;
    for (int i = 0; i < N; i++) {
      if (S[i] == '1') {
        ones.push_back(i);
      }
    }

    if (ones.size() % 2 != 0 or ones.size() == 0) {
      cout << "NO\n";
      continue;
    }

    vector<pair<int, int>> ans;
    if (ones.size() == 2 and ones[1] - ones[0] == 1) {
      for (int i = 0; i < N - 1; i++) {
        ans.push_back({(ones[1] + i) % N, (ones[1] + i + 1) % N});
      }
    } else {
      vector<int> adj(N);
      for (int i = ones[0] + 1; i < ones.back() - 1; i++) {
        adj[i] = i + 1;
      }
      adj[0] = ones[0] + 1;
      for (int i = 1; i + 1 < ones.size(); i += 2) {
        adj[ones[i] == ones[0] + 1 ? 0 : ones[i] - 1] = ones[i + 1];
      }
      for (int i = ones[0] + 1; i < ones.back() - 1; i++) {
        ans.push_back({i, adj[i]});
      }
      ans.push_back({0, adj[0]});
      ans.push_back({ones.back() - 1, N - 1});
      for (int i = 0; i < ones[0]; i++) {
        ans.push_back({i, i + 1});
      }
      for (int i = ones.back(); i < N - 1; i++) {
        ans.push_back({i, i + 1});
      }
    }

    cout << "YES\n";
    for (auto [a, b] : ans) {
      cout << a + 1 << ' ' << b + 1 << '\n';
    }

#ifdef ETHANKIM8683
    vector<int> deg(N, 0);
    for (auto [a, b] : ans) {
      (deg[a] += 1) %= 2;
      (deg[b] += 1) %= 2;
    }
    for (auto e : deg) {
      cerr << e << ' ';
    }
    cerr << '\n';
    bool ok = true;
    for (int i = 0; i < N; i++) {
      ok = ok and deg[i] + '0' == S[i];
    }
    cerr << (ok ? "ok" : "wa") << '\n';
#endif
  }
}
