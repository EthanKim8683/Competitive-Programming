#include <bits/stdc++.h>

using namespace std;

const int K1 = 130;
const int K2 = 9385;
const int K3 = 2573;
const int K4 = (int) 2.5e4 - (K2 + K3);

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
#ifdef ETHANKIM8683
    static mt19937 rng(time(nullptr));

    int $W = rng() % (int) 1e5 + 1;
    cin >> $W;
#endif

    auto simulate = [&](int w, vector<int> A) -> int {
      if (*max_element(A.begin(), A.end()) > w) return 0;

      int l = 1, s = 0;
      for (auto e : A) {
        if (s + e <= w) {
          s += e;
        } else {
          l++;
          s = e;
        }
      }
      return l;
    };

#ifdef ETHANKIM8683
    int $Q = 0;
    auto query = [&](vector<int> A) -> int {
      cerr << A.size() << '\n';
      $Q += A.size();
      if ($Q > (int) 2.5e4) {
        cout << $W << ": query limit exceeded\n";
        exit(0);
      }

      return simulate($W, A);
    };
#else
    auto query = [&](vector<int> A) -> int {
      cout << "? " << A.size();
      for (auto e : A) {
        cout << ' ' << e;
      }
      cout << endl;

      int rv;
      cin >> rv;
      if (rv == -1) {
        exit(0);
      }
      return rv;
    };
#endif

#ifdef ETHANKIM8683
    auto answer = [&](int W) -> void {
      if ($W != W) {
        cout << $W << ": wrong answer\n";
        exit(0);
      }
    };
#else
    auto answer = [&](int W) -> void { cout << "! " << W << endl; };
#endif

    vector<int> A1(K4, K1 + 1);
    int l1 = query(A1);
    if (l1 == 0) {
      vector<int> A2;
      for (int i = 0; i < K2; i++) {
        A2.push_back(1);
      }
      for (int i = 0; i < K3; i++) {
        A2.push_back(2);
      }
      int l2 = query(A2);
      for (int w = 1; w <= K1; w++) {
        if (l2 != simulate(w, A2)) continue;
        answer(w);
        break;
      }
    } else {
      int w1 = (K4 + l1 - 1) / l1 * (K1 + 1),
          w2 = (K4 + l1 - 1) / (l1 - 1) * (K1 + 1);
      vector<int> A2;
      for (int i = w1 + 1; i < w2; i++) {
        A2.push_back(w1);
        A2.push_back(i - w1);
      }
      answer(w1 + A2.size() - query(A2));
    }
  }
}