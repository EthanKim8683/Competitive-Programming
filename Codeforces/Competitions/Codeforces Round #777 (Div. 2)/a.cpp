#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>

using namespace std;

// start 10:49
// end 10:50

int main(void) {
#if !defined(ONLINE_JUDGE)
  freopen("a.in", "r", stdin);
#endif // !defined(ONLINE_JUDGE)
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  unsigned int n;
  cin >> n;
  while (n--) {
    unsigned int t;
    cin >> t;
    const unsigned int mod = t % 3;
    if (mod == 1)
      printf("1");
    for (unsigned int i = t / 3; i--;)
      printf("21");
    if (mod == 2)
      printf("2");
    printf("\n");
  }
  return 0;
}