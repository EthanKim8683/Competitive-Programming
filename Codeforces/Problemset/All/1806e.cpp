#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I K=317;
I a_arr[N];
vector<I>adjs[N];
vector<I>deps[N];
vector<tuple<Lli,I,I>>mems[N];
I inds[N];
I pars[N];
I cpss[N];
void dfs(I a,I d=0){
  inds[a]=d;
  deps[d].push_back(a);
  for(auto b:adjs[a])dfs(b,d+1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  pars[0]=-1;
  for(I i=1;i<n;i++){
    I p;cin>>p,p--;
    pars[i]=p;
    adjs[p].push_back(i);
  }
  dfs(0);
  mems[0].push_back({(Lli)a_arr[0]*a_arr[0],-1,-1});
  for(I i=1;i<n;i++)if(deps[i].size()<K){
    for(I j=0;j<deps[i].size();j++)cpss[deps[i][j]]=j;
    for(I j=0;j<deps[i].size();j++)for(I k=0;k<deps[i].size();k++){
      I a=deps[i][j],b=deps[i][k],c=pars[a],d=pars[b];
      if(a>b)swap(a,b);
      if(c>d)swap(c,d);
      if(mems[i-1].size()>0){
        auto[val,e,f]=mems[i-1][cpss[c]*deps[i-1].size()+cpss[d]];
        mems[i].push_back({val+(Lli)a_arr[a]*a_arr[b],e,f});
      }else{
        mems[i].push_back({(Lli)a_arr[a]*a_arr[b],c,d});
      }
    }
  }
  while(q--){
    I x,y;cin>>x>>y,x--,y--;
    Lli res=0;
    while(x!=-1&&y!=-1){
      if(x>y)swap(x,y);
      I i=inds[x];
      if(mems[i].size()>0){
        auto[val,z,w]=mems[i][cpss[x]*deps[i].size()+cpss[y]];
        res+=val,tie(x,y)=tie(z,w);
      }else{
        res+=(Lli)a_arr[x]*a_arr[y],x=pars[x],y=pars[y];
      }
    }
    printf("%lli\n",res);
  }
}