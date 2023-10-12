#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
using B=bool;
const I N=10;
const I M=1e4;
const Lli MOD=(1ll<<31)-1;
const Lli BAS=(1ll<<17)-1;
const I MAX=1e9;
Lli pows[M+1];
S s_arr[N];
vector<Lli>pres[N];
I adds[N][N];
I dp[1<<N][N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&adds[0][0],&adds[0][0]+N*N,MAX);
  fill(&dp[0][0],&dp[0][0]+(1<<N)*N,MAX);
  pows[0]=1;
  for(I i=1;i<=M;i++)pows[i]=pows[i-1]*BAS%MOD;
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>s_arr[i];
  for(I i=0;i<n;i++){
    pres[i].push_back(0);
    for(auto c:s_arr[i])pres[i].push_back((pres[i].back()*BAS+c)%MOD);
  }
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)if(i!=j)for(I k=0;k<=s_arr[i].size();k++){
    I l=min(s_arr[i].size(),k+s_arr[j].size());
    if(((pres[i][l]-pres[i][k]*pows[l-k])%MOD+MOD)%MOD==((pres[j][l-k]-pres[j][0]*pows[l-k])%MOD+MOD)%MOD)adds[i][j]=min(adds[i][j],(I)s_arr[j].size()-(l-k));
  }
  for(I i=0;i<n;i++)dp[1<<i][i]=s_arr[i].size();
  for(I i=0;i<(1<<n);i++)for(I j=0;j<n;j++)if(i>>j&1)for(I k=0;k<n;k++)if(~i>>k&1){
    dp[i|1<<k][k]=min(dp[i|1<<k][k],dp[i][j]+adds[j][k]);
    if(adds[j][k]==0)dp[i|1<<k][j]=min(dp[i|1<<k][j],dp[i][j]);
  }
  printf("%i\n",*min_element(dp[(1<<n)-1],dp[(1<<n)-1]+n));
}