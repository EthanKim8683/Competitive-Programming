#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int S, N;
  cin >> S >> N;

  vector<pair<int, bool>> people(N);
  for (auto &[d, y] : people) {
    char t;
    cin >> d >> t;
    y = t == 'y';
  }
  sort(people.begin(), people.end());

  map<int, int> taken;
  int l = INF, r = INF;
  for (int i = N - 1; i >= 0; i--) {
    auto [d, y] = people[i];
    if (!y) continue;
    if (l <= d and d <= r) {
      l--;
    } else {
      l = d;
      r = d;
    }
    if (l < 1) {
      cout << "No";
      exit(0);
    }
    taken[l]++;
  }

  int j = 1;
  for (auto [d, y] : people) {
    if (y) continue;
    while (taken[j] == S) {
      j++;
    }
    if (j > d) {
      cout << "No";
      exit(0);
    }
    taken[j]++;
  }
  cout << "Yes";
}