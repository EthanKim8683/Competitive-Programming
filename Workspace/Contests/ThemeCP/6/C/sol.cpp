#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifdef ETHANKIM8683
  int T = 1;
  while (T--) {
    int N = 2000;

    static mt19937 rng(time(nullptr));
    vector<int> A_t(N);
    iota(A_t.begin(), A_t.end(), 1);
    shuffle(A_t.begin(), A_t.end(), rng);
    int X_t = rng() % N + 1;

    int Q = 0;
#else
  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;
#endif

    auto query = [&](int i) -> char {
      cout << "? " << i + 1 << endl;
#ifdef ETHANKIM8683
      Q++;
      if (Q > 40 * N) {
        cerr << "query limit exceeded\n";
        exit(0);
      }

      if (A_t[i] > X_t) {
        X_t++;
        return '>';
      } else if (A_t[i] < X_t) {
        X_t--;
        return '<';
      } else {
        return '=';
      }
#else
      string s;
      cin >> s;
      if (s == "-1") exit(0);
      return s[0];
#endif
    };

    auto answer = [&](vector<int> A) -> void {
      cout << "! ";
      for (auto e : A) {
        cout << e << ' ';
      }
      cout << endl;
#ifdef ETHANKIM8683
      cout << (equal(A.begin(), A.end(), A_t.begin()) ? "ok" : "wa") << '\n';
#endif
    };

    auto find_ext = [&](char c) -> int {
      int rv = 0;
      while (query(0) != '=');
      for (int i = 1; i < N; i++) {
        if (query(i) != c) {
          query(rv);
        } else {
          rv = i;
          while (query(i) != '=');
        }
      }
      return rv;
    };
    int i_min = find_ext('<'), i_max = find_ext('>'), X = N;

    auto query_ = [&](int i) -> char {
      char c = query(i);
      X += (c == '>') - (c == '<');
      return c;
    };

    auto set = [&](int X_) -> void {
      while (X < X_) {
        query_(i_max);
      }
      while (X > X_) {
        query_(i_min);
      }
    };

    vector<tuple<int, int, vector<int>>> queries;
    queries.push_back({2, N, {}});
    for (int i = 0; i < N; i++) {
      if (i != i_min and i != i_max) {
        get<2>(queries.back()).push_back(i);
      }
    }
    vector<int> ans(N);
    ans[i_min] = 1;
    ans[i_max] = N;
    bool ltr = true;
    while (queries.size() > 0) {
      auto queries0 = queries;
      queries.clear();

      sort(queries0.begin(), queries0.end());
      if (!ltr) {
        reverse(queries0.begin(), queries0.end());
      }

      for (auto [l, r, I] : queries0) {
        int m = l + (r - l) / 2;

        if (I.size() == 1) {
          ans[I[0]] = m;
          continue;
        }

        vector<int> I_l, I_r;
        for (auto i : I) {
          set(m);
          auto c = query_(i);
          if (c == '<') {
            I_l.push_back(i);
          } else if (c == '>') {
            I_r.push_back(i);
          } else {
            ans[i] = m;
          }
        }

        if (I_l.size() > 0) {
          queries.push_back({l, m, I_l});
        }
        if (I_r.size() > 0) {
          queries.push_back({m + 1, r, I_r});
        }
      }

      ltr = !ltr;
    }
    answer(ans);
  }
}
