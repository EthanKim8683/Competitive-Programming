#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I L=17;
const I N=150;
const I K=9;
const Lli MAX=1e18;
Lli pows[L+1];
Lli dp[L+1][N+1][K+1];
Lli ress[N+1][K+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(L+1)*(N+1)*(K+1),MAX);
  fill(&ress[0][0],&ress[0][0]+(N+1)*(K+1),MAX);
  pows[0]=1;
  for(I i=1;i<=L;i++)pows[i]=pows[i-1]*10;
  for(I i=0;i<=K;i++)for(I j=0;j<=9;j++){
    Lli cur=j,sum=0;
    for(I k=0;k<=i;k++)for(Lli l=cur+k;l;l/=10)sum+=l%10;
    if(sum<=N&&cur+i<10)dp[1][sum][i]=min(dp[1][sum][i],cur);
  }
  for(I i=2;i<=L;i++)for(I j=0;j<=K;j++)for(I k=0;k<=8;k++)for(I l=0;l<=9;l++){
    Lli cur=pows[i-1]*k+pows[i-1]-10+l,sum=0;
    for(I m=0;m<=j;m++)for(Lli n=cur+m;n;n/=10)sum+=n%10;
    if(sum<=N)dp[i][sum][j]=min(dp[i][sum][j],cur);
  }
  for(I i=1;i<L;i++)for(I j=0;j<=N;j++)for(I k=0;k<=K;k++)for(I l=0;l<=9;l++){
    Lli cur=dp[i][j][k]+l*pows[i],sum=j+l*(k+1);
    if(sum<=N)dp[i+1][sum][k]=min(dp[i+1][sum][k],cur);
  }
  for(I i=1;i<=L;i++)for(I j=0;j<=K;j++){
    Lli cur=pows[i]-1,sum=0;
    for(I l=0;l<=j;l++)for(Lli m=cur+l;m;m/=10)sum+=m%10;
    if(sum<=N)dp[i][sum][j]=min(dp[i][sum][j],cur);
  }
  for(I i=0;i<=L;i++)for(I j=0;j<=N;j++)for(I k=0;k<=K;k++)ress[j][k]=min(ress[j][k],dp[i][j][k]);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    printf("%lli\n",ress[n][k]==MAX?-1:ress[n][k]);
  }
}