#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100000;
const I MAX=1e9;

I a_arr[N];
I dp[N][2];

I gcd(I a,I b){
  return b?gcd(b,a%b):a;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*2,MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I cur=0;
  for(I i=0;i<n;i++)cur=gcd(cur,a_arr[i]);
  if(cur>1)printf("YES\n0\n"),exit(0);
  dp[0][a_arr[0]%2]=0;
  for(I i=1;i<n;i++){
    if(a_arr[i]%2){
      dp[i][0]=min(dp[i][0],dp[i-1][0]+2);
      dp[i][0]=min(dp[i][0],dp[i-1][1]+1);
      dp[i][1]=min(dp[i][1],dp[i-1][0]+0);
    }else{
      dp[i][0]=min(dp[i][0],dp[i-1][0]+0);
      dp[i][0]=min(dp[i][0],dp[i-1][1]+2);
    }
  }
  printf("YES\n");
  printf("%i\n",dp[n-1][0]);
}