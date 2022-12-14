#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
using Lli=long long int;
using B=bool;
const I N=8;
Lli dp[N][10][25];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  if(n==1){
    C d=s[0];
    if(d=='X')printf("1\n");
    if(d=='_')printf("1\n");
    if(d>='0'&&d<='9')printf("%i\n",d=='0');
    exit(0);
  }
  B und=0;
  C d=s[0];
  if(d=='X')for(I i=0;i<10;i++)if(i!=0)dp[0][i][i]=1,und=1;
  if(d=='_')for(I i=0;i<10;i++)for(I j=0;j<10;j++)if(j!=0)dp[0][i][j]=1;
  if(d>='0'&&d<='9')for(I i=0;i<10;i++)if(d!='0')dp[0][i][d-'0']=1;
  for(I i=0;i+1<n;i++)for(I j=0;j<10;j++)for(I k=0;k<25;k++){
    C d=s[i+1];
    if(d=='X')dp[i+1][j][(k*10+j)%25]+=dp[i][j][k];
    if(d=='_')for(I l=0;l<10;l++)dp[i+1][j][(k*10+l)%25]+=dp[i][j][k];
    if(d>='0'&&d<='9')dp[i+1][j][(k*10+d-'0')%25]+=dp[i][j][k];
    und|=d=='X';
  }
  Lli res=0;
  for(I i=0;i<10;i++)res+=dp[n-1][i][0];
  if(!und)res/=10;
  printf("%lli\n",res);
}