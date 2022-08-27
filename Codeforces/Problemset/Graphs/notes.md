# Practice Problem Notes

## [1511D](https://codeforces.com/problemset/problem/1511/D) - Min Cost String

### Problem:

Find a string that contains each pair of letters only once.

<h3 id="Eulerian Paths">Solution: Eulerian Paths</h3>

```cpp
#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

vector<I>adjs[N];
vector<I>euls;
I n;

// Eulerian cycle happens here!
void dfs(I a){
  // While there are edges, traverse them
  while(adjs[a].size()){
    // Once you use an edge, delete it so
    // you can't visit it again
    I b=adjs[a].back();adjs[a].pop_back();
    dfs(b);
  }
  // Add the current node to the path
  euls.push_back(a);
}

// Check if Eulerian cycle exists:
// Every vertex has to have an even number
// of edges touching it, one entering and
// one leaving.
B chk(){
  for(I i=0;i<n;i++)
    if(adjs[i].size()%2)return false;
  return true;
}

// I/O
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  if(!chk()){printf("Eulerian cycle does not exist.\n");return 0;}
  dfs(0);
  for(auto i:euls)printf("%i ",i+1);
  return 0;
}
```

Treat each pair of letters as an edge and find the Eulerian cycle.

<br>