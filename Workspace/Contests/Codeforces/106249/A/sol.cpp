#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    string S;
    cin >> S;

    int N = S.size();

    dsu d(N);
    for (int i = 0; i + 1 < N; i++) {
      if ((S[i] == 'I') != (S[i + 1] == 'I')) {
        d.merge(i, i + 1);
      }
    }
    vector<int> M(N), T(N);
    for (int i = 0; i < N; i++) {
      int a = d.leader(i);
      if (S[i] == 'M') {
        M[a]++;
      } else if (S[i] == 'T') {
        T[a]++;
      }
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
      ans += min(M[i], T[i] / 2);
    }
    cout << ans << '\n';
  }
}
