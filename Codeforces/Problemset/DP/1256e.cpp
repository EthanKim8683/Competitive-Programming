#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2e5;
const Lli MAX=1e18;
I a_arr[N];
pair<Lli,I>dp[N+1];
vector<I>cuts;
I inds[N];
I ress[N];
B cmp(I a,I b){
  return a_arr[a]<a_arr[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  fill_n(dp,n+1,pair<Lli,I>{MAX,-1});
  dp[3]={a_arr[inds[n-1]]-a_arr[inds[0]],-1};
  for(I i=3;i<n;i++){
    if(i+3<=n)dp[i+3]=min(dp[i+3],{dp[i].first+a_arr[inds[i-1]]-a_arr[inds[i]],i});
    dp[i+1]=min(dp[i+1],dp[i]);
  }
  auto[res,j]=dp[n];
  for(;j!=-1;j=dp[j].second)cuts.push_back(j);
  reverse(cuts.begin(),cuts.end());
  for(I i=0,j=0;i<n;i++){
    if(j<cuts.size()&&i==cuts[j])j++;
    ress[inds[i]]=j;
  }
  printf("%lli %i\n",res,cuts.size()+1);
  for(I i=0;i<n;i++)printf("%i ",ress[i]+1);
}