#include <iostream>
#include <cstdio>

using namespace std;

// start 1:17
// end 1:19

int main(void) {
#if !defined(ONLINE_JUDGE)
  freopen("a.in", "r", stdin);
#endif // !defined(ONLINE_JUDGE)
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  unsigned int t;
  cin >> t;
  while (t--) {
    unsigned int n;
    cin >> n;
    unsigned int max_a;
    unsigned int max_b = 0;
    while (n--) {
      unsigned int a;
      cin >> a;
      if (a >= max_b) {
        max_a = max_b;
        max_b = a;
      } else if (a > max_a)
        max_a = a;
    }
    printf("%u\n", max_a + max_b);
  }
  return 0;
}