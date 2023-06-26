#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I M1=N;
const I M2=N;
const I MIN=-1e9;
vector<I>adjs[N];
I a_arr[M1];
I b_arr[M2];
B uses1[N],uses2[N];
I d;
I dfs3(I a,I p=-1){
  I dis=uses2[a]?0:MIN;
  for(auto b:adjs[a])if(b!=p)dis=max(dis,dfs3(b,a)+1);
  if(dis>=d)uses1[a]=1;
  return dis;
}
I dfs4(I a,I p=-1){
  I dis=uses1[a]?0:MIN;
  for(auto b:adjs[a])if(b!=p)dis=max(dis,dfs4(b,a)+1);
  if(dis>=d)uses2[a]=1;
  return dis;
}
B dfs1(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p)uses1[a]|=dfs1(b,a);
  return uses1[a];
}
B dfs2(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p)uses2[a]|=dfs2(b,a);
  return uses2[a];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>d;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  I m1;cin>>m1;
  for(I i=0;i<m1;i++){
    I a;cin>>a,a--;
    uses1[a]=1;
  }
  I m2;cin>>m2;
  for(I i=0;i<m2;i++){
    I b;cin>>b,b--;
    uses2[b]=1;
  }
  dfs3(0),dfs4(0),dfs1(0),dfs2(0);
  I res=0;
  res+=accumulate(uses1,uses1+n,0)-1;
  res+=accumulate(uses2,uses2+n,0)-1;
  printf("%i\n",2*res);
}