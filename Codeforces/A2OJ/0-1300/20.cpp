#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("20.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  C d;
  cin >> d;
  U a_count = d == '1';
  U b_count = d == '2';
  U c_count = d == '3';
  while (true) {
    C d;
    cin >> d;
    if (d != '+')
      break;
    cin >> d;
    a_count += d == '1';
    b_count += d == '2';
    c_count += d == '3';
  }
  if (a_count) {
    printf("1");
    while (--a_count)
      printf("+1");
    while (b_count--)
      printf("+2");
    while (c_count--)
      printf("+3");
  } else if (b_count) {
    printf("2");
    while (--b_count)
      printf("+2");
    while (c_count--)
      printf("+3");
  } else if (c_count) {
    printf("3");
    while (--c_count)
      printf("+3");
  }
  return 0;
}