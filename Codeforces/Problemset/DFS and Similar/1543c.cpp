#include <iostream>
#include <cstdio>

#define SCALE 1000000000

using namespace std;

using I = int;
using Lli = long long int;
using Lf = long double;

Lli v;
I depth = 1;

Lli dfs(Lli c, Lli m, Lli p) {
  Lli result = depth * p;
  depth++;
  if (c > 0) {
    if (c > v) {
      if (m > 0)
        result += c * dfs(c - v, m + v / 2, p + v / 2) / SCALE;
      else
        result += c * dfs(c - v, -1, p + v) / SCALE;
    } else {
      if (m > 0)
        result += c * dfs(-1, m + c / 2, p + c / 2) / SCALE;
      else
        result += c * dfs(-1, -1, p + c) / SCALE;
    }
  }
  if (m > 0) {
    if (m > v) {
      if (c > 0)
        result += m * dfs(c + v / 2, m - v, p + v / 2) / SCALE;
      else
        result += m * dfs(-1, m - v, p + v) / SCALE;
    } else {
      if (c > 0)
        result += m * dfs(c + m / 2, -1, p + m / 2) / SCALE;
      else
        result += m * dfs(-1, -1, p + m) / SCALE;
    }
  }
  depth--;
  return result;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("1543c.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    Lf c_pre, m_pre, p_pre, v_pre;
    cin >> c_pre >> m_pre >> p_pre >> v_pre;
    Lli c = (Lli) (c_pre * SCALE);
    Lli m = (Lli) (m_pre * SCALE);
    Lli p = (Lli) (p_pre * SCALE);
    v = (Lli) (v_pre * SCALE);
    printf("%.7Lf\n", (Lf) (dfs(c, m, p)) / SCALE);
  }
  return 0;
}