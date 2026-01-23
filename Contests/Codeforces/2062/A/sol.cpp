#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    string S;
    cin >> S;

    cout << count(S.begin(), S.end(), '1') << '\n';
  }
}
/*

*/
