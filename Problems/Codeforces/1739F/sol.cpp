#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  // Not hard, just very implementation heavy

  vector<pair<int, string>> words;
  for (int i = 0; i < N; i++) {
    int c;
    string s;
    cin >> c >> s;

    deque<char> dq = {s[0]};
    int j = 0;
    bool ok = true;
    for (int i = 1; i < s.size(); i++) {
      if (j + 1 < dq.size() and dq[j + 1] == s[i]) {
        j++;
      } else if (j - 1 >= 0 and dq[j - 1] == s[i]) {
        j--;
      } else if (j + 1 == dq.size()) {
        dq.push_back(s[i]);
        j++;
      } else if (j == 0) {
        dq.push_front(s[i]);
      } else {
        ok = false;
        break;
      }
    }

    int mask = 0;
    for (auto e : dq) {
      mask |= 1 << (e - 'a');
    }
    ok = ok and __builtin_popcount(mask) == dq.size();

    if (ok) {
      string t(dq.begin(), dq.end());
      words.push_back({c, t});
      reverse(t.begin(), t.end());
      words.push_back({c, t});
    }
  }

  map<pair<int, string>, int> by_super;
  for (auto [c, s] : words) {
    by_super[make_pair(s.size(), s)] += c;
  }
  for (auto &[k, c] : by_super) {
    auto [l, s] = k;
    for (int i = 1; i < l; i++) {
      for (int j = 0; j + i <= l; j++) {
        string t = s.substr(j, i);
        auto k2 = make_pair(t.size(), t);
        if (by_super.contains(k2)) {
          c += by_super[k2];
          by_super.erase(k2);
        }
      }
    }
  }

  vector<tuple<string, int, int>> words2;
  for (auto [k, c] : by_super) {
    auto s = k.second;
    int mask = 0;
    for (auto e : s) {
      mask |= 1 << (e - 'a');
    }
    words2.push_back({s, mask, c});
  }
  int K = words2.size();

  vector<vector<int>> adj(K);
  for (int i = 0; i < K; i++) {
    for (int j = 0; j < K; j++) {
      if (i == j) continue;
      string s = get<0>(words2[i]), t = get<0>(words2[j]);

      // TODO: check if adj
    }
  }

  auto chmax = [&](auto &a, auto b) -> void { a = max(a, b); };
  vector dp(1 << 12, vector<tuple<int, int, int>>(K, {-INF, -1, -1}));
  for (int i = 0; i < K; i++) {
    auto [s, mask, c] = words2[i];
    dp[mask][i] = {c, -1, -1};
  }
  for (int i = 0; i < (1 << 12); i++) {
    for (int j = 0; j < K; j++) {
      for (auto k : adj[j]) {
        int mask1 = get<1>(words2[j]), mask2 = get<1>(words2[k]),
            c = get<2>(words2[k]);
        if (i & ~mask1 & mask2) continue;
        chmax(dp[i | mask2][k], make_tuple(get<0>(dp[i][j]) + c, i, j));
      }
    }
  }

  tuple<int, int, int> best = {-INF, -1, -1};
  for (int i = 0; i < (1 << 12); i++) {
    for (int j = 0; j < K; j++) {
      best = max(best, make_tuple(get<0>(dp[i][j]), i, j));
    }
  }

  // TODO: construct
}
