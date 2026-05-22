#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<string> ans;
  for (int i = 0; i < (1 << N) - 1; i++) {
    string op(1 << N, 'A');
    for (int j = 0; j < (1 << (N - 1)); j++) {
      op[(j + i) % (1 << N)] = 'B';
    }
    ans.push_back(op);
  }

#ifdef ETHANKIM8683
  int _n = -1;
  bool ok = true;
  for (int i = 0; i < (1 << N); i++) {
    for (int j = i + 1; j < (1 << N); j++) {
      int nij = 0;
      for (int k = 0; k < ans.size(); k++) {
        nij += ans[k][i] == ans[k][j];
      }
      if (_n == -1) {
        _n = nij;
      } else {
        ok = ok and _n == nij;
      }
    }
  }
  cout << (ok ? "ok" : "wa");
#else
  cout << ans.size() << '\n';
  for (auto e : ans) {
    cout << e << '\n';
  }
#endif
}
