#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=3e5;

I w_arr[N];
vector<pair<I,I>>adjs[N];
Lli dp1[N],dp2[N];
Lli res=0;

void dfs(I a,I p=-1){
  dp1[a]=max(dp1[a],(Lli)0);
  dp2[a]=max(dp2[a],(Lli)0);
  res=max(res,(Lli)w_arr[a]);
  for(auto[b,c]:adjs[a])if(b!=p){
    dp1[b]=max(dp1[b],w_arr[a]+dp1[a]-c);
    dfs(b,a);
    res=max(res,max(dp1[a],dp2[a])+w_arr[b]+dp2[b]-c+w_arr[a]);
    dp2[a]=max(dp2[a],w_arr[b]+dp2[b]-c);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>w_arr[i];
  for(I i=0;i<n-1;i++){
    I u,v,c;cin>>u>>v>>c,u--,v--;
    adjs[u].push_back({v,c});
    adjs[v].push_back({u,c});
  }
  dfs(0);
  printf("%lli\n",res);
}