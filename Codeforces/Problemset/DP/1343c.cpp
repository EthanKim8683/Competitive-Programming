#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;
const Lli MIN=-1e18;

I a_arr[N];
set<I>inds[2];
pair<I,Lli>dp[N];

void cmb(pair<I,Lli>&a,pair<I,Lli>b){
  if(b.first<a.first)return;
  if(b.first==a.first&&b.second>a.second)a=b;
  if(b.first>a.first)a=b;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    inds[0].clear(),inds[1].clear();
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)inds[a_arr[i]<0].insert(i);
    for(I i=0;i<n;i++)dp[i]={1,a_arr[i]};
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      auto it1=inds[a>0].upper_bound(i);
      if(it1!=inds[a>0].end())
        cmb(dp[*it1],{dp[i].first+1,dp[i].second+a_arr[*it1]});
      auto it2=inds[a<0].upper_bound(i);
      if(it2!=inds[a<0].end())
        cmb(dp[*it2],{dp[i].first,dp[i].second-a+a_arr[*it2]});
    }
    pair<I,Lli>res={0,MIN};
    for(I i=0;i<n;i++)cmb(res,dp[i]);
    printf("%lli\n",res.second);
  }
}