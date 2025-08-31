#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K, Q;
    cin >> N >> K >> Q;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<pair<int, int>> queries(Q);
    for (auto &[l, r] : queries) {
      cin >> l >> r;
      l--;
      r -= K - 1;
    }

    vector<int> f(N - K + 1);
    map<int, int> D;
    multiset<int> counts;
    auto update = [&](int x, int dc) -> void {
      if (counts.contains(D[x])) {
        counts.erase(counts.find(D[x]));
      }
      D[x] += dc;
      counts.insert(D[x]);
    };
    for (int i = 0; i < K; i++) {
      update(A[i] - i, 1);
    }
    for (int i = 0; i + K <= N; i++) {
      f[i] = K - *counts.rbegin();

      update(A[i] - i, -1);
      if (i + K < N) {
        update(A[i + K] - (i + K), 1);
      }
    }

    int sqrtN = sqrt(N);

    vector<int> blocks(N - K + 1);
    for (int i = 0; i + sqrtN <= N - K + 1; i += sqrtN) {
      blocks[i] = f[i];
      for (int j = i + 1; j < i + sqrtN; j++) {
        blocks[j] = min(blocks[j - 1], f[j]);
      }
    }

    vector<i64> ps(N - K + 2);
    ps[0] = 0;
    for (int i = 0; i < N - K + 1; i++) {
      ps[i + 1] = ps[i] + blocks[i];
    }

    auto ceil_div = [&](int x, int y) -> int {
      return x <= 0 ? x / y : (x - 1) / y + 1;
    };

    for (auto [l, r] : queries) {
      int mf = INF, ls = min(ceil_div(l, sqrtN) * sqrtN, r),
          rs = max(r / sqrtN * sqrtN, ls);
      i64 ans = 0;
      for (int i = l; i < ls; i++) {
        mf = min(mf, f[i]);
        ans += mf;
      }
      for (int i = ls; i + sqrtN <= rs; i += sqrtN) {
        int j = upper_bound(blocks.begin() + i, blocks.begin() + i + sqrtN, mf,
                            greater{}) -
                blocks.begin();
        ans += (i64) (j - i) * mf + ps[i + sqrtN] - ps[j];
        mf = min(mf, blocks[i + sqrtN - 1]);
      }
      for (int i = rs; i < r; i++) {
        mf = min(mf, f[i]);
        ans += mf;
      }
      cout << ans << '\n';
    }
  }
}
/*

*/
