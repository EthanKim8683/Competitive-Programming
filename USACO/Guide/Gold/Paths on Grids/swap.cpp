#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I X=30;
const I Y=30;
const I Z=30;
const I N=30;
Lli dp[X+1][Y+1][Z+1][N*(N-1)+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I k;cin>>k;
  I n=s.size();
  I x1=0,y1=0,z1=0;
  for(auto c:s)x1+=c=='K',y1+=c=='E',z1+=c=='Y';
  dp[0][0][0][0]=1;
  for(I i=0;i<=x1;i++)for(I j=0;j<=y1;j++)for(I k=0;k<=z1;k++)for(I l=0;l<=n*(n-1);l++){
    I x2=0,y2=0,z2=0;
    for(I m=0;m<n;m++){
      if(s[m]=='K'){
        if(x2==i){
          I o=l+max(m-(min(x2,i)+min(y2,j)+min(z2,k)),0);
          if(i+1<=x1&&o<=n*(n-1))dp[i+1][j][k][o]+=dp[i][j][k][l];
        }
        x2++;
      }
      if(s[m]=='E'){
        if(y2==j){
          I o=l+max(m-(min(x2,i)+min(y2,j)+min(z2,k)),0);
          if(j+1<=y1&&o<=n*(n-1))dp[i][j+1][k][o]+=dp[i][j][k][l];
        }
        y2++;
      }
      if(s[m]=='Y'){
        if(z2==k){
          I o=l+max(m-(min(x2,i)+min(y2,j)+min(z2,k)),0);
          if(k+1<=z1&&o<=n*(n-1))dp[i][j][k+1][o]+=dp[i][j][k][l];
        }
        z2++;
      }
    }
  }
  Lli res=0;
  for(I i=0;i<=min(k,n*(n-1));i++)res+=dp[x1][y1][z1][i];
  printf("%lli\n",res);
}