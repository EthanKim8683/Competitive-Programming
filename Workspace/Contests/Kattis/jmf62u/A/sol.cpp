#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int A, B, C;
  cin >> A >> B >> C;

  auto sign = [&](int x) -> int { return (x > 0) - (x < 0); };

  int d1 = B - A, d2 = C - B;
  if (d1 == d2) {
    cout << "cruised";
  } else if (sign(d1) != sign(d2)) {
    cout << "turned";
  } else if (abs(d1) < abs(d2)) {
    cout << "accelerated";
  } else {
    cout << "braked";
  }
}