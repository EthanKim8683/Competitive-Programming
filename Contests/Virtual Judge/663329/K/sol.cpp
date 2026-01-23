#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> counts(13 + 1, 0);

  int j = 0;
  for (int i = 0; i < 2; i++) {
    int v;
    cin >> v;
    counts[v]++;
    j += min(v, 10);
  }

  int m = 0;
  for (int i = 0; i < 2; i++) {
    int v;
    cin >> v;
    counts[v]++;
    m += min(v, 10);
  }

  for (int i = 0; i < N; i++) {
    int v;
    cin >> v;
    counts[v]++;
    j += min(v, 10);
    m += min(v, 10);
  }

  for (int i = 1; i <= 13; i++) {
    if (counts[i] >= 4) continue;
    int v = min(i, 10);

    bool ok = false;
    ok = ok or (j + v > 23 and m + v <= 23);
    ok = ok or m + v == 23;
    if (ok) {
      cout << i;
      exit(0);
    }
  }
  cout << -1;
}