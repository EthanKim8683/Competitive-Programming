#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;
  K--;

  auto mod = [&](int x, int y) -> int { return (x % y + y) % y; };

  auto repeat = [&](string s, int n) -> string {
    string rv = "";
    for (int i = 0; i < n; i++) {
      rv += s;
    }
    return rv;
  };

  if (K < N / 2) {
    cout << repeat("LDLU", (N / 2 + 1) / 2);
    cout << "DR";
    cout << "LDRU";
    cout << repeat("LDRU", mod(K - 1, N / 2));
    cout << "L";
  } else {
    cout << repeat("RDRU", N / 2 / 2);
    cout << "DL";
    cout << "RDLU";
    cout << repeat("RDLU", mod(N - 5 - K, N / 2));
    cout << repeat("RURD", (N / 2 + 1) / 2);
    cout << repeat("LULD", N / 2 - 1);
    cout << "RDL";
  }
}
