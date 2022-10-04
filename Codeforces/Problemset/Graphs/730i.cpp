#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=3000;
const I S=N;
const I MIN=-1e9;

I vals[2][N];
I inds[N];
I dp[N+1][S+1];
I pars[N+1][S+1];
priority_queue<I>rems;
priority_queue<I>wins;
vector<pair<I,I>>maxs;
vector<I>ress[2];
I sum=0;
I s;

B cmp(I a,I b){
  return vals[0][a]>vals[0][b];
}

void trn(I i,I j,I k){
  if(j+k>s)return;
  I sum=dp[i][j]+vals[k][inds[i]];
  if(sum<=dp[i+1][j+k])return;
  dp[i+1][j+k]=sum;
  pars[i+1][j+k]=k;
}

void add(I i){
  rems.push(i),i=rems.top(),rems.pop();
  wins.push(-i);
  sum+=i;
}

void rem(I i){
  while(wins.size()>i){
    I j=-wins.top();rems.push(j);
    wins.pop();
    sum-=j;
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,p;cin>>n>>p>>s;
  fill(&dp[0][0],&dp[0][0]+(N+1)*(S+1),MIN);
  for(I i=0;i<n;i++)cin>>vals[0][i];
  for(I i=0;i<n;i++)cin>>vals[1][i];
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  dp[0][0]=0;
  for(I i=0;i<p+s;i++)for(I j=0;j<=s;j++)
    for(I k=0;k<2;k++)trn(i,j,k);
  for(I i=p+s;i<n;i++)add(vals[1][inds[i]]);
  I res=dp[p+s][s],j=s;
  for(I i=1;i<=s;i++){
    rem(i);
    I tot=dp[p+s-i][s-i]+sum;
    if(tot>res)res=tot,j=s-i;
    add(vals[1][inds[p+s-i]]);
  }
  for(I i=p+j+1;i<n;i++){
    I k=inds[i];
    maxs.push_back({-vals[1][k],k});
  }
  sort(maxs.begin(),maxs.end());
  for(I i=0;i<s-j;i++)
    ress[1].push_back(maxs[i].second);
  for(I i=p+j;i>0;i--){
    I k=pars[i][j];
    ress[k].push_back(inds[i-1]);
    j-=k;
  }
  printf("%i\n",res);
  for(I i=0;i<2;i++){
    sort(ress[i].begin(),ress[i].end());
    for(auto j:ress[i])printf("%i ",j+1);
    printf("\n");
  }
}