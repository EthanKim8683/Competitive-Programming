#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string S;
  cin >> S;

  for (int i = 0; i + 1 < S.size();) {
    if (S.substr(i, 2) == "WA") {
      S[i] = 'A';
      S[i + 1] = 'C';
      i = max(i - 1, 0);
    } else {
      i++;
    }
  }
  cout << S;
}
