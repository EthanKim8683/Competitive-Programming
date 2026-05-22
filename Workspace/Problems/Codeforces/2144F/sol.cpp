#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // at most 2 groups?
  // ((((()))))
  // ()()()()()
  // only nontrivial common substring is (), which has yields no solution
  // check if there exists a regular bracket sequence such that none of the
  // provided sequences are a substring of it
  // brute force?

  int N, K;
  cin >> N >> K;

  vector<string> S(N);
  for (auto &e : S) cin >> e;

  if (find(S.begin(), S.end(), "()") != S.end()) {
    cout << "-1\n";
    exit(0);
  }

  vector<pair<string, vector<int>>> groups;

  string s = "";
  int h = 0;
  auto dfs = [&](auto self) -> bool {
    for (auto e : S) {
      if (e.size() > s.size()) continue;
      if (s.substr(s.size() - e.size()) == e) return false;
    }

    if (s.size() == K) {
      vector<int> all(N);
      iota(all.begin(), all.end(), 0);
      groups.emplace_back(s, all);
      return true;
    }

    if (h + 1 <= K - (s.size() + 1)) {
      s.push_back('(');
      h++;
      if (self(self)) return true;
      s.pop_back();
      h--;
    }

    if (h - 1 >= 0) {
      s.push_back(')');
      h--;
      if (self(self)) return true;
      s.pop_back();
      h++;
    }

    return false;
  };
  if (!dfs(dfs)) {
    string s1 = "";
    s1 += string(K / 2, '(');
    s1 += string(K / 2, ')');
    groups.emplace_back(s1, vector<int>());

    string s2 = "";
    for (int i = 0; i < K / 2; i++) {
      s2 += "()";
    }
    groups.emplace_back(s2, vector<int>());

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < 2; j++) {
        if (groups[j].first.find(S[i]) == string::npos) {
          groups[j].second.push_back(i);
          break;
        }
      }
    }
  }

  cout << groups.size() << '\n';
  for (auto [rbs, indices] : groups) {
    cout << rbs << '\n';
    cout << indices.size() << '\n';
    for (auto e : indices) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
