#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1000;
const I X=1000;

I a_arr[N];
B dp[N+1][X+1][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,x;cin>>n>>x;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<=n;i++)for(I j=0;j<=x;j++)dp[i][j][0]=dp[i][j][1]=0;
    dp[0][0][0]=1;
    for(I i=0;i<n;i++)for(I j=0;j<=x;j++)for(I k=0;k<2;k++){
      I a=a_arr[i];
      if(j+1<=x)dp[i+1][j+1][(k+a)%2]+=dp[i][j][k];
      dp[i+1][j][k]+=dp[i][j][k];
    }
    B res=0;
    for(I i=0;i<=n;i++)res|=dp[i][x][1];
    printf("%s\n",res?"Yes":"No");
  }
}