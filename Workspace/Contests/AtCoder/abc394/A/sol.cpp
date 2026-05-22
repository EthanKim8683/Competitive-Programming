#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string S;
  cin >> S;

  cout << string(count(S.begin(), S.end(), '2'), '2');
}
