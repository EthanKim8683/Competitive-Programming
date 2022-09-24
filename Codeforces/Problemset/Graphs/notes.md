# Practice Problem Notes

## [1511D](https://codeforces.com/problemset/problem/1511/D) - Min Cost String

### Problem:

Find a string that contains each pair of letters only once.

<h3 id="Euler Cycles for Directed Graphs">Solution: Euler Cycles for Directed Graphs</h3>

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
I inds[N],outs[N];
I n;

// Euler cycle for directed graphs happens
// here!
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

// Check if Euler cycle exists:
// Every vertex has to have the same number
// of edges going in as coming out
B chk(){
  for(I i=0;i<n;i++)if(inds[i]!=outs[i])return 0;
  return 1;
}

// I/O
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    outs[a]++,inds[b]++;
  }
  if(!chk())printf("Euler cycle does not exist.\n"),exit(0);
  dfs(0);
  for(auto i:euls)printf("%i ",i+1);
}
```

Treat each pair of letters as an edge and find the Euler cycle.

<br>

## [427C](https://codeforces.com/problemset/problem/427/C) - Checkposts

### Problem:

How many maximal cycles are there?

<h3 id="Strongly Connected Components">Solution: Strongly Connected Components</h3>

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

vector<I>adjs1[N],adjs2[N];
B viss1[N],viss2[N];
vector<I>tops;
vector<I>sccs[N];
I n;

// Topological sort
void dfs1(I a){
  if(viss1[a])return;
  viss1[a]=1;
  for(auto b:adjs1[a])dfs1(b);
  tops.push_back(a);
}

// Traverse SCC: maximal size is ensured
// by the fact that all reachable nodes
// are traversed
void dfs2(I a,I r){
  if(viss2[a])return;
  viss2[a]=1;
  for(auto b:adjs2[a])dfs2(b,r);
  sccs[r].push_back(a);
}

// SCC happens here!
void scc(){
  // Run topological sort to produce a
  // head-first ordering
  for(I i=0;i<n;i++)dfs1(i);
  reverse(tops.begin(),tops.end());
  // Non-cycles' heads don't have any incoming
  // edges, so traversing with flipped edges
  // ensure only cycles are found
  for(auto i:tops)if(!viss2[i])dfs2(i,i);
}

// I/O
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs1[a].push_back(b);
    adjs2[b].push_back(a);
  }
  scc();
  for(I i=0;i<n;i++){
    if(!sccs[i].size())continue;
    for(auto j:sccs[i])printf("%i ",j+1);
    printf("\n");
  }
}
```

For minimum price, sum the minimum cost of each component. For the number of ways to produce the minimum
number of checkpoints, multiply all the sizes of the connected components.

<br>

## [1406C](https://codeforces.com/problemset/problem/1406/C) - Link Cut Centroids

### Problem:

Find the centroid of a tree.

<h3 id="Centroids">Solution: Centroids</h3>

```cpp
#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

const I N=1e5;

vector<I>adjs[N];
I sizs[N];
I n;

// Find the size of each subtree
I dfs1(I a,I p=-1){
  I siz=1;
  for(auto b:adjs[a]){
    if(b==p)continue;
    siz+=dfs1(b,a);
  }
  return sizs[a]=siz;
}

// Find the first centroid
I dfs2(I a,I p=-1){
  // Traverse all children
  for(auto b:adjs[a]){
    if(b==p)continue;
    // If the child's subtree size is greater
    // than half the entire tree, the centroid
    // must be inside it.
    if(sizs[b]*2>n)
      return dfs2(b,a);
  }
  // If no child satisfies the above, the
  // current node is the centroid.
  return a;
}

// Find the second centroid if it exists
I dfs3(I a,I p=-1){
  for(auto b:adjs[a]){
    if(b==p)continue;
    // If there are two centroids, either of
    // them would split the tree into the same
    // sizes, meaning a >= is needed to avoid
    // finding the existing centroid again.
    if(sizs[b]*2>=n)
      return dfs3(b,a);
  }
  return a;
}

// I/O
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs1(0);
  I a=dfs2(0);
  dfs1(a);
  I b=dfs3(a);
  printf("%i ",a+1);
  if(a!=b)printf("%i",b+1);
}
```

If there is only one centroid, just detach and reattach an edge. If there are two centroids, cut a leaf node from one of the centroid's subtrees and add it to the other's.

<br>

## [1062D](https://codeforces.com/problemset/problem/1062/D) - Fun with Integers

### Problem:

Find the sum of a traversal where all edges are used.

<h3 id="Euler Cycles for Undirected Graphs">Solution: Euler Cycles for Undirected Graphs</h3>

```cpp
#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I M=1e5;

vector<pair<I,I>>adjs[N];
vector<I>stks;
vector<I>euls;
B viss[M];
I n;

// Euler cycle for undirected graphs happens
// here!
void eul(I i){
  // Start at the given node
  stks.push_back(i);
  while(stks.size()){
    I a=stks.back(),b=-1;
    // While there is an edge, traverse and
    // delete it, otherwise add the current
    // node to the path and continue
    while(adjs[a].size()&&b==-1){
      auto[c,i]=adjs[a].back();adjs[a].pop_back();
      if(!viss[i])b=c,viss[i]=1;
    }
    if(b!=-1)stks.push_back(b);
    else euls.push_back(a),stks.pop_back();
  }
}

// Check if Euler cycle exists:
// Every vertex has to have an even number of
// edges, one going in and one coming out per
// pair
B chk(){
  for(I i=0;i<n;i++)if(adjs[i].size()%2)return 0;
  return 1;
}

// I/O
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back({b,i});
    adjs[b].push_back({a,i});
  }
  if(!chk())printf("Euler cycle does not exist.\n"),exit(0);
  eul(0);
  for(auto i:euls)printf("%i ",i+1);
}
```

<br>

## [949C](https://codeforces.com/problemset/problem/949/C) - Data Center Maintenence

### Problem:

Find the smallest strongly connected component that leads only into itself.

<h3 id="Sinks">Solution: Sinks</h3>

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

vector<I>adjs1[N],adjs2[N];
B viss1[N],viss2[N];
vector<I>tops;
vector<I>sccs[N];
I pars[N];
I n;

// Topological sort
void dfs1(I a){
  if(viss1[a])return;
  viss1[a]=1;
  for(auto b:adjs1[a])dfs1(b);
  tops.push_back(a);
}

// Traverse SCC
void dfs2(I a,I r){
  if(viss2[a])return;
  viss2[a]=1;
  for(auto b:adjs2[a])dfs2(b,r);
  sccs[r].push_back(a);
}

// SCC sink happens here!
void scc(){
  for(I i=0;i<n;i++)dfs1(i);
  reverse(tops.begin(),tops.end());
  for(auto i:tops)if(!viss2[i])dfs2(i,i);
  // Here, we assign each node a parent
  // representing the SCC it's part of
  for(I i=0;i<n;i++)for(auto j:sccs[i])pars[j]=i;
  // Now, we check if all members of an SCC only
  // direct towards other members of its SCC
  for(I i=0;i<n;i++)for(auto j:adjs1[i])
    if(pars[i]!=pars[j])sccs[pars[i]].clear();
}

// I/O
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs1[a].push_back(b);
    adjs2[b].push_back(a);
  }
  scc();
  for(I i=0;i<n;i++){
    if(!sccs[i].size())continue;
    for(auto j:sccs[i])printf("%i ",j+1);
    printf("\n");
  }
}
```

<br>

## [1423B](https://codeforces.com/problemset/problem/1423/B) - Valuable Paper

### Problem:

Check for perfect matchings.

<h3 id="Hopcroft-Karp Algorithm">Solution: Hopcroft-Karp Algorithm</h3>

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I MAX=1e9;

vector<I>adjs[N];
I cons1[N],cons2[N];
I diss[N+1];
queue<I>que;
I n1,n2;

// Try to add node to queue
void add(I d,I i){
  if(d>=diss[i])return;
  que.push(i),diss[i]=d;
}

// BFS for alternating paths starting and ending
// in unmatched edges. Each such path contains
// x matched and x+1 unmatched edges. Thus,
// swapping the states of every edge in the path
// provides a net gain of 1 matched edge.
B bfs(){
  fill_n(diss,n1,MAX);
  // If a node from the first subset is free,
  // then start an alternating path
  for(I i=0;i<n1;i++)if(cons1[i]==N)add(0,i);
  diss[N]=MAX;
  while(que.size()){
    I a=que.front();que.pop();
    // If a node from the second subset is free,
    // then an alternating path is satisfied
    if(a==N)return 1;
    for(auto b:adjs[a])add(diss[a]+1,cons2[b]);
  }
  return 0;
}

// Apply the swaps through DFS traversal
B dfs(I a){
  // If end of path, return true
  if(a==N)return 1;
  for(auto b:adjs[a]){
    I c=cons2[b];
    // If adjacent node is next in a valid path,
    // reassign edge
    if(diss[a]+1!=diss[c]||!dfs(c))continue;
    cons1[a]=b,cons2[b]=a;
    return 1;
  }
  // Mask current node as visited
  diss[a]=MAX;
  return 0;
}

// Hopcroft-Karp happens here!
I hpk(){
  fill_n(cons1,n1,N),fill_n(cons2,n2,N);
  I res=0;
  // While there are optimizations to be made
  // apply them
  while(bfs())for(I i=0;i<n1;i++)
    if(cons1[i]==N)res+=dfs(i);
  // Return number of matchings
  return res;
}

// I/O
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n1>>n2>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v;
    adjs[u-1].push_back(v-1);
  }
  printf("%i\n",hpk());
}
```

<br>

## [118E](https://codeforces.com/problemset/problem/118/E) - Bertown Roads

### Problem:

Checking if every component has an edge leading in and leading out (no bridges).

<h3 id="Finding Bridges">Solution: Finding Bridges</h3>

```cpp
#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

vector<I>adjs[N];
B viss[N];
I tbegs[N],tlows[N];
I t=0;
I res=0;

// Bridge finding happens here!
I dfs(I a,I p=-1){
  if(viss[a])return tlows[a];
  viss[a]=1;
  // Mark the first visit of the component as
  // sort of a "parent"
  tbegs[a]=tlows[a]=t++;
  for(auto b:adjs[a])if(b!=p){
    // Join the adjacent node to the current
    // component
    tlows[a]=min(tlows[a],dfs(b,a));
    // If the adjacent node is not connected
    // to any other components
    if(tlows[b]>tbegs[a])res++;
  }
  return tlows[a];
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
  dfs(0);
  printf("%i\n",res);
}
```