#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  int A, B;
  cin >> A >> B;

  vector<int> D(N - 1);
  for (auto &e : D) cin >> e;
  i64 sum = accumulate(D.begin(), D.end(), 0ll);

  if (A + B > sum or (A + B) % 2 != sum % 2) {
    cout << "NO";
    exit(0);
  }

  bool flip = A < B;
  if (flip) {
    swap(A, B);
  }

  auto key = [&](i64 pos) -> int {
    i64 neg = sum - pos, y = pos - neg;
    if (A + B < y) return 1;
    if (B - A > y) return -1;
    return 0;
  };
  i64 L, R;
  {
    i64 l = 0, r = sum;
    while (l < r) {
      i64 m = l + (r - l) / 2;
      key(m) > -1 ? r = m : l = m + 1;
    }
    L = l;
  }
  {
    i64 l = 0, r = sum;
    while (l < r) {
      i64 m = l + (r - l + 1) / 2;
      key(m) < 1 ? l = m : r = m - 1;
    }
    R = l;
  }
  vector<pair<i64, int>> left;
  for (int i = 0; i < (1 << ((N - 1) / 2)); i++) {
    i64 pos = 0;
    for (int j = i; j != 0; j -= j & -j) {
      int k = __lg(j & -j);
      pos += D[k];
    }
    left.push_back({pos, i});
  }
  sort(left.begin(), left.end());
  i64 mask = -1;
  for (int i = 0; i < (1 << ((N - 1) - (N - 1) / 2)); i++) {
    i64 pos = 0;
    for (int j = i; j != 0; j -= j & -j) {
      int k = __lg(j & -j);
      pos += D[k + (N - 1) / 2];
    }
    // L <= pos_r + pos_l <= R
    // L - pos_r <= pos_l <= R - pos_r
    auto it = lower_bound(left.begin(), left.end(), make_pair(L - pos, -1));
    if (it != left.end()) {
      i64 pos2 = it->first;
      if (L <= pos + pos2 and pos + pos2 <= R) {
        mask = it->second | (i64) i << ((N - 1) / 2);
        break;
      }
    }
  }
  if (mask == -1) {
    cout << "NO";
    exit(0);
  }

  i64 x = 0, y = 0;
  for (int i = 0; i < N - 1; i++) {
    y += (mask >> i & 1 ? 1 : -1) * D[i];
  }
  // \Delta pos + \Delta neg = A - x
  // \Delta neg - \Delta pos = B - y
  i64 dneg = (A - x + B - y) / 2, dpos = A - x - dneg;

  vector<pair<i64, i64>> ans;
  x = y = 0;
  ans.push_back({x, y});
  for (int i = 0; i < N - 1; i++) {
    int dx, dy;
    if (mask >> i & 1) {
      dx = min((i64) D[i], dpos);
      dy = D[i] - dx;
      dpos -= dx;
    } else {
      dx = min((i64) D[i], dneg);
      dy = -(D[i] - dx);
      dneg -= dx;
    }
    x += dx;
    y += dy;
    ans.push_back({x, y});
  }

  cout << "YES\n";
  for (auto [x, y] : ans) {
    if (flip) {
      swap(x, y);
    }
    cout << x << ' ' << y << '\n';
  }
}
