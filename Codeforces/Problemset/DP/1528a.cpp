#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;

vector<I>adjs[N];
I a_arr[N][2];
Lli dp[N][2];

void dfs(I a,I p=-1){
  dp[a][0]=dp[a][1]=0;
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    Lli low=0,upp=0;
    low=max(low,abs(a_arr[b][0]-a_arr[a][0])+dp[b][0]);
    low=max(low,abs(a_arr[b][1]-a_arr[a][0])+dp[b][1]);
    upp=max(upp,abs(a_arr[b][0]-a_arr[a][1])+dp[b][0]);
    upp=max(upp,abs(a_arr[b][1]-a_arr[a][1])+dp[b][1]);
    dp[a][0]+=low;
    dp[a][1]+=upp;
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n;i++){
      I l,r;cin>>l>>r;
      a_arr[i][0]=l;
      a_arr[i][1]=r;
    }
    for(I i=0;i<n-1;i++){
      I u,v;cin>>u>>v,u--,v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    dfs(0);
    printf("%lli\n",max(dp[0][0],dp[0][1]));
  }
}