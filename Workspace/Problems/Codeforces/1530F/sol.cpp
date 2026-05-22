#include <bits/stdc++.h>

using namespace std;

using u16 = unsigned short;

const u16 MOD = 31607;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector A(N, vector<int>(N));
  for (auto &r : A) {
    for (auto &e : r) {
      cin >> e;
    }
  }
}
