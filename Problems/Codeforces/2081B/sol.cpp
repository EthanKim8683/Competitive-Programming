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
    for (auto &e : A) cin >> e;

    vector<int> bad;
    for (int i = 0; i + 1 < N; i++) {
      if (A[i] > A[i + 1]) {
        bad.push_back(i);
      }
    }
    if (bad.empty()) {
      cout << 0 << '\n';
      continue;
    }

    int L = bad[0], R = bad.back() + 1;
    cout << (A[R] - A[L] >= R - L ? (bad.size() + 1) / 2 : bad.size() / 2 + 1)
         << '\n';
  }
}
