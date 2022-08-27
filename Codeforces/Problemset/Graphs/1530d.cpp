#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

B viss[N];
I a_arr[N];
I pars[N];
I inds[N],outs[N];
I heds[N],tals[N];
vector<pair<I,I>>pats;
I ress[N];
priority_queue<pair<I,I>>que;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    pats.clear();
    fill_n(viss,n,false);
    fill_n(pars,n,-1);
    fill_n(inds,n,0),fill_n(outs,n,0);
    fill_n(heds,n,-1),fill_n(tals,n,-1);
    I res=0;
    for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
    for(I i=0;i<n;i++)inds[a_arr[i]]++;
    for(I i=0;i<n;i++)que.push({-inds[i],i});
    while(que.size()){
      auto[ind,a]=que.top();que.pop();
      I b=a_arr[a];
      if(viss[b])continue;
      viss[b]=true;
      uni(a,b);
      outs[a]=1;
      ress[a]=b;
      res++;
    }
    for(I i=0;i<n;i++){
      if(outs[i]==0)heds[fnd(i)]=i;
      if(inds[i]==0)tals[fnd(i)]=i;
    }
    for(I i=0;i<n;i++){
      if(fnd(i)!=i)continue;
      if(heds[i]==-1||tals[i]==-1)continue;
      pats.push_back({heds[i],tals[i]});
    }
    for(I i=0;i<pats.size();i++){
      auto a=pats[i],b=pats[(i+1)%pats.size()];
      ress[a.first]=b.second;
    }
    printf("%i\n",res);
    for(I i=0;i<n;i++)printf("%i ",ress[i]+1);
    printf("\n");
  }
  return 0;
}