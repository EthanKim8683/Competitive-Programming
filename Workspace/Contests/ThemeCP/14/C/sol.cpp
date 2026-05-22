#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K, M;
    cin >> N >> K >> M;

    vector<int> B(M);
    for (auto &e : B) cin >> e, e--;

    vector<bool> seen(N, false);
    for (auto e : B) {
      seen[e] = true;
    }

    if (count(seen.begin(), seen.end(), false) % (K - 1) != 0) {
      cout << "NO\n";
      continue;
    }

    vector<int> ps(N + 1);
    ps[0] = 0;
    for (int i = 0; i < N; i++) {
      ps[i + 1] = ps[i] + !seen[i];
    }

    bool ans = false;
    for (int i = 0; i < N; i++) {
      ans = ans or (seen[i] and ps[i] >= (K - 1) / 2 and
                    ps[N] - ps[i + 1] >= (K - 1) / 2);
    }
    cout << (ans ? "YES" : "NO") << '\n';
  }
}
