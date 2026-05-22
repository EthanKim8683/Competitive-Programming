#include <bits/stdc++.h>

using namespace std;

int main() {
  ofstream fout("inputs/2.txt");

  mt19937 rng(time(nullptr));

  int N = 1000, Q = 0;  // N + 1;
  fout << N << ' ' << Q << '\n';

  for (int i = 0; i < N; i++) {
    int a = rng() % (int) 1e9 + 1, b = rng() % (int) 1e9 + 1;
    fout << a << ' ' << b << '\n';
  }

  for (int i = 0; i <= N; i++) {
    fout << i << '\n';
  }
}
