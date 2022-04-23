#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;
using I = int;

pair<U, U*> times[400000];
pair<U, U> customers[200000];
I ps[400001];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("customers.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U t = 0;
  for (U i = n; i--;) {
    auto& a_time = times[t++];
    auto& b_time = times[t++];
    cin >> a_time.first >> b_time.first;
    auto& customer = customers[i];
    a_time.second = &customer.first;
    b_time.second = &customer.second;
  }
  sort(times, times + t);
  for (U i = 0; i < t; i++)
    *times[i].second = i;
  for (U i = n; i--;) {
    const auto [a, b] = customers[i];
    ps[a]++;
    ps[b + 1]--;
  }
  U result = 0;
  U sum = 0;
  for (U i = 0; i < t; i++) {
    sum += ps[i];
    result = max(result, sum);
  }
  printf("%u\n", result);
  return 0;
}