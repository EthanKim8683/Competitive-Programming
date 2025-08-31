#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    int sum = 0;
    for (int l = 0; l + 1 <= N; l++) {
      for (int r = l + 1; r <= N; r++) {
      }
    }
    cout << sum << '\n';
  }
}
