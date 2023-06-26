#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I M=2e5;
const I K=20;
const I LOGK=5;
const I MIN=-5e5;
pair<I,I>stds[N];
I dp[K+1][M+1][K+1];
I cnts[M+1][K+1];
vector<I>ress;
pair<I,I>cmb(pair<I,I>a,pair<I,I>b){
  auto[ay,ax]=a;auto[by,bx]=b;
  return(Lli)ay*bx>(Lli)by*ax?a:b;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(K+1)*(M+1)*(K+1),MIN<<LOGK);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I m,k;cin>>m>>k;
    cnts[m][k]++;
  }
  pair<I,I>res={MIN,1};
  for(I i=1;i<=K;i++){
    dp[i][0][0]=0;
    for(I j=0;j<M;j++){
      I trn=0;
      for(I k=1;k<=K;k++)trn+=cnts[j+1][k]*min(k,i);
      for(I k=0;k<=i;k++){
        if(k+1<=i)dp[i][j+1][k+1]=max(dp[i][j+1][k+1],(dp[i][j][k]&~((1<<LOGK)-1))+(trn<<LOGK)+k);
        dp[i][j+1][k]=max(dp[i][j+1][k],(dp[i][j][k]&~((1<<LOGK)-1))+k);
      }
    }
    for(I j=0;j<=i;j++)res=cmb(res,{dp[i][M][j]>>LOGK,i});
  }
  auto[num,t]=res;
  pair<I,I>sub={MIN,-1};
  for(I i=0;i<=t;i++)sub=max(sub,{dp[t][M][i]>>LOGK,i});
  I j1=sub.second;
  for(I i=M;i>0;i--){
    I j2=dp[t][i][j1]&((1<<LOGK)-1);
    if(j1!=j2)ress.push_back(i-1);
    j1=j2;
  }
  printf("%i\n",t);
  for(auto i:ress)printf("%i ",i+1);
}