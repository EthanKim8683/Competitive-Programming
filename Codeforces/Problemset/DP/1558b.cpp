#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=4e6;
I dp[N+1+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  I pfx=0;
  dp[1]+=1,dp[1+1]-=1;
  for(I i=1;i<=n;i++){
    (dp[i+1]+=dp[i])%=m;
    (dp[i]+=pfx)%=m;
    for(I j=2;i*j<=n;j++){
      (dp[i*j]+=dp[i])%=m;
      (dp[min(i*j+j,n+1)]-=dp[i])%=m;
    }
    (pfx+=dp[i])%=m;
  }
  printf("%i\n",(dp[n]+m)%m);
}