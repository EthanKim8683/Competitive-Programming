#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100;

I a_arr[N];
I dp[N+1][N+1][2][2];

I dfs(I a,I b,I x,I t){
  if(a==0&&b==0)return x;
  if(dp[a][b][x][t]!=-1)return dp[a][b][x][t];
  if(a-1>=0&&dfs(a-1,b,(x+(t==0))%2,!t)==t)return dp[a][b][x][t]=t;
  if(b-1>=0&&dfs(a,b-1,x,!t)==t)return dp[a][b][x][t]=t;
  return dp[a][b][x][t]=!t;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)a_arr[i]=abs(a_arr[i])%2;
    I odd=accumulate(a_arr,a_arr+n,0);
    I eve=n-odd;
    for(I i=0;i<=odd;i++)for(I j=0;j<=eve;j++)
      for(I k=0;k<2;k++)for(I l=0;l<2;l++)dp[i][j][k][l]=-1;
    printf("%s\n",dfs(odd,eve,0,0)==0?"Alice":"Bob");
  }
}