#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;

const I N=5e5;
const I K=26;
const I MAX=1e9;

I dp[N][K];
I pars[N][K];
pair<I,I>ps1[K],ps2[K];
C ress[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*K,MAX);
  I n,k;cin>>n>>k;
  S s;cin>>s;
  for(I i=0;i<k;i++)dp[0][i]=i!=s[0]-'A';
  for(I i=0;i+1<n;i++){
    for(I j=0;j<k;j++)ps1[j]=ps2[j]={dp[i][j],j};
    for(I j=0;j+1<k;j++)ps1[j+1]=min(ps1[j+1],ps1[j]);
    for(I j=k-1;j>0;j--)ps2[j-1]=min(ps2[j-1],ps2[j]);
    for(I j=0;j<k;j++){
      pair<I,I>low={MAX,-1};
      if(j-1>=0)low=min(low,ps1[j-1]);
      if(j+1<k)low=min(low,ps2[j+1]);
      auto[val,x]=low;
      val+=j!=s[i+1]-'A';
      if(val>=dp[i+1][j])continue;
      dp[i+1][j]=val,pars[i+1][j]=x;
    }
  }
  I j=min_element(dp[n-1],dp[n-1]+k)-dp[n-1];
  I res=dp[n-1][j];
  for(I i=n-1;i>=0;i--){
    ress[i]=j+'A';
    j=pars[i][j];
  }
  printf("%i\n",res);
  printf("%s\n",ress);
}