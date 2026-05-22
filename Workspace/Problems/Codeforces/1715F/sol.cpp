#include <bits/stdc++.h>

using namespace std;

using f64 = long double;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  cout << setprecision(15) << fixed;

  auto query = [&](vector<pair<f64, f64>> P) -> f64 {
    cout << "? " << P.size() << '\n';
    for (auto [x, y] : P) {
      cout << x << ' ' << y << '\n';
    }
    cout.flush();
    f64 rv;
    cin >> rv;
    return rv;
  };

  auto answer = [&](f64 x, f64 y) -> void {
    cout << "! " << x << ' ' << y << endl;
    exit(0);
  };

  auto area = [&](f64 D, f64 x) -> f64 {
    f64 m = (f64) 1 / (D - 1), w1 = max(1 - x, (f64) 0), w2 = 1 - w1,
        h2 = max(x - 1, (f64) 0) * m;
    return w1 + w2 * (1 - h2) - w2 * w2 * m / 2;
  };

  f64 x, y;
  {
    vector<pair<f64, f64>> P;
    P.push_back({0, 0});
    for (int i = 0; i < M; i++) {
      P.push_back({N, i});
      P.push_back({1, i + 1});
    }
    P.push_back({0, M});
    reverse(P.begin(), P.end());
    f64 a = query(P), l = 0, r = N - 1;
    for (int i = 0; i < 64; i++) {
      f64 m = (l + r) / 2;
      area(N, m) <= a ? r = m : l = m;
    }
    x = l;
  }
  {
    vector<pair<f64, f64>> P;
    P.push_back({0, 0});
    for (int i = 0; i < N; i++) {
      P.push_back({i, M});
      P.push_back({i + 1, 1});
    }
    P.push_back({N, 0});
    f64 a = query(P), l = 0, r = M - 1;
    for (int i = 0; i < 64; i++) {
      f64 m = (l + r) / 2;
      area(M, m) <= a ? r = m : l = m;
    }
    y = l;
  }
  answer(x, y);
}
