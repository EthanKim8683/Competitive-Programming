#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100000;
const I MAX=1e9;

pair<I,I>beas[N];
I dp[N][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*2,MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I a,b;cin>>a>>b;
    beas[i]={-a,b};
  }
  sort(beas,beas+n);
  dp[0][1]=0;
  for(I i=0;i+1<n;i++){
    auto[a,b]=beas[i];
    dp[i][0]=min(dp[i][0],i+1);
    I j=upper_bound(beas,beas+n,pair<I,I>{a+b,MAX})-beas;
    dp[i+1][1]=min(dp[i+1][1],dp[i][0]);
    dp[j-1][0]=min(dp[j-1][0],dp[i][1]+j-i-1);
    dp[j][1]=min(dp[j][1],dp[i][1]+j-i-1);
  }
  printf("%i\n",min(dp[n-1][1],dp[n-1][0]));
}