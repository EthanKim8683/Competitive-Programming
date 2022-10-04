#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;

const I N=2e5;
const I MAX=1e9;

I dp[N][2];
I pars[N][2];

void add(I i,I j,I t){
  if(dp[i-1][j]+t>=dp[i][t])return;
  dp[i][t]=dp[i-1][j]+t,pars[i][t]=j;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*2,MAX);
  S s;cin>>s;
  I n=s.size();
  dp[0][0]=0,dp[0][1]=1;
  for(I i=1;i<n;i++){
    C a=s[i-1],b=s[i];
    if(a!=b)add(i,0,0);
    add(i,0,1);
    add(i,1,0);
  }
  I j=dp[n-1][1]<dp[n-1][0];
  S res="";
  for(I i=n-1;i>=0;i--){
    if(j==1){
      C a=i-1>=0?s[i-1]:0;
      C b=i+1<n?s[i+1]:0;
      for(C j='a';j<='z';j++){
        if(j==a||j==b)continue;
        res=j+res;
        break;
      }
    }else res=s[i]+res;
    j=pars[i][j];
  }
  printf("%s\n",res.c_str());
}