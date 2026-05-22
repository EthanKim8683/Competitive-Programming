#include <bits/stdc++.h>

#include <tr2/dynamic_bitset>

using namespace std;
using namespace tr2;

using u64 = unsigned long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // xor swap or just xor
  //
  // reorder arbitrarily
  // xor arbitrarily
  //
  // same span
  //
  // O(PQ\min(P,Q))

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string S;
    cin >> S;

    string T;
    cin >> T;

    int P = 1 << __builtin_ctz(N), Q = N / P;

    auto reshape = [&](string s) -> vector<dynamic_bitset<u64>> {
      vector rv(P, dynamic_bitset<u64>(Q));
      for (int i = 0; i < N; i++) {
        rv[i / Q][i % Q] = s[i] == '1';
      }
      return rv;
    };
    auto vectors1 = reshape(S), vectors2 = reshape(T);

    auto reduce = [&](vector<dynamic_bitset<u64>> &vectors) -> void {
      for (int i = 0; i < P; i++) {
        pair<int, int> best = {Q, -1};
        for (int j = i; j < P; j++) {
          best = min(best, {vectors[j].find_first(), j});
        }
        auto [f, s] = best;
        if (f == Q) break;
        swap(vectors[i], vectors[s]);
        for (int j = 0; j < P; j++) {
          if (j == i) continue;
          if (!vectors[j][f]) continue;
          vectors[j] ^= vectors[i];
        }
      }
    };
    reduce(vectors1);
    reduce(vectors2);

    cout << (vectors1 == vectors2 ? "Yes" : "No") << '\n';
  }
}
