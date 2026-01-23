#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5;

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int Q;
  if (argc > 1) {
    Q = 1;
  } else {
    cin >> Q;
  }

  while (Q--) {
    int N, K;
    if (argc > 1) {
      N = rng() % MAXN;
      K = rng() % N;
    } else {
      cin >> N >> K;
      K--;
    }

    int ans = 0, b = 1, e = N - 1, k = K, i = 0;
    while (e > 0) {
      int n = e + 1, m = b == 0 ? (n + 1) / 2 : n / 2;
      if (k < m) {
        ans |= (k << 1 | b) << i;
        break;
      }
      ans |= (b ^ 1) << i;
      tie(b, e, k, i) = make_tuple((b ^ m ^ (n - m)) & 1,
                                   (e - ((e & 1) == b)) >> 1, k - m, i + 1);
    }
    if (argc > 1) {
      list<int> A(N);
      iota(A.begin(), A.end(), 0);
      auto it = next(A.begin());
      if (it == A.end()) {
        it = A.begin();
      }
      for (int i = 0; i < K; i++) {
        it = A.erase(it);
        if (it == A.end()) {
          it = A.begin();
        }
        it = next(it);
        if (it == A.end()) {
          it = A.begin();
        }
      }
      assert(*it == ans);
    } else {
      ans++;
      cout << ans << '\n';
    }
  }
}
