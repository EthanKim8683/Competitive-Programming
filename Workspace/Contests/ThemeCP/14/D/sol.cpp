#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e, e--;

    vector<int> counts(N, 0);
    int s = 1;
    counts[A[0]]++;
    counts[A[N - 1]]++;
    for (int i = 0; i + 1 < N; i++) {
      if (A[i] == A[i + 1]) {
        counts[A[i]]++;
        counts[A[i + 1]]++;
        s++;
      }
    }
    pair<int, int> t = {0, 0};
    for (int i = 0; i < N; i++) {
      t = max(t, {counts[i], i});
    }
    int u = 0;
    for (int i = 0; i + 1 < N; i++) {
      if (A[i] != A[i + 1] and A[i] != t.second and A[i + 1] != t.second) {
        u++;
      }
    }
    cout << (t.first - 1 <= s + u ? max(t.first - 1, s) - 1 : -1) << '\n';
  }
}
