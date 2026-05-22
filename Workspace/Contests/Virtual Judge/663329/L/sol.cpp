#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<tuple<int, int, string>> teams;
  for (int i = 0; i < N; i++) {
    string C;
    int P;
    vector<int> E(6);
    cin >> C >> P;
    for (auto &e : E) cin >> e;

    sort(E.begin(), E.end());
    teams.push_back(
        {-(P * 10 + accumulate(E.begin() + 1, E.end() - 1, 0)), i, C});
  }
  sort(teams.begin(), teams.end());

  vector<int> scores;
  for (auto [score, i, team] : teams) {
    scores.push_back(score);
  }

  for (auto [score, i, team] : teams) {
    if (lower_bound(scores.begin(), scores.end(), score) - scores.begin() <=
        2) {
      cout << team << ' ' << -score << '\n';
    }
  }
}