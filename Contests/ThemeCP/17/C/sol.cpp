#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<vector<int>> divs(3e5 + 1);
  for (int i = 1; i <= 3e5; i++) {
    for (int j = i; j <= 3e5; j += i) {
      divs[j].push_back(i);
    }
  }

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;
  sort(A.begin(), A.end());

  // PIE

  vector<vector<int>> lbs(3e5 + 1), ubs(3e5 + 1);
  for (int i = 0; i < N; i++) {
    for (auto d : divs[A[i]]) {
      lbs[d].push_back(i + 1);
      ubs[d].push_back(i);
    }
  }
  vector<i64> pie(3e5 + 1, 0);
  for (int i = 1; i <= 3e5; i++) {
    vector<i64> ps(ubs[i].size() + 1);
    ps[0] = 0;
    for (int j = 0; j < ubs[i].size(); j++) {
      ps[j + 1] = ps[j] + ubs[i][j];
    }

    for (auto lb : lbs[i]) {
      int j = lower_bound(ubs[i].begin(), ubs[i].end(), lb) - ubs[i].begin();
      pie[i] += ps[ubs[i].size()] - ps[j] - (i64) (ubs[i].size() - j) * lb;
    }
  }

  for (int i = 3e5; i >= 1; i--) {
    for (auto j : divs[i]) {
      if (j < i) {
        pie[j] -= pie[i];
      }
    }
  }
  cout << pie[1];
}
