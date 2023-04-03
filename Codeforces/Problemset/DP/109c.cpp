#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e5;
vector<pair<I,B>>adjs[N];
I sizs[N];
I dp1[N],dp2[N];
Lli res=0;
void dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto[b,lck]:adjs[a])if(b!=p){
    dfs1(b,a);
    sizs[a]+=sizs[b];
    dp1[a]+=lck?sizs[b]:dp1[b];
  }
}
void dfs2(I a,I p=-1){
  for(auto[b,lck]:adjs[a])if(b!=p){
    dp2[b]=lck?sizs[0]-sizs[b]:dp2[a]+dp1[a]-dp1[b];
    dfs2(b,a);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I u,v,w;cin>>u>>v>>w,u--,v--;
    B lck=1;
    for(;w;w/=10)lck&=w%10==4||w%10==7;
    adjs[u].push_back({v,lck});
    adjs[v].push_back({u,lck});
  }
  dfs1(0),dfs2(0);
  for(I i=0;i<n;i++){
    Lli cnt=dp1[i]+dp2[i];
    res+=cnt*(cnt-1);
  }
  printf("%lli\n",res);
}