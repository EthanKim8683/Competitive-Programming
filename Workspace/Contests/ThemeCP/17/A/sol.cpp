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

    string T;
    cin >> T;

    auto solve = [&](string A, string B) -> string {
      for (int i = 0; i + 2 < A.size(); i++) {
        if (A[i] == '0' and A[i + 2] == '0') {
          B[i + 1] = '1';
        }
      }
      for (int i = 0; i + 2 < B.size(); i++) {
        if (B[i] == '1' and B[i + 2] == '1') {
          A[i + 1] = '1';
        }
      }
      return A;
    };
    auto A = solve(S, T);
    vector<int> ps(N + 1, 0);
    for (int i = 0; i < N; i++) {
      ps[i + 1] = ps[i] + (A[i] == '1');
    }

    int Q;
    cin >> Q;

    int K1 = 10, K2 = 5;
    while (Q--) {
      int l, r;
      cin >> l >> r;
      l--;

      if (r - l < 2 * K1) {
        auto A = solve(S.substr(l, r - l), T.substr(l, r - l));
        cout << count(A.begin(), A.end(), '1') << '\n';
      } else {
        auto A1 = solve(S.substr(l, K1), T.substr(l, K1)),
             A2 = solve(S.substr(r - K1, K1), T.substr(r - K1, K1));
        cout << count(A1.begin(), A1.begin() + K2, '1') +
                    count(A2.end() - K2, A2.end(), '1') + ps[r - K2] -
                    ps[l + K2]
             << '\n';
      }
    }
  }
}
