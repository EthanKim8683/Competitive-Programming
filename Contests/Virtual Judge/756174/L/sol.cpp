#include <bits/stdc++.h>
using namespace std;

#define int long long
#define float long double
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef pair<float, float> vec;

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vi ans(N, -1);
  auto read = [&](auto self) -> int {
    int a;
    cin >> a;
    a--;
    while (true) {
      char c;
      if (!(cin >> c)) break;
      if (c != '(') break;
      ans[self(self)] = a;
    }
    return a;
  };
  read(read);
  for (auto e : ans) {
    cout << e + 1 << ' ';
  }
}