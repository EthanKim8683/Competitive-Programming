#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I T=200;

B dp[T+1][T+1][T+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I a1,a2;cin>>a1>>a2;
  dp[0][a1][a2]=1;
  for(I i=0;i<T;i++){
    for(I j=0;j<=T;j++){
      for(I k=0;k<=T;k++){
        if(j+1<=T&&k-2>=0)dp[i+1][j+1][k-2]|=dp[i][j][k];
        if(j-2>=0&&k+1<=T)dp[i+1][j-2][k+1]|=dp[i][j][k];
      }
    }
  }
  I res=0;
  for(I i=0;i<=T;i++){
    for(I j=0;j<=T;j++){
      for(I k=0;k<=T;k++){
        if(dp[i][j][k])res=max(res,i-1);
      }
    }
  }
  printf("%i\n",res);
}