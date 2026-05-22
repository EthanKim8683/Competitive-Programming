#include <bits/stdc++.h>

#include "ethankim8683/algebra"

using namespace std;
using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, X, Y, VX, VY;
    cin >> N >> X >> Y >> VX >> VY;

    int g = gcd(VX, VY), vx = VX / g, vy = VY / g;

    // if we mirror the triangle, then tile the square infinitely, we can see
    // that the plane, travelling without without getting reflected, reaches a
    // vertex when n | x and n | y
    //
    // for each side (horizontal/vertical), let's only look at the plane
    // starting when it hits the side and has integer coordinates
    //
    // now, each side has equations of the form x * a = b, and I think we can
    // combine them to form a single linear Diophantine equation

    // xx * vx + yx * N = -X
    // xy * vy + yy * N = -Y

    if (-X % gcd(vx, N) != 0 or -Y % gcd(vy, N) != 0) {
      cout << -1 << '\n';
      continue;
    }
    auto sol_x = diop_linear<i64>(vx, N, -X).min_nonneg_sol_for_x();
    auto sol_y = diop_linear<i64>(vy, N, -Y).min_nonneg_sol_for_x();

    // dx = lcm(vx, N) / vx
    // dy = lcm(vy, N) / vy
    // t = xx' * dx + xx
    // t = xy' * dy + xy
    // xx' * dx + xx = xy' * dy + xy
    // xx' * dx - xy' * dy = xy - xx

    int dx = lcm(vx, N) / vx, dy = lcm(vy, N) / vy;
    int xx = sol_x.x(), xy = sol_y.x();

    if ((xy - xx) % gcd(dx, -dy) != 0) {
      cout << -1 << '\n';
      continue;
    }
    auto sol_t = diop_linear<i64>(dx, -dy, xy - xx).min_nonneg_sol_for_x();

    int t = sol_t.x() * dx + xx;
    cout << t << '\n';
  }
}