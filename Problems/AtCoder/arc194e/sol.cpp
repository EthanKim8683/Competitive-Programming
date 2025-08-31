#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, X, Y;
  cin >> N >> X >> Y;

  string S;
  cin >> S;

  string T;
  cin >> T;

  // proof by AC?

  auto get_occs = [&](string S) -> array<vector<int>, 2> {
    array<vector<int>, 2> rv;
    for (int i = 0; i < S.size(); i++) {
      rv[S[i] - '0'].push_back(i);
    }
    return rv;
  };
  auto occs1 = get_occs(S), occs2 = get_occs(T);
  bool ok = true;
  for (int i = 0; i < 2; i++) {
    if (occs1[i].size() != occs2[i].size()) {
      ok = false;
      break;
    }
    int Z = (int[]) {Y, X}[i];
    for (int j = 0; j < occs1[i].size(); j++) {
      ok = ok and occs1[i][j] % Z == occs2[i][j] % Z;
    }
  }
  cout << (ok ? "Yes" : "No");
}
