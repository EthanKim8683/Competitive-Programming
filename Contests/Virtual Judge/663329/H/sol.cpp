#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<int> N(8);
  for (auto &e : N) {
    cin >> e;
  }

  cout << (find(N.begin(), N.end(), 9) != N.end() ? "F" : "S");
}