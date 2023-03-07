#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
vector<I>adjs[N];
I sizs[N];
I dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto b:adjs[a])if(b!=p)sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p=-1){
  for(auto b:adjs[a])if(b!=p&&sizs[b]*2>siz)return dfs2(b,siz,a);
  return a;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  printf("%i\n",dfs2(0,dfs1(0))+1);
}