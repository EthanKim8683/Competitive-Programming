#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector A(N, vector<int>(M));
    for (auto &r : A) {
      for (auto &e : r) {
        cin >> e, e--;
      }
    }

    vector B(N, vector<int>(M));
    for (auto &r : B) {
      for (auto &e : r) {
        cin >> e, e--;
      }
    }

    vector<int> index(2 * N * M, -1);
    int t = 0;
    for (auto r : A) {
      for (auto e : r) {
        index[e] = t++;
      }
    }

    int ans = 0;
    t = 0;
    for (auto r : B) {
      for (int i = 0; i < M; i++) {
        if (index[r[i]] != t) {
          if (i <= ans) {
            ans++;
          } else {
            t = -2;
            ans = i + 1;
          }
        } else {
          t++;
        }
      }
    }
    cout << ans << '\n';
  }
}
