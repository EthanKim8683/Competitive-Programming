#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    string S;
    cin >> S;

    int X = count(S.begin(), S.end(), '1'), g = gcd(X, N), x = X / g, n = N / g;
    if (M % n != 0) {
      cout << "-1\n";
      continue;
    }
    X = M / n * x;

    // if S was cyclic, we could always find a solution with K = 1 via IVT
    //
    // since it's not, the worst case is two subarrays forming the overflowing
    // single subarray

    vector<int> ps(2 * N + 1);
    ps[0] = 0;
    for (int i = 0; i < 2 * N; i++) {
      ps[i + 1] = ps[i] + (S[i % N] == '1');
    }

    pair<int, int> ans = {INF, -1};
    for (int i = 0; i < N; i++) {
      if (ps[i + M] - ps[i] == X) {
        ans = min(ans, {1 + (i + M > N), i});
      }
    }

    auto [k, i] = ans;
    cout << k << '\n';
    if (i + M > N) {
      cout << 1 << ' ' << i + M - N << '\n';
    }
    cout << i + 1 << ' ' << min(i + M, N) << '\n';
  }
}
