#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    string A;
    cin >> A;

    string B;
    cin >> B;

    set<char> A_;
    for (auto e : A) {
      A_.insert(e);
    }
    bool ok = true;
    for (auto e : B) {
      ok = ok and A_.find(e) != A_.end();
    }
    cout << (ok ? "YES" : "NO") << '\n';
  }
}