#include<bits/stdc++.h>

using namespace std;

using I=int;

const I V=100;
const I T=100;
const I D=10;
const I MIN=-1e9;

I dp[T][V+T*D+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I v1,v2;cin>>v1>>v2;
  I t,d;cin>>t>>d;
  fill(&dp[0][0],&dp[0][0]+T*(V+T*D+1),MIN);
  dp[0][v1]=0;
  for(I i=0;i+1<t;i++)for(I j=0;j<=v1+i*d;j++)for(I k=-d;k<=d;k++)
    if(j+k>=0&&j+k<=v1+(i+1)*d)dp[i+1][j+k]=max(dp[i+1][j+k],dp[i][j]+j);
  printf("%i\n",dp[t-1][v2]+v2);
}