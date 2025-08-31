#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

// My first DMOJ contest! Hope I do alright!
int main() {
  cin.tie(0)->sync_with_stdio(0);

  i64 N;
  cin >> N;

  i64 a;
  cin >> a;

  i64 b;
  cin >> b;

  cout << (a <= b and a % 2 == b % 2 ? "YES" : "NO");
}
