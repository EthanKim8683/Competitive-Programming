#include <bits/stdc++.h>

#include "question.h"

using namespace std;

const int MAXH = 12;

int fact(int n) {
  static vector<int> memo = {1};
  while (memo.size() <= n) {
    memo.push_back(memo.back() * memo.size());
  }
  return memo[n];
}

int binom(int n, int k) {
  if (n < 0 or k < 0 or n - k < 0) return 0;
  return fact(n) / (fact(k) * fact(n - k));
}

int get_key(int x) {
  x -= 1;
  int k = MAXH / 2, rv = 0;
  for (int i = 0; i < MAXH; i++) {
    int y = binom(MAXH - (i + 1), k);
    if (x >= y) {
      rv |= 1 << i;
      x -= y;
      k -= 1;
    }
  }
  return rv;
}

int encode(int n, int x, int y) {
  int k1 = get_key(x), k2 = get_key(y);
  for (int i = 0; i < MAXH; i++) {
    if ((k1 >> i & 1) == 1 and (k2 >> i & 1) == 0) return i + 1;
  }
  assert(false);
}

int decode(int n, int q, int h) { return get_key(q) >> (h - 1) & 1; }
