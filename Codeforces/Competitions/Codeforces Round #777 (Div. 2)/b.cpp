#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>

using namespace std;

// start 10:53
// end 11:51

int main(void) {
#if !defined(ONLINE_JUDGE)
  freopen("b.in", "r", stdin);
#endif // !defined(ONLINE_JUDGE)
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  unsigned int t;
  cin >> t;
  while (t--) {
    unsigned int n, m;
    cin >> n >> m;
    unsigned char table[10000];
    const unsigned int a = n * m;
    for (unsigned int i = 0; i < a; i++) {
      unsigned char x;
      cin >> x;
      table[i] = x - '0';
    }
    bool elegant = true;
    unsigned int index = 0;
    for (unsigned int y = n; --y;) {
      for (unsigned int x = m; --x;) {
        if (table[index] + table[index + m + 1] + 
            table[index + m] + table[index + 1] == 3) {
          elegant = false;
          goto RESULT;
        }
        index++;
      }
      index++;
    }
    RESULT:
    printf("%s\n", elegant ? "YES" : "NO");
  }
  return 0;
}