#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string S;
  cin >> S;

  string T = S;
  sort(T.begin(), T.end());
  T.erase(unique(T.begin(), T.end()), T.end());
  cout << S.size() - T.size() << '\n';
}