#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I K = 2000000;
const I X = 10527449;

I facs[X + 1];
I prds[X + 1];
vector<I> spcs;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  fill_n(prds, X + 1, 1);
  for (I i = 2; i <= X; i++) {
    if (facs[i] == 0) {
      for (I j = i + i; j <= X; j += i) {
        facs[j]++;
        prds[j] *= i;
      }
    }
  }
  for (I i = 2; i <= X; i++)
    if (facs[i] == 2 && prds[i] == i)
      spcs.push_back(i);
  I t;
  cin >> t;
  while (t--) {
    I k;
    cin >> k;
    printf("%i\n", spcs[k - 1]);
  }
  return 0;
}