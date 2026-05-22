#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> B(N / 2);
    for (auto &e : B) cin >> e, e--;

    vector<int> ps(N + 1, 1);
    ps[0] = 0;
    for (auto e : B) {
      ps[e + 1] = 0;
    }
    for (int i = 0; i < N; i++) {
      ps[i + 1] += ps[i];
    }

    vector<int> slack(N / 2);
    for (int i = 0; i < N / 2; i++) {
      slack[i] = ps[B[i]];
    }
  }
}
