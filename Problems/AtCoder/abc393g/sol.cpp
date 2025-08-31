#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using f64 = long double;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  i64 P, Q;
  cin >> P >> Q;

  vector A(N, vector<int>(N));
  for (auto &r : A) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  // this feels Lagrangian? There's two functions f(x), g(x) and we want to
  // minimize f(x) under the constraint of g(x).
  //
  // I'll get back to this when I have internet.
}
