#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M, Q;
    cin >> N >> M >> Q;

    vector<int> A(N);
    for (auto &e : A) cin >> e, e--;

    vector<int> B(M);
    for (auto &e : B) cin >> e, e--;

    vector<int> index(N);
    for (int i = 0; i < N; i++) {
      index[A[i]] = i;
    }
    for (auto &e : B) {
      e = index[e];
    }

    vector<set<int>> occ(N);
    for (int i = 0; i < M; i++) {
      occ[B[i]].insert(i);
    }

    vector<int> by_index(N, M);
    multiset<int> diffs;
    for (int i = 0; i + 1 < N; i++) {
      diffs.insert(by_index[i + 1] - by_index[i]);
    }
    auto update = [&](int i) -> void {
      if (i - 1 >= 0) {
        diffs.erase(diffs.find(by_index[i] - by_index[i - 1]));
      }
      if (i + 1 < N) {
        diffs.erase(diffs.find(by_index[i + 1] - by_index[i]));
      }
      by_index[i] = occ[i].empty() ? M : *occ[i].begin();
      if (i - 1 >= 0) {
        diffs.insert(by_index[i] - by_index[i - 1]);
      }
      if (i + 1 < N) {
        diffs.insert(by_index[i + 1] - by_index[i]);
      }
    };
    for (int i = 0; i < N; i++) {
      update(i);
    }

    cout << (diffs.empty() or *diffs.begin() >= 0 ? "YA" : "TIDAK") << '\n';
    while (Q--) {
      int s, t;
      cin >> s >> t;
      s--, t--;
      t = index[t];

      occ[B[s]].erase(s);
      update(B[s]);
      B[s] = t;
      occ[B[s]].insert(s);
      update(B[s]);

      cout << (diffs.empty() or *diffs.begin() >= 0 ? "YA" : "TIDAK") << '\n';
    }
  }
}
