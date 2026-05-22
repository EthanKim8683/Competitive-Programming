#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    auto query = [&](int l, int r) -> int {
      cout << "? " << l + 1 << ' ' << r << endl;
      int rv;
      cin >> rv;
      if (rv == -1) exit(0);
      return rv;
    };

    auto answer = [&](int k) -> void { cout << "! " << k << endl; };
  }
}
