#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=50;
const I K=50;
const I LOGA=60;
Lli a_arr[N];
B dp[N+1][K+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli res=0;
  for(I i=LOGA-1;i>=0;i--){
    Lli msk=res|1ll<<i;
    fill(&dp[0][0],&dp[0][0]+(N+1)*(K+1),0);
    dp[0][0]=1;
    for(I j=0;j<n;j++){
      Lli sum=0;
      for(I l=j;l<n;l++){
        sum+=a_arr[l];
        for(I o=0;o<k;o++)dp[l+1][o+1]|=dp[j][o]&&(sum&msk)==msk;
      }
    }
    res|=(Lli)dp[n][k]<<i;
  }
  printf("%lli\n",res);
}