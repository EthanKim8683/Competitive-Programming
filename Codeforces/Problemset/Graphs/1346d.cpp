#include<iostream>
#include<cstdio>
#include<tuple>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=200000;
const I M=200000;

I maxs[N];
tuple<I,I,I>edgs[M];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    fill_n(maxs,n,0);
    for(I i=0;i<m;i++){
      I u,v,w;cin>>u>>v>>w,u--,v--;
      edgs[i]={u,v,w};
      maxs[u]=max(maxs[u],w);
      maxs[v]=max(maxs[v],w);
    }
    B res=true;
    for(I i=0;i<m;i++){
      auto[u,v,w]=edgs[i];
      res&=min(maxs[u],maxs[v])==w;
    }
    if(!res){printf("NO\n");continue;}
    printf("YES\n");
    for(I i=0;i<n;i++)printf("%i ",maxs[i]);
    printf("\n");
  }
  return 0;
}