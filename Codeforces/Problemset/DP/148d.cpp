#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lf=long double;

const I W=1000;
const I B=1000;

Lf dp[W+1][B+1][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I w,b;cin>>w>>b;
  dp[w][b][0]=1;
  Lf res=0;
  for(I i=w;i>=0;i--)for(I j=b;j>=0;j--)for(I k=0;k<2;k++){
    if(k==1){
      if(i>=0&&j-1-1>=0)dp[i][j-1-1][!k]+=dp[i][j][k]*(Lf)j/(i+j)*(Lf)(j-1)/(i+j-1);
      if(i-1>=0&&j-1>=0)dp[i-1][j-1][!k]+=dp[i][j][k]*(Lf)j/(i+j)*(Lf)(i)/(i+j-1);
    }else{
      if(i-1>=0&&j>=0)res+=dp[i][j][k]*(Lf)i/(i+j);
      if(i>=0&&j-1>=0)dp[i][j-1][!k]+=dp[i][j][k]*(Lf)j/(i+j);
    }
  }
  printf("%.9Lf\n",res);
}