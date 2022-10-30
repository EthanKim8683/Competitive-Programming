#include<bits/stdc++.h>
 
using namespace std;
 
using I=int;
using Lli=long long int;
 
const I A=5000000;

Lli dp[A+1];
 
I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=2;i<=A;i++)if(!dp[i]){
    dp[i]=1;
    for(Lli j=1;i*j<=A;j++)if(dp[j])dp[i*j]+=dp[j]+dp[i];
  }
  for(I i=0;i<A;i++)dp[i+1]+=dp[i];
  I t;cin>>t;
  while(t--){
    I a,b;cin>>a>>b;
    printf("%lli\n",dp[a]-dp[b]);
  }
}