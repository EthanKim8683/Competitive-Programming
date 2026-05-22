#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N - 1);
  for (auto &e : A) cin >> e;

  vector<int> counts(20, 0);
  int v = 0;
  for (auto e : A) {
    v ^= e;
    for (int i = 0; i < 20; i++) {
      counts[i] += v >> i & 1;
    }
  }

  int v0 = 0;
  for (int i = 0; i < 20; i++) {
    if (counts[i] > N - counts[i]) {
      v0 |= 1 << i;
    }
  }

  v = v0;
  cout << v;
  for (auto e : A) {
    v ^= e;
    cout << ' ' << v;
  }
}
