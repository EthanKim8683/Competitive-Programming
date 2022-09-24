#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

I e_arr[N];
vector<I>adjs[N];
vector<I>tops;
B viss[N];
I dp[N];

void dfs(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs[a])dfs(b);
  tops.push_back(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>e_arr[i];
  for(I i=0;i<m;i++){
    I t1,t2;cin>>t1>>t2;
    adjs[t1].push_back(t2);
  }
  for(I i=0;i<n;i++)dfs(i);
  reverse(tops.begin(),tops.end());
  for(auto i:tops)for(auto j:adjs[i])
    dp[j]=max(dp[j],dp[i]+(e_arr[i]&&!e_arr[j]));
  I res=0;
  for(I i=0;i<n;i++)res=max(res,dp[i]+e_arr[i]);
  printf("%i\n",res);
  return 0;
}