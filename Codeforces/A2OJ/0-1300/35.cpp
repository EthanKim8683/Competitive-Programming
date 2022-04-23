#include <iostream>
#include <cstdio>
#include <cmath>
#include <numeric>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("35.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U a, b, c;
  cin >> a >> b >> c;
  const U ab = gcd(a, b);
  const U bc = gcd(b, c);
  const U ca = gcd(c, a);
  const U a_a = ca * ab / a;
  const U b_a = ab * bc / b;
  const U c_a = bc * ca / c;
  const U ab_a = gcd(a_a, b_a);
  const U bc_a = gcd(b_a, c_a);
  const U ca_a = gcd(c_a, a_a);
  U ab_r = ab / ab_a;
  U bc_r = bc / bc_a;
  U ca_r = ca / ca_a;
  const U f = sqrt(a / (ca_r * ab_r));
  ab_r *= f;
  bc_r *= f;
  ca_r *= f;
  printf("%u\n", 4 * (ab_r + bc_r + ca_r));
  return 0;
}