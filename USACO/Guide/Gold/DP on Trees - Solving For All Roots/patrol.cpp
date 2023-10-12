#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100000;
vector<I>adjs[N];
I dp1[N],dp2[N][4+1],dp3[N],dp4[N];
multiset<I>rems;
I res=0;
void dfs1(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a);
    dp1[a]=max(dp1[a],dp1[b]+1);
  }
}
void dfs2(I a,I p=-1){
  rems.clear();
  for(auto b:adjs[a])if(b!=p)rems.insert(dp1[b]+1);
  for(auto b:adjs[a])if(b!=p){
    rems.erase(rems.find(dp1[b]+1));
    I sum=0;
    if(rems.size()>=1)sum+=*rems.rbegin();
    dp4[b]=max(dp4[a],sum)+1;
    rems.insert(dp1[b]+1);
  }
  I pre=dp4[a];
  for(auto b:adjs[a])if(b!=p){
    dfs2(b,a);
    dp1[a]=max(dp1[a],dp1[b]+1);
    res=max(res,dp1[b]+1+pre-1);
    pre=max(pre,dp1[b]+1);
  }
}
void dfs3(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    dfs3(b,a);
    dp1[a]=max(dp1[a],dp1[b]+1);
    res=max(res,dp3[a]+dp3[b]-2);
    dp3[a]=max(dp3[a],dp3[b]);
    for(I i=4;i>=1;i--)dp2[a][i]=max(dp2[a][i],dp2[a][i-1]+dp1[b]+1);
  }
  dp3[a]=max(dp3[a],dp2[a][2]);
}
void dfs4(I a,I p=-1){
  rems.clear();
  for(auto b:adjs[a])if(b!=p)rems.insert(dp1[b]+1);
  for(auto b:adjs[a])if(b!=p){
    rems.erase(rems.find(dp1[b]+1));
    I sum=0;
    if(rems.size()>=1)sum+=*rems.rbegin();
    dp4[b]=max(dp4[a],sum)+1;
    rems.insert(dp1[b]+1);
  }
  rems.insert(dp4[a]);
  for(auto b:adjs[a])if(b!=p){
    rems.erase(rems.find(dp1[b]+1));
    I sum=dp3[b];
    if(rems.size()>=1)sum+=*rems.rbegin();
    if(rems.size()>=2)sum+=*next(rems.rbegin());
    res=max(res,sum-2);
    rems.insert(dp1[b]+1);
  }
  res=max(res,max(dp2[a][4],dp2[a][3]+dp4[a])-2);
  for(auto b:adjs[a])if(b!=p)dfs4(b,a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  if(k==1)dfs1(0),dfs2(0);
  if(k==2)dfs3(0),dfs4(0);
  printf("%i\n",2*(n-1)-res);
}