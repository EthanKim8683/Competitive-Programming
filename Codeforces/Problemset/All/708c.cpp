#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=400000;
vector<I>adjs[N];
I sizs[N];
I dp[N][2];
B ress[N];
multiset<I>curs;
I n;
void dfs1(I a,I p=-1){
  sizs[a]=1,ress[a]=1;
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a);
    ress[a]&=sizs[b]-n/2<=dp[b][0];
    sizs[a]+=sizs[b];
    dp[a][0]=max(dp[a][0],dp[b][0]);
  }
  if(sizs[a]<=n/2)dp[a][0]=max(dp[a][0],sizs[a]);
}
void dfs2(I a,I p=-1){
  ress[a]&=n-sizs[a]-n/2<=dp[a][1];
  curs.clear();
  for(auto b:adjs[a])if(b!=p)curs.insert(dp[b][0]);
  if(n-sizs[a]<=n/2)curs.insert(n-sizs[a]);
  curs.insert(dp[a][1]);
  for(auto b:adjs[a])if(b!=p){
    curs.erase(curs.find(dp[b][0]));
    dp[b][1]=max(dp[b][1],*curs.rbegin());
    curs.insert(dp[b][0]);
  }
  for(auto b:adjs[a])if(b!=p)dfs2(b,a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs1(0),dfs2(0);
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
}
/*
for each vertex, if a subtree with size of a child with size exceeding n / 2
can be reattached to the vertex itself such that the child and the subtree
now has size not exceeding n / 2, the vertex can be a centroid

we can use dynamic programming on trees, solving for all roots, keeping track
of the maximum value not exceeding n / 2 for each subtree

this allows us to check, for each child of each vertex, if it is possible to
detach a descendant from said child such that the child's size would not
exceed n / 2
*/