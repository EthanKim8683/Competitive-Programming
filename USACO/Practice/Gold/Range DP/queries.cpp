#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using S=string;

const I N=5000;

I dp[N][N][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I q;cin>>q;
  I n=s.size();
  for(I i=n-1;i>=0;i--){
    dp[i][i][0]=dp[i][i][1]=1;
    if(i+1<n){
      dp[i][i+1][0]=dp[i][i+1][1]=s[i]==s[i+1];
      dp[i][i+1][1]+=2;
    }
    for(I j=i+2;j<n;j++){
      if(s[i]==s[j]){
        dp[i][j][0]+=dp[i+1][j-1][0];
        dp[i][j][1]+=dp[i+1][j-1][0];
      }
      dp[i][j][1]+=dp[i][j-1][1];
      dp[i][j][1]+=dp[i+1][j][1];
      dp[i][j][1]-=dp[i+1][j-1][1];
    }
  }
  while(q--){
    I l,r;cin>>l>>r;
    printf("%i\n",dp[l-1][r-1][1]);
  }
  return 0;
}