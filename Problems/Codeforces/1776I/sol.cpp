#include <bits/stdc++.h>

#include "ethankim8683/data_structures.hpp"
#include "ethankim8683/geometry.hpp"

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  ordered_map<int, complex<i64>> V;
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    V.insert({i, {x, y}});
  }

  // if there's an even number of vertices, play as Alberto, since we can always
  // choose the smallest triangle and not introduce smaller ones (the smallest
  // triangle is never the larger of the two sub-triangles of a trapezoid)
  //
  // if there's an odd number of vertices, Beatrice will always have no more
  // than half the area of the polygon after Alberto's first move using the
  // strategy above, so Alberto loses and we play as Beatrice

  int me = N % 2;
  cout << (string[]) {"Alberto", "Beatrice"}[me] << endl;

  for (int i = 0; i < N - 2; i++) {
    if (i % 2 == me) {
      pair<i64, int> best = {INF, -1};
      for (int j = 0; j < V.size(); j++) {
        auto A = V.find_by_order(j)->second,
             B = V.find_by_order((j + 1) % V.size())->second,
             C = V.find_by_order((j + 2) % V.size())->second;
        best = min(best, {cross(A - B, B - C),
                          V.find_by_order((j + 1) % V.size())->first});
      }
      int p = best.second;
      cout << p + 1 << endl;
      V.erase(p);
    } else {
      int q;
      cin >> q;
      q--;
      V.erase(q);
    }
  }
}
