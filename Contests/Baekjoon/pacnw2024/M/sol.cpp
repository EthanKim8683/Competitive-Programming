#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<string> S(N);
  for (auto &e : S) cin >> e;

  vector<set<string>> S_(1 << N);
  for (int i = 0; i < N; i++) {
    S_[1 << i].insert(S[i]);
  }
  for (int i = 0; i < (1 << N); i++) {
    for (int j = (i + 1) | i; j < (1 << N); j = (j + 1) | i) {
      int k = j ^ i;
      for (auto ei : S_[i]) {
        for (auto ek : S_[k]) {
          for (int l = min(ei.size(), ek.size()); l > 0; l--) {
            if (ei.substr(ei.size() - l) == ek.substr(0, l)) {
              S_[j].insert(ei + ek.substr(l));
            }
          }
          for (int l = min(ek.size(), ei.size()); l > 0; l--) {
            if (ek.substr(ek.size() - l) == ei.substr(0, l)) {
              S_[j].insert(ek + ei.substr(l));
            }
          }
        }
      }
    }
  }
  if (S_[(1 << N) - 1].empty()) {
    cout << -1;
    exit(0);
  }
  pair<int, string> ans = {INF, ""};
  for (auto e : S_[(1 << N) - 1]) {
    ans = min(ans, {e.size(), e});
  }
  cout << ans.second;
}