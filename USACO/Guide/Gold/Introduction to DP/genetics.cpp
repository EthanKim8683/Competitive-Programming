#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=1e5;
const Lli MOD=1e9+7;
S cpss="?ACGT";
vector<I>cpds;
Lli dp[N+1][4][4][4];
void bas(I cur){
  for(I i=0;i<4;i++)dp[1][i][cur][cur]=1;
}
void trn(I i,I cur){
  for(I j=0;j<4;j++)for(I k=0;k<4;k++)(dp[i+1][k][cur][cur]+=dp[i][j][k][j])%=MOD;
  for(I j=0;j<4;j++)if(j!=cur)for(I k=0;k<4;k++)for(I l=0;l<4;l++)(dp[i+1][k][l][cur]+=dp[i][k][l][j])%=MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  for(auto c:s)cpds.push_back(lower_bound(cpss.begin(),cpss.end(),c)-cpss.begin()-1);
  I n=s.size(),pre=cpds[0];
  if(pre==-1)for(I i=0;i<4;i++)bas(i);
  if(pre!=-1)bas(pre);
  for(I i=1;i<n;i++){
    I cur=cpds[i];
    if(cur==-1)for(I j=0;j<4;j++)trn(i,j);
    if(cur!=-1)trn(i,cur);
  }
  Lli res=0;
  for(I i=0;i<4;i++)for(I j=0;j<4;j++)(res+=dp[n][i][j][i])%=MOD;
  printf("%lli\n",res);
}