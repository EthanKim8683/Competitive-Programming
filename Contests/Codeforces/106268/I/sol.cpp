#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string S;
    cin >> S;

    if (S == ".") {
      cout << "alice\n";
      continue;
    }

    vector<pair<int, int>> ranges;
    for (int i = 0; i < N; i++) {
      if (ranges.empty() or S[i] != S[ranges.back().first]) {
        if (!ranges.empty()) {
          ranges.back().second = i;
        }
        ranges.emplace_back(i, N);
      }
    }

    map<char, int> counts;
    for (auto [l, r] : ranges) {
      if (S[l] != '.') continue;
      if (l == 0 and r == N) {
      } else if (l == 0) {
        counts[S[r]]++;
      } else if (r == N) {
        counts[S[l - 1]]++;
      } else {
        if (S[l - 1] == S[r]) {
          counts[S[l - 1]]++;
        }
      }
    }
    cout << (counts['b'] >= counts['a'] + 1 ? "alice" : "bob") << '\n';
  }
}
