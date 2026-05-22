#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<int> S(N);
  for (auto &e : S) cin >> e;

  vector<int> index(N + 1);
  for (int i = 0; i < N; i++) {
    index[S[i]] = i;
  }
  index[N] = -1;
  vector<int> T(N);
  for (int i = 0; i < N; i++) {
    T[i] = index[S[i] + 1];
  }

  int splits = 0;
  for (int i = 0; i + 1 < N; i++) {
    if (T[i + 1] < T[i]) {
      splits++;
    }
  }
  mint ans = 0;
  for (int i = 0; i <= N - 1 - splits; i++) {
    ans += binom<mint>(N - 1 - splits, i) * binom<mint>(K, splits + i + 1);
  }
  cout << ans.val();
}
