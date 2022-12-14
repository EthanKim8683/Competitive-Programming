#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=200;
const I L=200;
const I K=200;
I p_arr[N];
I a_arr[N];
Lf dp[N+1][N+1][N+N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,l,k;cin>>n>>l>>k;
  for(I i=0;i<n;i++)cin>>p_arr[i];
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[0][0][min(k,n)+N]=1;
  for(I i=0;i<n;i++)for(I j=0;j<=n;j++)for(I o=-n;o<=n;o++){
    if(!dp[i][j][o+N])continue;
    Lf p=p_arr[i]/100.0;
    I a=a_arr[i];
    if(a==-1){
      if(j+1<=n)dp[i+1][j+1][o-1+N]+=p*dp[i][j][o+N];
      dp[i+1][j][o+N]+=(1-p)*dp[i][j][o+N];
    }else{
      if(j+1<=n)dp[i+1][j+1][min(o+a,n)+N]+=p*dp[i][j][o+N];
      dp[i+1][j][o+N]+=(1-p)*dp[i][j][o+N];
    }
  }
  Lf res=0;
  for(I i=l;i<=n;i++)for(I j=0;j<=n;j++)res+=dp[n][i][j+N];
  printf("%.12Lf\n",res);
}