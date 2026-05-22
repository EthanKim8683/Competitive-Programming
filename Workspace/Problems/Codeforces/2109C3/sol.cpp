#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int INF = 1e9;
const i64 MINX = 1;
const i64 MAXX = 1e18;
const int K = 9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // f(9) = mul 9, digit, digit

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    auto get_jury_response = [&]() -> bool {
      int rv;
      cin >> rv;
      if (rv == -1) {
        exit(0);
      }
      return rv == 1;
    };

    auto add = [&](i64 y) -> bool {
      cout << "add " << y << endl;
      return get_jury_response();
    };

    auto mul = [&](i64 y) -> bool {
      cout << "mul " << y << endl;
      return get_jury_response();
    };

    auto digit = [&]() -> bool {
      cout << "digit" << endl;
      return get_jury_response();
    };

    auto answer = [&]() -> void {
      cout << "!" << endl;
      assert(get_jury_response());
    };

    mul(9);
    digit();
    digit();
    if (N != 9) {
      add(N - 9);
    }
    answer();
  }
}
