#include <bits/stdc++.h>

#include "transfer.h"

using namespace std;

int main(int argc, char **argv) {
  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int T;
  if (argc > 1) {
    T = 200000;
  } else {
    cin >> T;
  }

  while (T--) {
    int N;
    if (argc > 1) {
      N = rng() % 2 == 0 ? 63 : 255;
    }

    int C;
    if (argc > 1) {
    } else {
      cin >> C;
    }

    string S;
    if (argc > 1) {
      S.resize(N);
      for (auto &e : S) {
        e = rng() % 2 + '0';
      }
    } else {
      cin >> S;
      N = S.size();
    }

    vector<int> source;
    for (auto e : S) {
      source.push_back(e - '0');
    }

    auto data = source;
    for (auto e : get_attachment(source)) {
      data.push_back(e);
    }

    if (argc > 1) {
      C = rng() % (data.size() + 1) - 1;
    }

    if (C != -1) {
      data[C] ^= 1;
    }

    assert(retrieve(data) == source);
  }
}
