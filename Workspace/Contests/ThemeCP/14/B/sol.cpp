#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  i64 X, Y;
  cin >> X >> Y;

  auto to_bin = [&](i64 n) -> string {
    string rv = "";
    for (; n; n >>= 1) {
      rv += to_string(n & 1);
    }
    reverse(rv.begin(), rv.end());
    return rv;
  };

  string x = to_bin(X) + '1', x_ = to_bin(X), y = to_bin(Y);
  while (x_.back() == '0') {
    x_.pop_back();
  }
  string rx = x, rx_ = x_;
  reverse(rx.begin(), rx.end());
  reverse(rx_.begin(), rx_.end());

  auto check = [&](string x, string y) -> bool {
    for (int i = 0; i + x.size() <= y.size(); i++) {
      if (string(i, '1') + x + string(y.size() - (i + x.size()), '1') == y) {
        return true;
      }
    }
    return false;
  };
  cout << (X == Y or check(x, y) or check(x_, y) or check(rx, y) or
                   check(rx_, y)
               ? "YES"
               : "NO");
}
