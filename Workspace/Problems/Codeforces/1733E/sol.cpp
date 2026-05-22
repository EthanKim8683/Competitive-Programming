#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // int D = 20;

  // vector down(D, vector<bool>(D, false)), slimes(D, vector<bool>(D, false));
  // slimes[0][0] = true;
  // for (int i = 0; i < 40; i++) {
  //   for (int j = 0; j < D; j++) {
  //     for (int k = 0; k < D; k++) {
  //       cerr << (down[j][k] ? '.' : '#');
  //     }
  //     cerr << '\n';
  //   }
  //   cerr << '\n';

  //   for (int j = D - 1; j >= 0; j--) {
  //     for (int k = D - 1; k >= 0; k--) {
  //       if (slimes[j][k]) {
  //         if (down[j][k]) {
  //           if (j + 1 < D) {
  //             slimes[j + 1][k] = true;
  //           }
  //           slimes[j][k] = false;
  //         } else {
  //           if (k + 1 < D) {
  //             slimes[j][k + 1] = true;
  //           }
  //           slimes[j][k] = false;
  //         }
  //         down[j][k] = !down[j][k];
  //       }
  //     }
  //   }
  //   slimes[0][0] = true;
  // }

  // vector<unsigned> add;
  // for (int i = 0; i < (1 << 5) + 1; i++) {
  //   add.push_back(1);
  // }
  // for (int i = 0; i < 5; i++) {
  //   unsigned v = -1;
  //   for (int j = 0; j < add.size(); j++) {
  //     int v0 = v;
  //     v += add[j];
  //     add[j] = (v0 + add[j]) & ~v0;
  //     cerr << (v & ((1 << 5) - 1)) << ' ';
  //   }
  //   cerr << '\n';
  // }

  // int D = 20;
  // vector down(2 * (D - 1), vector<bool>(2 * (D - 1), false));
  // for (int i = 0; i < 200; i++) {
  //   int x = 0, y = 0;
  //   string s = "";
  //   for (int j = 0; j < 2 * (D - 1); j++) {
  //     if (down[y][x]) {
  //       down[y][x] = false;
  //       s += '#';
  //       y++;
  //     } else {
  //       down[y][x] = true;
  //       s += '.';
  //       x++;
  //     }
  //   }
  //   cerr << s << '\n';
  // }

  // int D = 20;
  // vector down(D, vector<int>(D, 0));
  // for (int i = 0; i < 100; i++) {
  //   int x = 0, y = 0;
  //   while (true) {
  //     if (x >= D or y >= D) break;
  //     if (down[y][x]++ % 2 == 1) {
  //       y++;
  //     } else {
  //       x++;
  //     }
  //   }

  //   for (int j = 0; j < D; j++) {
  //     for (int k = 0; k < D; k++) {
  //       cerr << down[j][k] << ' ';
  //     }
  //     cerr << '\n';
  //   }
  //   cerr << '\n';
  // }
}
