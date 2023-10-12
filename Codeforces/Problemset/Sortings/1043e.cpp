#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=300000;
pair<I,I>coms[N];
vector<I>adjs[N];
I vals[N];
I inds[N];
Lli pres[N+1],sufs[N+1];
Lli ress[N];
B cmp(I a,I b){
  return vals[a]<vals[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    coms[i]={x,y};
    vals[i]=x-y;
  }
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++){
    auto[x,y]=coms[inds[i]];
    pres[i+1]=x,sufs[i]=y;
  }
  for(I i=0;i<n;i++)pres[i+1]+=pres[i];
  for(I i=n;i>0;i--)sufs[i-1]+=sufs[i];
  for(I i=0;i<n;i++){
    I j=inds[i];
    auto[x,y]=coms[j];
    ress[j]+=pres[i]+(Lli)y*i;
    ress[j]+=sufs[i+1]+(Lli)x*(n-i-1);
  }
  for(I i=0;i<n;i++){
    for(auto j:adjs[i]){
      auto[x1,y1]=coms[i];
      auto[x2,y2]=coms[j];
      ress[i]-=min(x1+y2,x2+y1);
    }
    printf("%lli ",ress[i]);
  }
}