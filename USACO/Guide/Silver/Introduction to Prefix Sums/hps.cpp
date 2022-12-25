#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

U h_ps[100001];
U p_ps[100001];
U s_ps[100001];

int main(void) {
  freopen("hps.in", "r", stdin);
#if !defined(ETHANKIM8683)
  freopen("hps.out", "w", stdout);
#endif // !defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  for (U i = 1; i <= n; i++) {
    C g;
    cin >> g;
    switch (g) {
      case 'H':
        h_ps[i] = 1;
        break;
      case 'P':
        p_ps[i] = 1;
        break;
      case 'S':
        s_ps[i] = 1;
        break;
    }
  }
  U h_sum = 0;
  U p_sum = 0;
  U s_sum = 0;
  for (U i = 1; i <= n; i++) {
    h_sum += h_ps[i];
    p_sum += p_ps[i];
    s_sum += s_ps[i];
    h_ps[i] = h_sum;
    p_ps[i] = p_sum;
    s_ps[i] = s_sum;
  }
  U wins = 0;
  for (U i = 0; i < n; i++) {
    const U h_before = h_ps[i];
    const U p_before = p_ps[i];
    const U s_before = s_ps[i];
    const U h_after = h_sum - h_before;
    const U p_after = p_sum - p_before;
    const U s_after = s_sum - s_before;
    const U h_wins = h_before + max(p_after, s_after);
    const U p_wins = p_before + max(h_after, s_after);
    const U s_wins = s_before + max(p_after, h_after);
    wins = max(wins, max(h_wins, max(p_wins, s_wins)));
  }
  printf("%u\n", wins);
  return 0;
}