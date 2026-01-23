#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  i64 N;
  cin >> N;

  auto key = [&](string s) -> pair<int, string> { return {s.size(), s}; };

  string ans = "0";
  for (i64 b = 1; b <= N; b *= 10) {
    auto s = to_string(N - b) + to_string(b);
    if (key(s) > key(ans)) {
      ans = s;
    }
  }
  cout << ans << '\n';
}
