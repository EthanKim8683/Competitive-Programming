#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6;
Lli dp[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli m;cin>>n>>m;
  dp[2]=1;
  for(I i=3;i<=n;i++)dp[i]=((Lli)(i-1)*dp[i-1]+(Lli)(i-1)*dp[i-2])%m;
  for(I i=1;i<=n;i++)printf("%lli ",dp[i]);
}