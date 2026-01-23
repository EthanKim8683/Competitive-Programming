#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"
#include "atcoder/string.hpp"

using namespace std;
using namespace atcoder;

using f64 = long double;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<pair<vector<string>, string>> texts(N);
  int M = 0;
  for (auto &[t, l] : texts) {
    int m;
    cin >> m;
    M = max(M, m);

    t.resize(m);
    for (auto &e : t) cin >> e;

    cin >> l;
  }

  vector<string> cc;
  for (auto [t, l] : texts) {
    cc.insert(cc.end(), t.begin(), t.end());
  }
  sort(cc.begin(), cc.end());
  auto compress = [&](string token) -> int {
    return lower_bound(cc.begin(), cc.end(), token) - cc.begin();
  };

  vector<int> s;
  vector<bool> is_llm;
  for (int i = 0; i < N; i++) {
    auto [t, l] = texts[i];
    for (int j = t.size() - 1; j >= 0; j--) {
      s.push_back(compress(t[j]));
      is_llm.push_back(l[j] == 'L');
    }
    s.push_back(-(i + 1));
    is_llm.push_back(false);
  }
  auto sa = suffix_array(s);

  vector<map<int, int>> counts(sa.size());
  for (int i = 0; i < sa.size(); i++) {
    int j = sa[i];
    if (j - 1 >= 0 and is_llm[j - 1]) {
      counts[i][s[j - 1]]++;
    }
  }

  vector<vector<int>> merges(M + 1);
  auto lcp = lcp_array(s, sa);
  for (int i = 0; i < lcp.size(); i++) {
    int k = lcp[i];
    if (s[sa[i] + k] < 0 and s[sa[i + 1] + k] < 0) {
      k = M;
    }
    merges[k].push_back(i);
  }

  vector<int> totals(sa.size(), 0);
  for (int i = 0; i < sa.size(); i++) {
    for (auto [token, count] : counts[i]) {
      totals[i] += count;
    }
  }

  auto f = [&](int x) -> double {
    if (x == 0) return 0;
    return x * log2l(x);
  };

  vector<f64> ans(M + 1, 0);
  dsu d(sa.size());
  f64 sum = 0;
  for (int i = M; i >= 0; i--) {
    for (auto j : merges[i]) {
      int a = d.leader(j), b = d.leader(j + 1);
      if (b == d.merge(a, b)) {
        swap(a, b);
      }

      if (counts[b].size() > counts[a].size()) {
        swap(totals[a], totals[b]);
        counts[a].swap(counts[b]);
      }

      sum -= f(totals[a]);
      sum -= f(totals[b]);
      totals[a] += totals[b];
      sum += f(totals[a]);
      totals[b] = 0;

      for (auto [token, count] : counts[b]) {
        sum += f(count);
        sum += f(counts[a][token]);
        counts[a][token] += count;
        sum -= f(counts[a][token]);
      }
      counts[b].clear();
    }
    ans[i] = sum;
  }

  cout << setprecision(12) << fixed;
  for (int i = 0; i < M; i++) {
    cout << ans[i] << '\n';
  }
}
