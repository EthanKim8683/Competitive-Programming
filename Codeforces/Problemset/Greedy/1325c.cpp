#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

I cnts[N];
pair<I,I>edgs[N-1];
I inds[N-1];
I ress[N-1];

B cmp(I a,I b){
  auto[x,y]=edgs[a];
  auto[z,w]=edgs[b];
  return min(cnts[x],cnts[y])<min(cnts[z],cnts[w]);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    cnts[u]++,cnts[v]++;
    edgs[i]={u,v};
  }
  iota(inds,inds+n-1,0);
  sort(inds,inds+n-1,cmp);
  for(I i=0;i<n-1;i++)ress[inds[i]]=i;
  for(I i=0;i<n-1;i++)printf("%i\n",ress[i]);
}