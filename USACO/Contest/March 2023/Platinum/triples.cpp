#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
vector<I>adjs[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  /*
  IDK
  */
}