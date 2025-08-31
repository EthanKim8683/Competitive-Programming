#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifdef ETHANKIM8683
  int T = 20;

  while (T--) {
    static mt19937 rng(time(nullptr));
    int K = rng() % ((50 + 1 - 2) / 2) * 2 + 2,
        N = rng() % ((K * K + 1 - K) / 2) * 2 + K;
    vector<int> A(N);
    for (auto &e : A) e = rng() % ((int) 1e9 + 1);
#else
  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;
#endif

    auto query = [&](int i) -> int {
#ifdef ETHANKIM8683
      assert(i >= 0 and i + K <= N);
      int rv = 0;
      for (int j = i; j < i + K; j++) {
        rv ^= A[j];
      }
      reverse(A.begin() + i, A.begin() + i + K);
      return rv;
#else
      cout << "? " << i + 1 << endl;
      int rv;
      cin >> rv;
      if (rv == -1) exit(0);
      return rv;
#endif
    };

    auto answer = [&](int x) -> void {
#ifdef ETHANKIM8683
      int ans = 0;
      for (auto e : A) {
        ans ^= e;
      }
      cout << N << ' ' << K << ": " << (x == ans ? "Ok" : "Wrong Answer")
           << '\n';
#else
      cout << "! " << x << endl;

#endif
    };

    int r = N % K, o = (2 * K - r) / 2;
    int ans = query(N - K) ^ query(N - 2 * K + o);
    for (int i = 0; i + K <= N - r; i += K) {
      ans ^= query(i);
    }
    answer(ans);
  }
}
/*

*/
