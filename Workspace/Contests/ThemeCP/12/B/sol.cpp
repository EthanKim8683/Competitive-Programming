#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifdef ETHANKIM8683
  mt19937 rng(time(nullptr));

  int N = rng() % (1000 + 1 - 2) + 2, X = rng() % (N - 1) + 1;

  auto query = [&](int c) -> int {
    X += c;
    return X / N;
  };

  auto answer = [&](int x) -> void {
    cout << x << ' ' << X << '\n';
    cout << (x == X ? "ok" : "wa");
  };
#else
  int N;
  cin >> N;

  auto query = [&](int c) -> int {
    cout << "+ " << c << endl;
    int rv;
    cin >> rv;
    return rv;
  };

  auto answer = [&](int x) -> void { cout << "! " << x << endl; };
#endif

  int sum = 0, pv = 0, pd = 0;
  auto check = [&](int v) -> bool {
    int c = (v - pv + N) % N, d = query(c);
    bool rv = d > pd;
    sum += c;
    pd = d;
    pv = v;
    return rv;
  };

  int l = 1, r = N - 1;
  while (l < r) {
    int m = l + (r - l) / 2;
    check(m) ? r = m : l = m + 1;
  }
  answer(sum + N - l);
}
