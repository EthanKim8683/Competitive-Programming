#include <bits/stdc++.h>

using namespace std;

const int MAXQ = 10;

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int T;
  if (argc > 1) {
    T = 1;
  } else {
    cin >> T;
  }

  while (T--) {
    int N;
    if (argc > 1) {
      N = 100;
    } else {
      cin >> N;
    }

    vector<int> A;
    if (argc > 1) {
      A.resize(N);
      for (auto &e : A) {
        e = rng() % 2;
      }
    }

    int Q = 0;
    auto type = [&](int i) -> string {
      Q++;
      assert(Q <= MAXQ);
      if (argc > 1) {
        assert(0 <= i and i < N);
        return (string[]) {"lily", "rose"}[A[i]];
      } else {
        cout << "type " << i + 1 << endl;
        string rv;
        cin >> rv;
        return rv;
      }
    };
    auto multi = [&](int j) -> int {
      Q++;
      assert(Q <= MAXQ);
      if (argc > 1) {
        assert(0 <= j and j <= N);
        return count(A.begin(), A.begin() + j, 0) *
               count(A.begin() + j, A.end(), 1);
      } else {
        cout << "multi " << j << endl;
        int rv;
        cin >> rv;
        return rv;
      }
    };
    auto answer = [&](int k) -> void {
      if (argc > 1) {
        assert(0 <= k and k <= N);
        assert(count(A.begin(), A.begin() + k, 0) ==
               count(A.begin() + k, A.end(), 1));
      } else {
        cout << "answer " << k << endl;
      }
    };

    int l = 0, r = N;
    while (l < r) {
      int m = l + (r - l) / 2;
      type(m) == "lily" ? r = m : l = m + 1;
    }
    if (l + 1 <= N) {
      int m1 = multi(l + 1);
      if (m1 != 0) {
        int m2 = multi(l), n1, n2;
        if (m1 - m2 > 0) {
          n2 = m1 - m2;
          n1 = m2 / n2;
        } else {
          n1 = m2 - m1;
          n2 = m2 / n1;
        }
        answer(l + n2 - n1);
        continue;
      }
    }
    if (l - 1 >= 0) {
      int m1 = multi(l - 1);
      if (m1 != 0) {
        int m2 = multi(l), n1, n2;
        if (m1 - m2 > 0) {
          n1 = m1 - m2;
          n2 = m2 / n1;
        } else {
          n2 = m2 - m1;
          n1 = m2 / n2;
        }
        answer(l + n2 - n1);
        continue;
      }
    }
    answer(l);
  }
}
