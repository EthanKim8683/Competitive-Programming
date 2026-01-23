#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;
using mint = modint1000000007;

const int MAXQ = 2e5;
const int MAXK = 60;

static char buf[450 << 20];
void *operator new(size_t n) {
  static size_t i = sizeof buf;
  assert(n < i);
  return (void *) &buf[i -= n];
}
void operator delete(void *) {}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<array<int, 2>> trie;
  vector<int> size;
  vector<mint> sum;

  int MAXQK = MAXQ * MAXK;
  trie.reserve(MAXQK);
  size.reserve(MAXQK);
  sum.reserve(MAXQK);

  int T;
  cin >> T;

  while (T--) {
    int N, K, Q;
    cin >> N >> K >> Q;

    vector<tuple<i64, int, int, int>> plans(Q);
    for (auto &[d, x, y, c] : plans) {
      cin >> d >> x >> y >> c;
      x--, y--;
    }

    trie.clear();
    size.clear();
    sum.clear();

    trie.push_back({-1, -1});
    size.push_back(0);
    sum.push_back(0);
    auto does_contribute = [&](int a) -> bool {
      return a != -1 and size[a] > 0;
    };
    auto contribute = [&](int a, int d) -> void {
      int b = trie[a][0], c = trie[a][1];
      if (does_contribute(b) and does_contribute(c)) {
        sum[a] += d * (sum[b] + sum[c]) / 2;
      } else if (does_contribute(b)) {
        sum[a] += d * sum[b];
      } else if (does_contribute(c)) {
        sum[a] += d * sum[c];
      }
    };
    auto insert = [&](i64 x, int c) -> void {
      auto dfs = [&](auto self, int a, int i) -> void {
        size[a]++;
        if (i == -1) {
          sum[a] = c;
          return;
        }
        contribute(a, -1);
        int &b = trie[a][x >> i & 1];
        if (b == -1) {
          b = trie.size();
          trie.push_back({-1, -1});
          size.push_back(0);
          sum.push_back(0);
        }
        self(self, b, i - 1);
        contribute(a, 1);
      };
      dfs(dfs, 0, K - 1);
    };
    auto erase = [&](i64 x) -> void {
      auto dfs = [&](auto self, int a, int i) -> void {
        size[a]--;
        if (i == -1) return;
        contribute(a, -1);
        self(self, trie[a][x >> i & 1], i - 1);
        contribute(a, 1);
      };
      dfs(dfs, 0, K - 1);
    };
    vector<vector<pair<i64, int>>> insertions(N);
    vector<vector<i64>> erasures(N);
    for (auto [d, x, y, c] : plans) {
      insertions[x].emplace_back(d, c);
      erasures[y].push_back(d);
    }
    mint ans = 0;
    for (int i = 0; i < N; i++) {
      for (auto [d, c] : insertions[i]) {
        insert(d, c);
      }
      ans += mint(2).pow(K) * sum[0];
      for (auto d : erasures[i]) {
        erase(d);
      }
    }
    cout << ans.val() << '\n';
  }
}
