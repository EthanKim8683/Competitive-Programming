#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  string S;
  cin >> S;

  bool pp = false, ans = true;
  int csp = 0, score = 0;
  for (auto e : S) {
    if (pp) {
      ans = ans and e != 'P';
    }
    if (csp == K) {
      ans = ans and e == 'F';
    }
    pp = e == 'P';
    if (e == 'F') {
      csp = 0;
    } else {
      csp++;
    }
    score += (e != 'F') + (e == 'P');
  }
  cout << (ans ? "YES" : "NO");
  if (ans) {
    cout << '\n' << score;
  }
}
