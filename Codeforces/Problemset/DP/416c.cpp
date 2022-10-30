#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1000;
const I K=1000;
const I MIN=-1e9;

pair<I,I>reqs[N];
I r_arr[K];
I inds1[N],inds2[K];
I dp[N+1][K+1];
I pars[N+1][K+1];
vector<pair<I,I>>ress;

B cmp1(I a,I b){
  return reqs[a]<reqs[b];
}

B cmp2(I a,I b){
  return r_arr[a]<r_arr[b];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(K+1),MIN);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I c,p;cin>>c>>p;
    reqs[i]={c,p};
  }
  I k;cin>>k;
  for(I i=0;i<k;i++)cin>>r_arr[i];
  iota(inds1,inds1+n,0);
  sort(inds1,inds1+n,cmp1);
  iota(inds2,inds2+k,0);
  sort(inds2,inds2+k,cmp2);
  dp[0][0]=0;
  for(I i=0;i<=n;i++)for(I j=0;j<=k;j++){
    if(i+1<=n&&dp[i][j]>dp[i+1][j])dp[i+1][j]=dp[i][j],pars[i+1][j]=0;
    if(j+1<=k&&dp[i][j]>dp[i][j+1])dp[i][j+1]=dp[i][j],pars[i][j+1]=1;
    if(i+1<=n&&j+1<=k){
      auto[c,p]=reqs[inds1[i]];
      if(c>r_arr[inds2[j]])continue;
      if(dp[i][j]+p<=dp[i+1][j+1])continue;
      dp[i+1][j+1]=dp[i][j]+p,pars[i+1][j+1]=2;
    }
  }
  I i=n,j=k;
  while(!(i==0&&j==0)){
    I p=pars[i][j];
    if(p==0)i--;
    if(p==1)j--;
    if(p==2)ress.push_back({inds1[i-1],inds2[j-1]}),i--,j--;
  }
  printf("%i %i\n",ress.size(),dp[n][k]);
  for(auto[i,j]:ress)printf("%i %i\n",i+1,j+1);
}