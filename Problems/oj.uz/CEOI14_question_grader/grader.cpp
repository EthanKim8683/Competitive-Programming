#include <bits/stdc++.h>

#include "question.h"

using namespace std;

int main(int argc, char **argv) {
  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int N, T;
  if (argc > 1) {
    N = 920;
    T = 2000000;
  } else {
    cin >> N >> T;
  }

  int hmax = 0;
  while (T--) {
    int X, Y, Q;
    if (argc > 1) {
      do {
        X = rng() % N + 1;
        Y = rng() % N + 1;
      } while (X == Y);
      Q = rng() % 2 == 0 ? X : Y;
    } else {
      cin >> X >> Y >> Q;
    }

    int h = encode(N, X, Y);
    hmax = max(hmax, h);
    assert(decode(N, Q, h) == (X == Q ? 1 : 0));
  }
  assert(hmax <= 12);
}
