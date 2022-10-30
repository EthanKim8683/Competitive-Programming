#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1000;
const I W=1000;

I w_arr[N];
I b_arr[N];
I pars[N];
I weis[N];
I beas[N];
I dp[N+1][W+1];
vector<I>coms;
vector<I>chds[N];

I fnd(I i){
  return pars[i]<0?i:pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,w;cin>>n>>m>>w;
  fill_n(pars,n,-1);
  for(I i=0;i<n;i++)cin>>w_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  for(I i=0;i<m;i++){
    I x,y;cin>>x>>y;
    uni(x-1,y-1);
  }
  for(I i=0;i<n;i++)weis[fnd(i)]+=w_arr[i];
  for(I i=0;i<n;i++)beas[fnd(i)]+=b_arr[i];
  for(I i=0;i<n;i++)chds[fnd(i)].push_back(i);
  for(I i=0;i<n;i++)if(fnd(i)==i)coms.push_back(i);
  I k=coms.size();
  for(I i=0;i<k;i++){
    for(auto j:chds[coms[i]]){
      I wei=w_arr[j],bea=b_arr[j];
      for(I l=0;l<=w;l++)if(l+wei<=w)dp[i+1][l+wei]=max(dp[i+1][l+wei],dp[i][l]+bea);
    }
    for(I j=0;j<=w;j++){
      I l=coms[i],wei=weis[l],bea=beas[l];
      if(j+wei<=w)dp[i+1][j+wei]=max(dp[i+1][j+wei],dp[i][j]+bea);
      dp[i+1][j]=max(dp[i+1][j],dp[i][j]);
    }
  }
  printf("%i\n",*max_element(dp[k],dp[k]+w+1));
}