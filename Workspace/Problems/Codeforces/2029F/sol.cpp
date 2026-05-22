#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string C;
    cin >> C;

    // I've looked at the editorial for this problem before, but I figured I'd
    // forgotten enough of it to give it another go.

    set<char> S;
    for (int i = 0; i < N; i++) {
      if (C[i] == C[(i + 1) % N]) {
        S.insert(C[i]);
      }
    }
    if (S.empty() or (S.contains('R') and S.contains('B'))) {
      cout << "NO\n";
      continue;
    }

    if (S.contains('B')) {
      for (auto &e : C) {
        e = e == 'B' ? 'R' : 'B';
      }
    }

    if (C == string(N, 'R')) {
      cout << "YES\n";
      continue;
    }

    vector<int> counts(2, 0);
    int i0 = find(C.begin(), C.end(), 'B') - C.begin(), j = 0;
    for (int i = 0; i < N; i++) {
      if (C[(i + i0) % N] == 'B') {
        if (j < i) {
          counts[(i - j) % 2]++;
        }
        j = i + 1;
      }
    }
    if (j < N) {
      counts[(N - j) % 2]++;
    }

    cout << ((counts[0] == 1 or counts[1] <= 1) and counts[0] <= 1 ? "YES"
                                                                   : "NO")
         << '\n';
  }
}
