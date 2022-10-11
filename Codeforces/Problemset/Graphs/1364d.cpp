#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

vector<I>adjs[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  
}