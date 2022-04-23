#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>

using namespace std;

int main(void) {
#if !defined(ONLINE_JUDGE)
  freopen("c.in", "r", stdin);
#endif // !defined(ONLINE_JUDGE)
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    char table[10000];
    char cache[10000] = { 0 };
    vector<tuple<int, int, int, int>> moves;
    const int a = n * m;
    for (int i = 0; i < a; i++) {
      char cell;
      cin >> cell;
      table[i] = cell - '0';
    }
    int n_index = a;
    for (int i = n; i--;) {
      int a_index = n_index - 1;
      n_index -= m;
      while (a_index > n_index) {
        char a_color;
        do {
          a_color = table[a_index];
          if (a_color != cache[a_index])
            break;
          a_index--;
        } while (a_index >= n_index);
        if (a_index < n_index)
          continue;
        int b_index = a_index;
        char paint = !a_color;
        while (--b_index >= n_index) {
          const char b_color = table[b_index];
          if (b_color != paint)
            break;
          paint = !paint;
        }
        int height = 1;
        int width = a_index - b_index;
        if (a_color ^ !(width & 1)) { // starts with 1
          if (b_index < n_index) {    // 1 at x = 0
            if (b_index < 0) {        // 1 at x = 0, y = 0
              printf("-1\n");
              goto SKIP;
            } else
              height++;
          } else
            width++;
        }
        int y_index = a_index;
        char y_paint = a_color;
        for (int y = height; y--;) {
          int x_index = y_index;
          char x_paint = y_paint;
          for (int x = width; x--;) {
            cache[x_index] = x_paint;
            x_index--;
            x_paint = !x_paint;
          }
          y_index -= m;
          y_paint = !y_paint;
        }
        int u_x = a_index % m + 1;
        int u_y = a_index / m + 1;
        int l_x = u_x - width + 1;
        int l_y = u_y - height + 1;
        moves.push_back(make_tuple(l_y, l_x, u_y, u_x));
        a_index = b_index;
      }
    }
    printf("%lu\n", moves.size());
    for (const auto& move : moves) {
      printf("%i %i %i %i\n", get<0>(move), get<1>(move), get<2>(move), get<3>(move));
    }
    SKIP:;
  }
  return 0;
}