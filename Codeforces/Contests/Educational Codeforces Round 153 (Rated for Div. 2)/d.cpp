#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=100;
const I M=N/2*N/2;
const I MAX=1e9;
I dp[N+1][N+1][M+M+1];
/*
assigning 0 to a 1 counts
assigning 1 to a 0 does not
*/
void cmb(I&a,I b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*(N+1)*(M+M+1),MAX);
  S s;cin>>s;
  I n=s.size();
  dp[0][0][0+M]=0;
  for(I i=0;i<n;i++)for(I j=0;j<=i;j++)for(I k=-M;k<=M;k++){
    if(s[i]=='0'){
      if(k+i-j<=M)cmb(dp[i+1][j+1][k+i-j+M],dp[i][j][k+M]);//1 to 0
      if(k-j>=-M)cmb(dp[i+1][j][k-j+M],dp[i][j][k+M]);//0 to 0
    }
    if(s[i]=='1'){
      if(k-j>=-M)cmb(dp[i+1][j][k-j+M],dp[i][j][k+M]+1);//0 to 1
      if(k+i-j<=M)cmb(dp[i+1][j+1][k+i-j+M],dp[i][j][k+M]);//1 to 1
    }
  }
  I cnt=0;
  for(auto c:s)cnt+=c=='1';
  printf("%i\n",dp[n][cnt][0+M]);
}