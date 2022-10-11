#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;
const Lli MAX=1e18;

I h_arr[N];
pair<I,Lli>dp[N][2];

void cmb(pair<I,Lli>&a,pair<I,Lli>b){
  if(a.first>b.first)return;
  if(a.first<b.first){a=b;return;}
  a.second=min(a.second,b.second);
}

pair<I,Lli>add(pair<I,Lli>a,Lli val){
  return{a.first+1,a.second+val};
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)for(I j=0;j<2;j++)dp[i][j]={0,MAX};
    for(I i=0;i<n;i++)cin>>h_arr[i];
    dp[0][0]={0,0};
    for(I i=0;i<n;i++){
      if(i-1>=0)cmb(dp[i][0],dp[i-1][0]);
      if(i-1>=0)cmb(dp[i][0],dp[i-1][1]);
      if(i-1>=0&&i+1<n)cmb(dp[i][1],add(dp[i-1][0],max(max(h_arr[i-1],h_arr[i+1])+1-h_arr[i],0)));
    }
    printf("%lli\n",dp[n-1][0].second);
  }
}