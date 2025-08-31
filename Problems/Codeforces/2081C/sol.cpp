#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<string> mat(N);
    for (auto &r : mat) {
      cin >> r;
      for (auto &e : r) {
        e -= '0';
      }
    }

    // if there was only one bit, we greedily match rows and columns with
    // non-zero sum, then pair off the remaining rows or columns
    //
    //
  }
}
