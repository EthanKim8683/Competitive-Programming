#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
const I LOGN=18;
pair<I,Lli>pars[N-1];
vector<I>adjs[N];
pair<I,Lli>ancs[N][LOGN];
I deps[N];
I ress[N];
I adds[N],rems[N];
I dfs(I a){
  I sum=adds[a];
  for(auto b:adjs[a])sum+=dfs(b);
  ress[a]+=sum;
  sum-=rems[a];
  return sum;
}
I main(){
#ifndef ETHANKIM8683
  freopen("runaway.in","r",stdin);
  freopen("runaway.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli l;cin>>n>>l;
  for(I i=0;i<n-1;i++){
    I p;Lli l;cin>>p>>l,p--;
    pars[i]={p,l};
  }
  for(I i=0;i<n-1;i++){
    auto[p,l]=pars[i];
    adjs[p].push_back(i+1);
    ancs[i+1][0]={p,l};
  }
  for(I i=1;i<LOGN;i++)for(I j=0;j<n;j++){
    auto[a,l1]=ancs[j][i-1];auto[b,l2]=ancs[a][i-1];
    ancs[j][i]={b,l1+l2};
  }
  for(I i=0;i<n;i++){
    I a=i;Lli l1=0;
    for(I j=LOGN-1;j>=0;j--){
      auto[b,l2]=ancs[a][j];
      if(l1+l2<=l)a=b,l1+=l2;
    }
    adds[i]++,rems[a]++;
  }
  dfs(0);
  for(I i=0;i<n;i++)printf("%i\n",ress[i]);
}