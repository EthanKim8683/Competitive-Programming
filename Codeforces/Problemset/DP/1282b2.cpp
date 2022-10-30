#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

I a_arr[N];
Lli ps[N+1];
pair<I,Lli>dp[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,p,k;cin>>n>>p>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    for(I i=0;i<n;i++)ps[i+1]=a_arr[i];
    for(I i=0;i<n;i++)ps[i+1]+=ps[i];
    for(I i=0;i<k;i++)dp[i]={i,ps[i]};
    I res=0;
    for(I i=0;i<=n;i++){
      auto[cnt,cst]=dp[i];
      if(cst<=p)res=max(res,cnt);
      if(i+k<=n)dp[i+k]={cnt+k,cst+a_arr[i+k-1]};
      else if(cst+ps[n]-ps[i]<=p)res=max(res,cnt+n-i);
    }
    printf("%i\n",res);
  }
}