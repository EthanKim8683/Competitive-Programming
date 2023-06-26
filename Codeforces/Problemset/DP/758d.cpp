#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
using B=bool;
const I L=60;
const Lli MAX=1e18;
Lli dp[L+1][L+1];
Lli pows[L+1];
Lli facs[L+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(L+1)*(L+1),MAX);
  pows[0]=1;
  for(I i=1;i<=L;i++)pows[i]=min(min(pows[i-1],(MAX+9)/10)*10,MAX);
  I n;cin>>n;
  S k;cin>>k;
  facs[0]=1;
  for(I i=1;i<=L;i++)facs[i]=min(min(facs[i-1],(MAX+n-1)/n)*n,MAX);
  I l=k.size();
  dp[l][0]=0;
  for(I i=l;i>0;i--)for(I j=0;j<=l;j++)if(dp[i][j]<MAX){
    I o=1;Lli cur=k[i-1]-'0';B lea=0;
    while(i-o>=0&&cur<n&&cur<(MAX+facs[j]-1)/facs[j]){
      if(j+1<=l&&!lea)dp[i-o][j+1]=min(dp[i-o][j+1],dp[i][j]+cur*facs[j]);
      if(pows[o]>=n)break;
      cur+=(k[i-1-o]-'0')*pows[o],lea=k[i-1-o]=='0',o++;
    }
  }
  Lli res=MAX;
  for(I i=0;i<=l;i++)res=min(res,dp[0][i]);
  printf("%lli\n",res);
}