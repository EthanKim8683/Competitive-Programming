#include <bits/stdc++.h>

#include "atcoder/string.hpp"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<string> S(N);
  for (auto &e : S) cin >> e;

  vector<tuple<int, int, int, string>> queries(M);
  for (auto &[t, i, x, q] : queries) {
    cin >> t;
    if (t == 1) {
      cin >> i >> x;
      i--;
    } else {
      cin >> q;
    }
  }

  string T = "";
  for (auto e : S) {
    T += e + '$';
    T += e + '~';
  }
  for (auto [t, i, x, q] : queries) {
    if (t == 2) {
      T += q + '%';
    }
  }

  auto sa = suffix_array(T);
  vector<int> isa(sa.size());
  for (int i = 0; i < sa.size(); i++) {
    isa[sa[i]] = i;
  }

  vector<pair<int, int>> ranges(N);
  int s = 0;
  for (int i = 0; i < N; i++) {
    ranges[i].first = isa[s];
    s += S[i].size() + 1;
    ranges[i].second = isa[s];
    s += S[i].size() + 1;
  }
  vector<vector<int>> indices(M);
  for (int i = 0; i < M; i++) {
    auto [t, i2, x, q] = queries[i];
    if (t != 2) continue;
    for (int j = 0; j < q.size(); j++) {
      indices[i].push_back(isa[s]);
      s++;
    }
    s++;
  }
}
