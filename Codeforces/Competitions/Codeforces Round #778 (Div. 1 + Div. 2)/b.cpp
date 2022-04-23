#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main(void) {
#if !defined(ONLINE_JUDGE)
  freopen("b.in", "r", stdin);
#endif // !defined(ONLINE_JUDGE)
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  unsigned int t;
  cin >> t;
  while (t--) {
    char s[200001];
    char* p = s;
    cin >> s;
    unsigned int n = strlen(s);
    bool f;
    do {
      f = false;
      for (unsigned int i = 1; i < n; i++) {
        while (p[i] == p[0]) {
          p++;
          n--;
          f = true;
        }
      }
    } while (f);
    printf("%s\n", p);
  }
  return 0;
}