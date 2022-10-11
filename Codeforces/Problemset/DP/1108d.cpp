#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;

const I N=2e5;
const I MAX=1e9;

I dp[N][3];
I pars[N][3];
I ress[N];

I tod(C c){
  if(c=='R')return 0;
  if(c=='G')return 1;
  if(c=='B')return 2;
  return -1;
}

C toc(I i){
  if(i==0)return 'R';
  if(i==1)return 'G';
  if(i==2)return 'B';
  return -1;
}

void add(I i,I j,I k,I c){
  if(j==k)return;
  I d=dp[i][j]+(k!=c);
  if(d>=dp[i+1][k])return;
  dp[i+1][k]=d,pars[i+1][k]=j;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*3,MAX);
  I n;cin>>n;
  S s;cin>>s;
  for(I i=0;i<3;i++)dp[0][i]=tod(s[0])!=i;
  for(I i=0;i+1<n;i++)for(I j=0;j<3;j++)for(I k=0;k<3;k++)add(i,j,k,tod(s[i+1]));
  I res=MAX,j=-1;
  for(I i=0;i<3;i++)if(dp[n-1][i]<res)res=dp[n-1][i],j=i;
  for(I i=n-1;i>=0;i--)ress[i]=j,j=pars[i][j];
  printf("%i\n",res);
  for(I i=0;i<n;i++)printf("%c",toc(ress[i]));
}