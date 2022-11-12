#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;

Lli ps[N+1];
Lli dp[N+1];

Lli cnt(Lli i,Lli j){
  return i/j-i/(j+1);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli m;cin>>n>>m;
  dp[n]=1;
  for(I i=n;i>1;i--){
    (ps[i-1]+=ps[i]+dp[i])%=m;
    (dp[i-1]+=ps[i]+dp[i])%=m;
    (dp[1]+=dp[i]*cnt(i,1))%=m;
    for(I j=2;j*j<=i;j++){
      (dp[i/j]+=dp[i]*cnt(i,i/j))%=m;
      if(j!=i/j)(dp[j]+=dp[i]*cnt(i,j))%=m;
    }
  }
  printf("%lli\n",dp[1]);
}