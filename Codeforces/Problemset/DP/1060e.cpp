#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
vector<I>adjs[N];
I cols[N];
Lli dp1[N][2],dp2[N][2],dp3[N][2];
void dfs1(I a,I col,I p=-1){
  cols[a]=col;
  for(auto b:adjs[a])if(b!=p)dfs1(b,!col,a);
}
void dfs2(I a,I p=-1){
  I x=cols[a],y=!x;
  dp1[a][x]=1;
  for(auto b:adjs[a])if(b!=p){
    dfs2(b,a);
    dp1[a][0]+=dp1[b][0];
    dp1[a][1]+=dp1[b][1];
    dp2[a][x]+=dp2[b][x]+dp1[b][x];
    dp2[a][y]+=dp2[b][y];
  }
}
void dfs3(I a,I p=-1){
  I x=cols[a],y=!x;
  for(auto b:adjs[a])if(b!=p){
    dp3[b][y]+=dp3[a][y]+dp2[a][y]-dp2[b][y]+dp1[0][y]-dp1[b][y];
    dp3[b][x]+=dp3[a][x]+dp2[a][x]-dp2[b][x]-dp1[b][x];
    dfs3(b,a);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs1(0,0),dfs2(0),dfs3(0);
  Lli res=0;
  for(I i=0;i<n;i++){
    I x=cols[i],y=!x;
    res+=dp2[i][x]+dp3[i][x];
    res+=dp2[i][y]+dp3[i][y]+dp1[0][y];
  }
  printf("%lli\n",res/2);
}