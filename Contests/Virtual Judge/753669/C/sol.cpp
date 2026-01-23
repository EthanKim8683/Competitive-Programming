#include <bits/stdc++.h>

using namespace std;

using f64 = long double;

const f64 PI = 2 * acosl(0);

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int Theta, N;
  cin >> Theta >> N;
  f64 d = Theta * PI / 180;
  cerr << d << '\n';

  vector<pair<f64, f64>> ranges;
  for (int i = 0; i < N; i++) {
    int X, H;
    cin >> X >> H;

    ranges.push_back({X, X + H / tanl(d)});
  }

  vector<f64> compressed;
  for (auto [l, r] : ranges) {
    compressed.push_back(l);
    compressed.push_back(r);
  }
  sort(compressed.begin(), compressed.end());
  compressed.erase(unique(compressed.begin(), compressed.end()),
                   compressed.end());
  vector<pair<int, int>> ranges_;
  for (auto [l, r] : ranges) {
    int l_ = lower_bound(compressed.begin(), compressed.end(), l) -
             compressed.begin();
    int r_ = lower_bound(compressed.begin(), compressed.end(), r) -
             compressed.begin();
    ranges_.push_back({l_, r_});
  }

  vector<int> ps(compressed.size(), 0);
  for (auto [l, r] : ranges_) {
    ps[l]++;
    ps[r]--;
  }
  for (int i = 0; i + 1 < compressed.size(); i++) {
    ps[i + 1] += ps[i];
  }
  f64 ans = 0;
  for (int i = 0; i + 1 < compressed.size(); i++) {
    ans += (ps[i] > 0) * (compressed[i + 1] - compressed[i]);
  }
  cout << setprecision(14) << fixed << ans;
}