#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using C=char;
const I N=500;
const Lli MOD=998244353;
pair<C,I>upds[N];
vector<I>cpss;
Lli dp[N][N+1];
Lli cnts1[N][N+1],cnts2[N][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    C t;cin>>t;
    if(t=='+'){
      I x;cin>>x;
      upds[i]={t,x};
      cpss.push_back(x);
    }
    if(t=='-')upds[i]={t,-1};
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<cpss.size();i++)dp[i][0]=1;
  for(I i=0;i<n;i++){
    auto[t,x]=upds[i];
    if(t=='+'){
      x=lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
      for(I j=0;j<=n;j++)cnts1[i][j]=dp[x][j];
      for(I j=0;j<cpss.size();j++)for(I k=n;k>=0;k--)(dp[j][min(k+(x<=j),n)]+=dp[j][k])%=MOD;
    }
    if(t=='-')for(I j=0;j<cpss.size();j++)for(I k=0;k<=n;k++)(dp[j][max(k-1,0)]+=dp[j][k])%=MOD;
  }
  fill(&dp[0][0],&dp[0][0]+N*(N+1),0);
  for(I i=0;i<cpss.size();i++)dp[i][0]=1;
  for(I i=n-1;i>=0;i--){
    auto[t,x]=upds[i];
    if(t=='+'){
      x=lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
      for(I j=0;j<=n;j++)cnts2[i][j]=dp[x][j];
      for(I j=0;j<cpss.size();j++)for(I k=0;k<=n;k++)(dp[j][max(k-(x<j),0)]+=dp[j][k])%=MOD;
    }
    if(t=='-')for(I j=0;j<cpss.size();j++)for(I k=n;k>=0;k--)(dp[j][min(k+1,n)]+=dp[j][k])%=MOD;
  }
  Lli res=0;
  for(I i=0;i<n;i++){
    auto[t,x]=upds[i];
    if(t=='+')for(I j=0;j<=n;j++)for(I k=0;k<=n;k++)if(j-k>=0)(res+=x*cnts1[i][j]%MOD*cnts2[i][k])%=MOD;
  }
  printf("%lli\n",(res+MOD)%MOD);
}