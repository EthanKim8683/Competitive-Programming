#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // map<tuple<int, int, int>, array<char, 10>> ok;
  // for (int i = 0; i < (1 << 10); i++) {
  //   string s = "";
  //   for (int j = 0; j < 10; j++) {
  //     s += to_string(i >> j & 1);
  //   }
  //   int counts[1 << 2] = {0};
  //   for (int j = 0; j + 1 < 10; j++) {
  //     counts[(s[j] - '0') << 1 | (s[j + 1] - '0')]++;
  //   }
  //   tuple<int, int, int> key = {counts[0], counts[1], counts[3]};
  //   if (!ok.contains(key)) {
  //     ok[key] = {};
  //     for (int j = 0; j < 10; j++) {
  //       ok[key][j] = s[j];
  //     }
  //   }
  //   for (int j = 0; j < 10; j++) {
  //     if (ok[key][j] != s[j]) {
  //       ok[key][j] = 0;
  //     }
  //   }
  // }
  // for (auto [key, inv] : ok) {
  //   auto [x, y, z] = key;
  //   cerr << x << ", " << y << ", " << z << ": ";
  //   for (int i = 0; i < 10; i++) {
  //     if (inv[i]) {
  //       cerr << i << ' ';
  //     }
  //   }
  //   cerr << '\n';
  // }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    auto query = [&](string t) -> int {
      cout << "1 " << t << endl;
      int rv;
      cin >> rv;
      if (rv == -1) exit(0);
      return rv;
    };
    auto answer = [&](int i, char c) -> void {
      cout << "0 " << i + 1 << ' ' << c << endl;
      int t;
      cin >> t;
      if (t == -1) exit(0);
    };

    int cnt01 = query("01"), cnt10 = query("10");
    if (cnt01 + 1 == cnt10) {
      answer(0, '1');
    } else if (cnt10 + 1 == cnt01) {
      answer(0, '0');
    } else {
      if (N == 2) {
        if (query("00") == 1) {
          answer(0, '0');
        } else {
          answer(0, '1');
        }
      } else {
        if (query("010") == cnt10) {
          answer(0, '0');
        } else {
          answer(0, '1');
        }
      }
    }
  }
}
