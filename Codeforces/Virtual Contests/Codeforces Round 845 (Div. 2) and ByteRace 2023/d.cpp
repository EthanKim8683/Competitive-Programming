#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=1e9+7;
vector<I>adjs[N];
vector<I>lays[N];
Lli sums[N];
Lli pows[N+1];
I sizs[N];
I n;
Lli dfs(I a,I p=-1){
  Lli res=0;
  lays[a].clear();
  sizs[a]=1,sums[a]=0;
  for(auto b:adjs[a])if(b!=p){
    (res+=dfs(b,a))%=MOD;
    sizs[a]+=sizs[b];
    if(lays[b].size()>lays[a].size())swap(lays[a],lays[b]),swap(sums[a],sums[b]);
    for(I i=0;i<lays[b].size();i++){
      I j=i+lays[a].size()-lays[b].size();
      (sums[a]-=pows[lays[a][j]-1]*pows[n-lays[a][j]])%=MOD;
      (lays[a][j]+=lays[b][i])%=MOD;
      (sums[a]+=pows[lays[a][j]-1]*pows[n-lays[a][j]])%=MOD;
    }
    lays[b].clear();
  }
  lays[a].push_back(1);
  (sums[a]+=pows[lays[a].back()-1]*pows[n-lays[a].back()])%=MOD;
  return(res+sums[a])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=N;i++)pows[i]=pows[i-1]*2%MOD;
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n-1;i++){
      I u,v;cin>>u>>v,u--,v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    Lli res=dfs(0);
    printf("%lli\n",(res+MOD)%MOD);
  }
}