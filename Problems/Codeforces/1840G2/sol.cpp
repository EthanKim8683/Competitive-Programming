#include <bits/stdc++.h>

#include "ethankim8683/combinatorics.hpp"

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int X;
  cin >> X;

  auto query = [&](int k) -> int {
    if (k < 0) {
      cout << "- " << -k << endl;
    } else {
      cout << "+ " << k << endl;
    }
    int rv;
    cin >> rv;
    return rv;
  };

  // I need to find an array containing multiples of each number of sectors as
  // subarray sums
  //
  // try a multiple of many numbers, then break it down
}
