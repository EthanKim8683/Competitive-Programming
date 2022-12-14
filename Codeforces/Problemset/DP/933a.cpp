#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2000;
const I MIN=-1e9;
I a_arr[N];
I dp[N][N][2][2][2];
void cmb(I&a,I b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0][0][0],&dp[0][0][0][0][0]+N*N*2*2*2,MIN);
  I n;cin>>n;
  for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
  for(I i=0;i<n;i++)for(I j=0;j<2;j++){
    I a=a_arr[i];
    dp[i][i][j][j][0]=dp[i][i][j][j][1]=j==a;
  }
  for(I i=1;i<n;i++)for(I j=0;j+i<n;j++)for(I x=0;x<2;x++)for(I y=0;y<2;y++){
    for(I z=0;z<2;z++)for(I w=0;w<2;w++){
      if(z>x||w<y||z>w)continue;
      I a=a_arr[j],b=a_arr[j+i];
      cmb(dp[j][j+i][z][w][0],dp[j+1][j+i][x][y][0]+(w==a));
      cmb(dp[j][j+i][z][w][0],dp[j][j+i-1][x][y][0]+(z==b));
      cmb(dp[j][j+i][z][w][1],dp[j+1][j+i][x][y][0]+(z==a));
      cmb(dp[j][j+i][z][w][1],dp[j][j+i-1][x][y][0]+(w==b));
      cmb(dp[j][j+i][z][w][1],dp[j+1][j+i][x][y][1]+(z==a));
      cmb(dp[j][j+i][z][w][1],dp[j][j+i-1][x][y][1]+(w==b));
    }
  }
  I res=0;
  for(I x=0;x<2;x++)for(I y=0;y<2;y++){
    if(x>y)continue;
    cmb(res,max(dp[0][n-1][x][y][0],dp[0][n-1][x][y][1]));
  }
  printf("%i\n",res);
}