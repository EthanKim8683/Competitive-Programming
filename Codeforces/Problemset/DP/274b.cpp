#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
vector<I>adjs[N];
I v_arr[N];
Lli dp[N];
void dfs(I a,I p=-1){
  dp[a]=max(-v_arr[a],0);
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    dp[a]=max(dp[a],dp[b]+max(v_arr[b]-v_arr[a],0));
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  for(I i=0;i<n;i++)cin>>v_arr[i];
  dfs(0);
  printf("%lli\n",v_arr[0]+dp[0]*2);
}