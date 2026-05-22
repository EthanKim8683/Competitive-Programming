#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<string> S(N);
  for (auto &r : S) cin >> r;

  sort(S.begin(), S.end(), [&](auto a, auto b) { return a.size() < b.size(); });
  for (auto e : S) {
    cout << e;
  }
}
