#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<int> X(N);
  for (auto &e : X) cin >> e;

  // if there's a section already chosen within Alessia's interval, Bernardo
  // will choose it and win
  //
  // for Bernardo to win, he should choose a length to win with, then ensure
  // that it's impossible to have a gap no smaller than this length
  //
  // for each length greater than this one, we can always choose a book
  // following the pattern of books that ensure the gap
  //
  // if we choose a length L, M <= KL-1 means Bernardo wins, where K is the
  // number of lengths no shorter than L
  //
  // can we do better? no because there will always be a gap >= L if this
  // condition isn't satisfied, which Alessia can choose
  //
  // playing as Alessia, this means choosing lengths in non-increasing order
  // (for simplicity) and simply looking for gaps to fit the length

  sort(X.rbegin(), X.rend());
  int L = -1;
  for (int i = 0; i < N; i++) {
    if (M <= (i + 1) * X[i] - 1) {
      L = X[i];
      break;
    }
  }

  vector<bool> cut(M, false);
  if (L != -1) {
    cout << "Bernardo" << endl;
    for (int i = 0; i < N; i++) {
      int y, a;
      cin >> y >> a;
      a--;
      int b = -1;
      for (int j = a; j < a + y; j++) {
        if (cut[j]) {
          b = j;
          goto MOVE;
        }
      }
      if (y >= L) {
        for (int j = a; j < a + y; j++) {
          if (j % L == L - 1) {
            b = j;
            goto MOVE;
          }
        }
      } else {
        b = a;
      }
    MOVE:
      cout << b + 1 << endl;
      cut[b] = true;
    }
  } else {
    cout << "Alessia" << endl;
    for (auto e : X) {
      int y, a;
      for (int i = 0; i + e <= M; i++) {
        bool ok = true;
        for (int j = i; j < i + e; j++) {
          ok = ok and !cut[j];
        }
        if (ok) {
          y = e;
          a = i;
          break;
        }
      }
      cout << y << ' ' << a + 1 << endl;
      int b;
      cin >> b;
      b--;
      cut[b] = true;
    }
  }
}
