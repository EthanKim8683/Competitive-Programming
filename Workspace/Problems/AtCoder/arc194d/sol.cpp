#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;
using i64 = long long;

const i64 BASE = 6969;
const i64 MOD = (1ll << 31) - 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  string S;
  cin >> S;

  int t = 0;
  vector<int> stack;
  vector<vector<int>> adj;
  adj.push_back({});
  stack.push_back(t++);
  for (auto e : S) {
    if (e == '(') {
      adj[stack.back()].push_back(t);
      adj.push_back({});
      stack.push_back(t++);
    } else {
      stack.pop_back();
    }
  }

  vector<i64> pows(N + 1);
  pows[0] = 1;
  for (int i = 0; i < N; i++) {
    pows[i + 1] = pows[i] * BASE % MOD;
  }

  auto dfs = [&](auto self, int a, int d) -> tuple<mint, i64, int> {
    map<i64, tuple<int, int, mint>> hashes;
    for (auto b : adj[a]) {
      auto [ways, hash, size] = self(self, b, d + 1);
      auto &[size2, count, ways2] = hashes[hash];
      size2 = size;
      ways2 = ways;
      count++;
    }

    mint ways2 = 1;
    int count2 = 0;
    i64 hash2 = d;
    int size2 = 1;
    for (auto [hash, data] : hashes) {
      auto [size, count, ways] = data;
      for (int i = 0; i < count; i++) {
        ways2 *= ways;
        hash2 = (hash2 * pows[size] + hash) % MOD;
        size2 += size;
      }
      ways2 /= fact<mint>(count);
      count2 += count;
    }
    ways2 *= fact<mint>(count2);

    return {ways2, hash2, size2};
  };
  cout << get<0>(dfs(dfs, 0, 1)).val();
}
