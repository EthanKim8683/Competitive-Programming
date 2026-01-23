#include <bits/stdc++.h>

#include "atcoder/string"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int K, T;
  cin >> K >> T;
  T %= K;

  int N = 1 << K;

  string S;
  cin >> S;

  auto riffle = [&](string S) -> string {
    string rv(N, ' ');
    for (int i = 0; i < N / 2; i++) {
      rv[2 * i] = S[i];
      rv[2 * i + 1] = S[N / 2 + i];
    }
    return rv;
  };
  for (int i = 0; i < T; i++) {
    S = riffle(S);
  }

  int M = 1 << T;

  string S2;
  for (int i = 0; i < N; i += M) {
    S2 += S.substr(i, M);
    S2 += S.substr(i, M);
  }
  auto order = suffix_array(S2);

  vector<int> value(2 * N);
  auto lcp = lcp_array(S2, order);
  int t = 0;
  for (int i = 0; i < 2 * N; i++) {
    if (i - 1 >= 0 and lcp[i - 1] < M) {
      t++;
    }
    value[order[i]] = t;
  }

  vector<int> A;
  for (int i = 0; i <= M; i++) {
    for (int j = 0; j < N / M; j++) {
      A.push_back(j * (2 * M) + i);
    }
  }

  vector<int> A2;
  for (auto e : A) {
    A2.push_back(value[e]);
  }
  auto order2 = suffix_array(A2);

  int l;
  for (auto e : order2) {
    if (e > N) continue;
    l = e;
    break;
  }

  for (int i = l; i < l + N / M; i++) {
    cout << S2.substr(A[i], M);
  }
}
