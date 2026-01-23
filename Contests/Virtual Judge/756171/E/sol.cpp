#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<int> V(N);
  for (auto &e : V) cin >> e;

  // 2^k - 1 <= N
  // 2^k <= N + 1
  // k <= log2(N + 1)
  // k <= floor(log2(N + 1))

  int K_ = min(K, __lg(N + 1) + 1);
  vector<int> P(K_);
  iota(P.begin(), P.end(), 1);
  do {
    int i = 0;
    for (auto e : V) {
      if (i < P.size() and e == P[i]) {
        i++;
      }
    }
    if (i < P.size()) {
      for (auto e : P) {
        cout << e << ' ';
      }
      for (int j = P.size() + 1; j <= K; j++) {
        cout << j << ' ';
      }
      exit(0);
    }
  } while (next_permutation(P.begin(), P.end()));
  cout << "*";
}