#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=19;
const Lli MIN=-1e18;

Lli pows[N];
Lli dp[1<<N][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(1<<N)*2,MIN);
  pows[0]=1;
  for(I i=0;i+1<N;i++)pows[i+1]=pows[i]*10;
  S a;cin>>a;
  Lli b;cin>>b;
  I n=a.size();
  for(I i=0;i<n;i++)a[i]-='0';
  dp[0][1]=0;
  for(I i=0;i<(1<<n);i++){
    Lli pow=pows[n-1-__builtin_popcount(i)];
    for(I j=0;j<n;j++){
      if(i>>j&1)continue;
      Lli low=dp[i][0]+pow*a[j];
      Lli upp=dp[i][1]+pow*a[j];
      if(upp/pow<b/pow)dp[i|1<<j][0]=max(dp[i|1<<j][0],upp);
      if(upp/pow==b/pow)dp[i|1<<j][1]=max(dp[i|1<<j][1],upp);
      dp[i|1<<j][0]=max(dp[i|1<<j][0],low);
    }
  }
  printf("%lli\n",max(dp[(1<<n)-1][0],dp[(1<<n)-1][1]));
}