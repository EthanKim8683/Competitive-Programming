#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=3e5;
I typs[N];
vector<I>adjs[N];
void dfs(I a){
  for(auto b:adjs[a]){
    
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>typs[i];
  for(I i=1;i<n;i++){I p;cin>>p,adjs[p-1].push_back(i);}
  dfs(0);
}