#include <iostream>
#include <cstdio>
#include <numeric>
#include <unordered_map>

using namespace std;

using I = int;
using Lli = long long int;
using C = char;

const I N = 5e5;

C s[N + 1];
unordered_map<Lli, I> cnts;

int main(void) {
#ifdef ETHANKIM8683
  freopen("diluc.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n;
    cin >> s;
    cnts.clear();
    I d_cnt = 0;
    I k_cnt = 0;
    for (I i = 0; i < n; i++) {
      d_cnt += s[i] == 'D';
      k_cnt += s[i] == 'K';
      const I den = gcd(d_cnt, k_cnt);
      const Lli d_num = d_cnt / den;
      const Lli k_num = k_cnt / den;
      const Lli hsh = d_num << 19 | k_num;
      cnts[hsh]++;
      printf("%i ", cnts[hsh]);
    }
    printf("\n");
  }
  return 0;
}