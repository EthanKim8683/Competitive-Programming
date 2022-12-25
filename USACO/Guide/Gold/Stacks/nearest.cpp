#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

using I = int;

const I N = 2e5;

stack<pair<I, I>> vals;

I main(void) {
#ifdef ETHANKIM8683
  freopen("nearest.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 1; i <= n; i++) {
    I x;
    cin >> x;
    while (!vals.empty() && vals.top().first >= x)
      vals.pop();
    if (vals.empty())
      printf("0 ");
    else
      printf("%i ", vals.top().second);
    vals.push({x, i});
  }
  return 0;
}