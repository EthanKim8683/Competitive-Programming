#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int W, S, C, K;
  cin >> W >> S >> C >> K;

  auto yes = [&]() -> void {
    cout << "YES";
    exit(0);
  };

  auto no = [&]() -> void {
    cout << "NO";
    exit(0);
  };

  if (C == 0) {
    if (min(S, W) < K) {
      yes();
    } else if (min(S, W) == K) {
      if (max(S, W) <= 2 * K) {
        yes();
      } else {
        no();
      }
    } else {
      no();
    }
  }

  if (W == 0) {
    if (min(S, C) < K) {
      yes();
    } else if (min(S, C) == K) {
      if (max(S, C) <= 2 * K) {
        yes();
      } else {
        no();
      }
    } else {
      no();
    }
  }

  if (S < K) {
    yes();
  } else if (S == K) {
    if (W + C <= 2 * K) {
      yes();
    } else {
      no();
    }
  } else {
    if (W + C < K) {
      yes();
    } else if (W + C == K) {
      if (S <= 2 * K) {
        yes();
      } else {
        no();
      }
    } else {
      no();
    }
  }
}