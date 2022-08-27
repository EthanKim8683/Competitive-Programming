#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;

vector<I> adjs[N];

/*
find longest path
disconnect each subtree not part of the path
attach at end of path, rooted at end of their own longest path
repeat

could do a bfs for each subtree
queue subtrees not part of path in each path traversal
then just add them until empty
*/

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n;
    for (I i = 0; i < n; i++)
      adjs[i].clear();
    for (I i = 0; i < n - 1; i ++) {
      I a, b;
      cin >> a >> b;
      a--;
      b--;
      adjs[a].push_back(b);
      adjs[b].push_back(a);
    }
  }
  return 0;
}