#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100;
const I B=100;
const I MIN=-1e9;

I a_arr[N];
I dp[N][B+1][N+N+1];

void cmb(I&a,I b){
  a=max(a,b);
}

I cst(I i){
  return i%2?-1:1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*(N+N+1),MIN);
  I n,b;cin>>n>>b;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp[0][0][N+cst(a_arr[0])]=0;
  for(I i=0;i+1<n;i++){
    I x=a_arr[i],y=a_arr[i+1];
    for(I j=0;j<=b;j++){
      for(I k=N-n;k<=N+n;k++)
        if(k+cst(y)>=N-N&&k+cst(y)<=N+N)
          cmb(dp[i+1][j][k+cst(y)],dp[i][j][k]);
      if(j+abs(x-y)<=b)
        cmb(dp[i+1][j+abs(x-y)][N+cst(y)],dp[i][j][N]+1);
    }
  }
  I res=MIN;
  for(I i=0;i<=b;i++)res=max(res,dp[n-1][i][N]);
  printf("%i\n",res);
}