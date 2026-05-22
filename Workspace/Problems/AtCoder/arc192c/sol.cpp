#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>
struct dsu_with_potentials {
 private:
  int n;
  vector<int> par;
  vector<T> V;

 public:
  dsu_with_potentials(int _n) : n(_n), par(n, -1), V(n, 0) {}

  int leader(int a) {
    if (par[a] < 0) return a;
    int p = leader(par[a]);
    V[a] += V[par[a]];
    return par[a] = p;
  }

  bool merge(int a, int b, T v) {
    int a_ = leader(a), b_ = leader(b);
    if (a_ == b_) return V[b] - V[a] == v;
    if (par[a_] > par[b_]) {
      swap(a_, b_);
      swap(a, b);
      v = -v;
    }
    par[a_] += par[b_];
    par[b_] = a_;
    V[b_] = v + V[a] - V[b];
    return true;
  }

  bool same(int a, int b) { return leader(a) == leader(b); }

  int size(int a) { return -par[a]; }

  T potential(int a) {
    leader(a);
    return V[a];
  }

  T voltage(int a, int b) { return potential(b) - potential(a); }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifdef ETHANKIM8683
  mt19937 rng(time(nullptr));

  int N = 5000;

  vector<int> _P(N);
  iota(_P.begin(), _P.end(), 0);
  do {
    shuffle(_P.begin(), _P.end(), rng);
  } while (_P[0] > _P[1]);

  vector<int> _A(N);
  for (auto &e : _A) {
    e = rng() % (int) 1e9 + 1;
  }

  vector<i64> _ps(N + 1);
  _ps[0] = 0;
  for (int i = 0; i < N; i++) {
    _ps[i + 1] = _ps[i] + _A[i];
  }
  auto query = [&](int s, int t) -> i64 {
    static int count = 0;
    count++;
    if (count > 2 * N) {
      cout << "query limit exceeded";
      exit(0);
    }
    s = _P[s];
    t = _P[t];
    if (s > t) {
      swap(s, t);
    }
    return _ps[t + 1] - _ps[s];
  };

  auto answer = [&](vector<int> P, vector<int> A) -> void {
    cout << "expected:\n";
    for (auto e : _P) {
      cout << e << ' ';
    }
    cout << '\n';
    for (auto e : _A) {
      cout << e << ' ';
    }
    cout << '\n';
    cout << "got:\n";
    for (auto e : P) {
      cout << e << ' ';
    }
    cout << '\n';
    for (auto e : A) {
      cout << e << ' ';
    }
    cout << '\n';
    cout << (equal(A.begin(), A.end(), _A.begin()) and
                     equal(P.begin(), P.end(), _P.begin())
                 ? "ok"
                 : "wa")
         << '\n';
  };
#else
  int N;
  cin >> N;

  auto query = [&](int s, int t) -> i64 {
    cout << "? " << s + 1 << ' ' << t + 1 << endl;
    i64 rv;
    cin >> rv;
    if (rv == -1) exit(0);
    return rv;
  };

  auto answer = [&](vector<int> P, vector<int> A) -> void {
    cout << "! ";
    for (auto e : P) {
      cout << e + 1 << ' ';
    }
    for (auto e : A) {
      cout << e << ' ';
    }
    cout << endl;
    exit(0);
  };
#endif

  dsu_with_potentials<i64> d(2 * N);
  i64 sum0 = query(0, 1);
  d.merge(2 * 0, 2 * 1 + 1, sum0);
  auto query_ = [&](int i) -> void {
    if (i == 0 or i == 1) return;
    i64 l = query(0, i), r = query(1, i);
    if (l > sum0 and r < l) {
      d.merge(2 * 0, 2 * i + 1, l);
      d.merge(2 * 1, 2 * i + 1, r);
    } else if (r > sum0 and l < r) {
      d.merge(2 * i, 2 * 0 + 1, l);
      d.merge(2 * i, 2 * 1 + 1, r);
    } else {
      d.merge(2 * 0, 2 * i + 1, l);
      d.merge(2 * i, 2 * 1 + 1, r);
    }
  };
  for (int i = 0; i < N; i++) {
    query_(i);
  }

  vector<i64> ps;
  for (int i = 0; i < 2 * N; i++) {
    if (d.same(0, i)) {
      ps.push_back(d.potential(i));
    }
  }
  sort(ps.begin(), ps.end());
  ps.erase(unique(ps.begin(), ps.end()), ps.end());

  vector<int> P(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if ((!d.same(0, 2 * i) or d.potential(2 * i) == ps[j]) and
          (!d.same(0, 2 * i + 1) or d.potential(2 * i + 1) == ps[j + 1])) {
        P[i] = j;
        break;
      }
    }
  }

  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    A[i] = ps[i + 1] - ps[i];
  }

  answer(P, A);
}
