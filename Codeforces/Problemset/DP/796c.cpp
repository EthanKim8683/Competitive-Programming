#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=3e5;
const I MAX=2e9;
const I MIN=-2e9;
I a_arr[N];
vector<I>adjs[N];
vector<I>dp4[N],dp5[N];
I dp1[N],dp2[N],dp3[N];
I res=MAX;
void dfs1(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a);
    dp2[a]=max(dp2[a],dp1[b]);
  }
  dp1[a]=max(dp2[a],a_arr[a]+2);
}
void dfs2(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    dp4[a].push_back(dp1[b]);
    dp5[a].push_back(dp1[b]);
  }
  for(I i=0;i+1<dp4[a].size();i++)dp4[a][i+1]=max(dp4[a][i+1],dp4[a][i]);
  for(I i=dp5[a].size()-1;i>0;i--)dp5[a][i-1]=max(dp5[a][i-1],dp5[a][i]);
  I i=0;
  for(auto b:adjs[a])if(b!=p){
    dp3[b]=dp3[a];
    if(p!=-1)dp3[b]=max(dp3[b],a_arr[p]+2);
    if(i-1>=0)dp3[b]=max(dp3[b],dp4[a][i-1]);
    if(i+1<dp5[a].size())dp3[b]=max(dp3[b],dp5[a][i+1]);
    dfs2(b,a),i++;
  }
}
void dfs3(I a,I p=-1){
  I cur=max(a_arr[a],dp3[a]);
  for(auto b:adjs[a]){
    if(b!=p)cur=max(cur,dp2[b]);
    cur=max(cur,a_arr[b]+1);
  }
  res=min(res,cur);
  for(auto b:adjs[a])if(b!=p)dfs3(b,a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(dp1,n,MIN);
  fill_n(dp2,n,MIN);
  fill_n(dp3,n,MIN);
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs1(0),dfs2(0),dfs3(0);
  printf("%i\n",res);
}