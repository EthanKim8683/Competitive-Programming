#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/data_structures.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int K, _A, _H;
  cin >> K >> _A >> _H;
  mint A = _A, H = _H;

  auto f = [&](int x) -> int { return x == 0 ? 1 : (1 << (x - 1)) + 1; };

  vector<mint> pows(f(K) + 1);
  pows[0] = 1;
  for (int i = 1; i < pows.size(); i++) {
    pows[i] = pows[i - 1] * A;
  }

  auto hash_lower = [&](vector<int> P) -> mint {
    mint rv = 0;
    for (int i = 0; i < P.size(); i++) {
      rv += (i + 1) * pows[P[i]];
    }
    return rv;
  };

  auto hash_upper = [&](vector<int> P) -> mint {
    mint rv = 0;
    for (int i = 0; i < P.size(); i++) {
      rv += ((1 << (K - 1)) + i + 1) * pows[P[i]];
    }
    return rv;
  };

  hash_table<int, int> lower, upper;
  vector<vector<int>> Q;
  for (int i = 0; i < (1 << ((1 << (K - 1)) - 1)); i++) {
    vector<int> S(1 << (K - 1)), P(1 << (K - 1));
    iota(S.begin(), S.end(), 0);
    int s = K, t = 0;
    while (S.size() > 1) {
      vector<int> S_;
      for (int j = 0; j < S.size(); j += 2) {
        int k = i >> t++ & 1;
        P[S[j + k]] = f(s);
        S_.push_back(S[j + 1 - k]);
      }
      S = S_;
      s--;
    }
    P[S[0]] = f(s);
    Q.push_back(P);

    lower.insert({hash_lower(P).val(), i});
    upper.insert({hash_upper(P).val(), i});
  }

  for (auto [_h, i] : upper) {
    auto P = Q[i];
    *find(P.begin(), P.end(), f(1)) = f(0);
    mint h = hash_upper(P);

    auto it = lower.find((H - h).val());
    if (it != lower.end()) {
      int j = it->second;
      for (auto e : Q[j]) {
        cout << e << ' ';
      }
      for (auto e : P) {
        cout << e << ' ';
      }
      exit(0);
    }
  }

  for (auto [_h, i] : lower) {
    auto P = Q[i];
    *find(P.begin(), P.end(), f(1)) = f(0);
    mint h = hash_lower(P);

    auto it = upper.find((H - h).val());
    if (it != upper.end()) {
      int j = it->second;
      for (auto e : P) {
        cout << e << ' ';
      }
      for (auto e : Q[j]) {
        cout << e << ' ';
      }
      exit(0);
    }
  }

  cout << -1;
}
