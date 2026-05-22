#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<array<int, 5>> lines(N);
  for (auto &r : lines) {
    for (auto &e : r) {
      cin >> e;
    }
  }
}
