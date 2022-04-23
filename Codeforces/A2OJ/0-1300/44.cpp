#include <iostream>
#include <cstdio>
#include <unordered_set>

using namespace std;

using U = unsigned;
using S = string;

unordered_multiset<S> games;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("44.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  while (n--) {
    S s;
    cin >> s;
    games.insert(s);
  }
  S result_team;
  U result_wins = 0;
  for (const auto team : games) {
    const U wins = games.count(team);
    if (wins > result_wins) {
      result_wins = wins;
      result_team = team;
    }
  }
  printf("%s", result_team.c_str());
  return 0;
}