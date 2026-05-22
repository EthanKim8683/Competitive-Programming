#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<pair<int, int>> people(N);
  for (auto &[S, T] : people) {
    cin >> S >> T;
  }
}