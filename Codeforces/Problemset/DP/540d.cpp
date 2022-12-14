#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I R=100;
const I S=100;
const I P=100;
Lf dp[R+1][S+1][P+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I r,s,p;cin>>r>>s>>p;
  dp[r][s][p]=1;
  for(I i=r;i>=0;i--)for(I j=s;j>=0;j--)for(I k=p;k>=0;k--){
    Lf a=i*j,b=i*k,c=j*k,d=dp[i][j][k]/(a+b+c);
    a*=d,b*=d,c*=d;
    if(i>0&&j>0)dp[i][j-1][k]+=a;
    if(i>0&&k>0)dp[i-1][j][k]+=b;
    if(j>0&&k>0)dp[i][j][k-1]+=c;
  }
  Lf a=0,b=0,c=0;
  for(I i=1;i<=r;i++)a+=dp[i][0][0];
  for(I i=1;i<=s;i++)b+=dp[0][i][0];
  for(I i=1;i<=p;i++)c+=dp[0][0][i];
  printf("%.12Lf %.12Lf %.12Lf\n",a,b,c);
}