#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int X, Y, Z;
  cin >> X >> Y >> Z;

  vector<int> scores(6);
  for (auto &e : scores) cin >> e;

  cout << (accumulate(scores.begin(), scores.end(), 0) >= X and
                   count(scores.begin(), scores.end(), 100) >= Y and
                   6 - count(scores.begin(), scores.end(), 0) >= Z
               ? "MASTER"
               : "REJECTED AGAIN");
}
