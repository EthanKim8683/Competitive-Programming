#include <bits/stdc++.h>

using namespace std;

const int MAXA = 90;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int H, W, N;
  cin >> H >> W >> N;

  vector A(H, vector<int>(W));
  for (auto &r : A) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  vector<int> B(N);
  for (auto &e : B) {
    cin >> e;
  }

  vector<bool> called(MAXA + 1, false);
  for (auto e : B) {
    called[e] = true;
  }

  int ans = 0;
  for (auto r : A) {
    int count = 0;
    for (auto e : r) {
      if (!called[e]) continue;
      count += 1;
    }
    ans = max(ans, count);
  }
  cout << ans;
}
